/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learn.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:43:45 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/27 16:05:10 by qhonore          ###   ########.fr       */
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

int Learn::graphicLearning(void)
{
	double learningRate = 0.03;
	double minError = 3;
	int i = 0;
	sf::RenderWindow window(sf::VideoMode(_winX, _winY), "Linear Regression");
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed
			|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
		}
		window.clear(sf::Color::White);
		drawUI(window, i);
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
	return (i);
}

int Learn::basicLearngin(void)
{
	double learningRate = 0.03;
	double minError = 3;
	int i = 0;

	while (std::abs(_errorA) > minError || std::abs(_errorB) > minError)
	{
		avgError();
		if (std::abs(_errorA) > minError)
			_a -= (learningRate * _errorA) / _avgX / _avgX;
		if (std::abs(_errorB) > minError)
			_b -= learningRate * _errorB;
		i++;
	}
	return (i);
}

void Learn::run(char *path, bool graphic)
{
	int i;

	try
	{
		parseDatas(path);
	}
	catch (std::exception &e)
	{
		std::cout << RED << e.what() << EOC << std::endl;
		return;
	}
	if (graphic)
		i = graphicLearning();
	else
		i = basicLearngin();
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
