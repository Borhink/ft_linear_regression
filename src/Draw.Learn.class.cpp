/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Draw.Learn.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 22:21:00 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/23 22:37:26 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Learn.class.hpp"

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

void Learn::drawNumber(sf::RenderWindow &window, double nb, int x, int y, int size)
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

void Learn::drawUI(sf::RenderWindow &window, int i)
{
	drawGrid(window);
	drawPoints(window);
	drawText(window, "Iterations : ", 20, _winY - 25, 20);
	drawNumber(window, i, 105, _winY - 25, 20);
	drawText(window, "Theta 0 : ", 170, _winY - 25, 20);
	drawNumber(window, _b, 235, _winY - 25, 20);
	drawText(window, "Theta 1 : ", 330, _winY - 25, 20);
	drawNumber(window, _a, 395, _winY - 25, 20);
}
