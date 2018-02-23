/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learn.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:43:45 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/23 21:15:44 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Learn.class.hpp"

Learn::Learn(void):
_m(0), _a(0), _b(0), _errorA(10000), _errorB(10000), _winX(1000 + WINOFFSET),
_winY(500 + WINOFFSET), _maxX(300000), _maxY(10000)
{
}

Learn::~Learn(void)
{
}

bool Learn::isNumber(std::string const &str)
{
	return (std::regex_match(str, std::regex("^[+\\-]?(?:|0|[1-9]\\d*)(?:\\.\\d*)?$")));
}

void Learn::parseDatas(char *path)
{
	std::fstream file;
	std::string buff;
	std::string valueX;
	std::string valueY;

	file.open(path);
	if (!file.is_open())
	{
		std::cout << RED << "Opening \"" << path << "\" failed" << EOC << std::endl;
		exit(-1);
	}
	while (std::getline(file, buff))
	{
		valueX = buff.substr(0, buff.find(","));
		valueY = buff.substr(buff.find(",") + 1);
		if (isNumber(valueX) && isNumber(valueY))
		{
			_vecX.push_back(std::stof(valueX));
			_vecY.push_back(std::stof(valueY));
			_m++;
		}
	}
	for (int i = 0; i < _m; i++)
		_avgX += _vecX[i];
	_avgX /= _m;
	file.close();
}

void Learn::saveTheta(void)
{
	std::ofstream file;
	std::string name("theta_data");

	file.open(name);
	if (!file.is_open())
	{
		std::cout << RED << "Opening \"" << name << "\" failed" << EOC << std::endl;
		exit(-1);
	}
	file << _b << std::endl;
	file << _a << std::endl;
	file.close();
}

void Learn::drawText(sf::RenderWindow &window, std::string str, int x, int y, int size)
{
	sf::Text text;
	sf::Font font;

	if (font.loadFromFile("font.ttf"))
	{
		text.setFont(font);
		text.setString(str);
		text.setCharacterSize(size);
		text.setFillColor(sf::Color::Black);
		text.setPosition(x, y);
		window.draw(text);
	}
	else
		std::cout << "font error\n";
}

void Learn::drawNumber(sf::RenderWindow &window, int nb, int x, int y, int size)
{
	std::stringstream ss;

	ss << nb;
	drawText(window, ss.str(), x, y, size);
}

void Learn::drawGrid(sf::RenderWindow &window)
{
	sf::RectangleShape cols(sf::Vector2f(1, _winY - WINOFFSET));
	sf::RectangleShape lines(sf::Vector2f(_winX - WINOFFSET, 1));
	int nb;

	cols.setFillColor(sf::Color(100, 100, 100));
	lines.setFillColor(sf::Color(100, 100, 100));
	nb = 0;
	for (int x = WINOFFSET; x <= _winX;)//Column every 7500
	{
		cols.setPosition(x, 0);
		window.draw(cols);
		if (x > 0)
		{
			if (!(x % 50))
				drawNumber(window, nb, x - 15, _winY - WINOFFSET + 3, 15);
			nb += 7500;
		}
		x += 25;
	}
	nb = 9500;
	for (int y = 25; y <= _winY - WINOFFSET;)//Line every 500
	{
		lines.setPosition(WINOFFSET, y);
		window.draw(lines);
		if (y > 0)
		{
			if (y % 50)
				drawNumber(window, nb, 10, y - 10, 15);
			nb -= 500;
		}
		y += 25;
	}
	drawText(window, "Mileage", _winX / 2 - 30, _winY - 25, 20);
	drawText(window, "Price", 2, _winY / 2 - 37, 20);
}

void Learn::drawPoints(sf::RenderWindow &window)
{
	sf::RectangleShape dot(sf::Vector2f(6, 6));

	dot.setFillColor(sf::Color(0, 0, 250));
	for (int i = 0; i < _m; i++)
	{
		dot.setPosition(WINOFFSET + _vecX[i] * (_winX - WINOFFSET) / _maxX,\
			_winY - WINOFFSET - (_vecY[i] * (_winY - WINOFFSET) / _maxY));
		window.draw(dot);
	}

	sf::RectangleShape line(sf::Vector2f(1500, 2));
	line.setFillColor(sf::Color(255, 0, 0));
	line.setPosition(WINOFFSET, _winY - WINOFFSET - (_b * (_winY - WINOFFSET) / _maxY));
	line.rotate(-_a * 825);
	window.draw(line);
}

void Learn::run(char *path)
{
	double learningRate = 0.03;
	double minError = 3;
	int i = 0;
	sf::RenderWindow window(sf::VideoMode(_winX, _winY), "Linear Regression");
	sf::Event event;

	parseDatas(path);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		drawGrid(window);
		drawPoints(window);
		drawText(window, "Iterations : ", 20, _winY - 25, 20);
		drawNumber(window, i, 110, _winY - 25, 20);
		if (std::abs(_errorA) > minError || std::abs(_errorB) > minError)
		{
			avgError();
			if (std::abs(_errorA) > minError)
				_a -= (learningRate * _errorA) / _avgX / _avgX;
			if (std::abs(_errorB) > minError)
				_b -= learningRate * _errorB;
			i++;
		}
		window.display();
	}
	std::cout << "Learning done after " << i << " iterations !" << std::endl\
		<< "theta0 = " << _b << std::endl\
		<< "theta1 = " << _a << std::endl;
	saveTheta();
}

void Learn::avgError(void)
{
	_errorA = 0;
	_errorB = 0;
	for (int i = 0; i < _m; i++)
	{
		_errorA += (estimatePrice(_vecX[i], _a, _b) - _vecY[i]) * _vecX[i];
		_errorB += estimatePrice(_vecX[i], _a, _b) - _vecY[i];
	}
	_errorA /= _m;
	_errorB /= _m;
}

double Learn::estimatePrice(double x, double a, double b)
{
	return (b + (a * x));
}
