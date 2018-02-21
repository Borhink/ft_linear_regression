/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 10:56:50 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/21 21:08:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fstream>
# include <iostream>
# include <string>
# include <regex>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define EOC "\033[0m"

double estimatePrice(double x, double a, double b)
{
	return (b + (a * x));
}

int main(int ac, char **av)
{
	double learningRate = 0.03;
	double tmpA = 0;
	double tmpB = 0;
	std::fstream file;
	std::string buff;
	std::string valueX;
	std::string valueY;

	if (ac >= 2)
	{
		file.open(av[1]);
		if (!file.is_open())
		{
			std::cout << RED << "Opening \"" << av[1] << "\" failed" << EOC << std::endl;
			return (-1);
		}
		while (!file.eof())
		{
			std::getline(file, buff);
			if (file.fail() || file.eof())
			{
				std::cout << RED << "Reading \"" << av[1] << "\" failed" << EOC << std::endl;
				return (-1);
			}
			valueX = buff.substr(0, buff.find(","));
			valueY = buff.substr(buff.find(",") + 1);
			if (std::regex_match(valueX, std::regex("^[+\\-]?(?:|0|[1-9]\\d*)(?:\\.\\d*)?$"))
			&& std::regex_match(valueY, std::regex("^[+\\-]?(?:|0|[1-9]\\d*)(?:\\.\\d*)?$")))
				std::cout << "valueX: " << valueX << ", valueY: " << valueY << std::endl;
		}
		// for (int i = 0; i < m; i++)
		// {
		// 	tmpB = estimatePrice(mileage[i], tmpA, tmpB) - price[i];
		// 	tmpA = (estimatePrice(mileage[i], tmpA, tmpB) - price[i]) * milleage[i];
		// }
		// tmpB = learningRate * (tmpB / m);
		// tmpA = learningRate * (tmpA / m);
		// std::cout << "tmpA: " << tmpA << ", tmpB: " << tmpB << std::endl;
	}
	return (0);
}
/*
size(x)	prix(y)	(x - ~x)	(y - ~y)	(x - ~x)*(y - ~y)	(x - ~x)2	(y - ~y)2
-----------------------------------------------------------------------------------
30		300		10			100			1000				100			10000
20		200		0			0			0					0			0
10		100		-10			-100		1000				100			10000
-------------------------------------------------------------------------------------
60		600								2000				200			20000
~20		~200

m = nb training = 3

correlation coef(r) = (x - ~x)*(y - ~y) / sqrt((x - ~x)2 * (y - ~y)2) = 2000 / sqrt(4000000) = 2000 / 2000 = 1

Sy = sqrt((y - ~y)2 / m - 1) = sqrt(20000 / 2) = sqrt(10000) = 100
Sx = sqrt((x - ~x)2 / m - 1) = sqrt(200 / 2) = sqrt(100) = 10

b = r * (Sy / Sx) = 1 * (100 / 10) = 1 * 10 = 10
a = ~y - (b * ~x) = 200 - (10 * 20) = 200 - (200) = 0

Y = a + b * x(50) = 0 + 10 * 50 = 500

================================================================================

estimatePrice(x) = b + (a ∗ x)
learningRate = 0.03

for (i = 0; i < m; i++)
{
	tmpB = estimatePrice(mileage[i]) - price[i];
	tmpA = (estimatePrice(mileage[i]) - price[i]) * milleage[i];
}
tmpB = learningRate * (tmpB / m);
tmpA = learningRate * (tmpA / m);
*/
