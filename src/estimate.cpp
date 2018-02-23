/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estimate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 10:56:50 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/23 16:26:05 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

#define RED "\033[31m"
#define EOC "\033[0m"

static double estimatePrice(double x, double a, double b)
{
	return (b + (a * x));
}

static double estimatePriceExpo(double x, double a, double b)
{
	int pivot = 400000;

	return (b / (1 + (x * 100 / pivot * -a)));
}

int main(int ac, char **av)
{
	std::fstream file;
	std::string buff;
	unsigned int nb;
	double a = 0.0;
	double b = 0.0;
	bool expo = false;

	if (ac >= 2 && av[1] == std::string("-x"))
		expo = true;
	try
	{
		std::cout << "Loading theta datas..." << std::endl;
		file.open("theta_data");
		if (file.is_open())
		{
			file >> b;
			if (std::cin.fail())
				throw std::runtime_error("Invalid theta0");
			file >> a;
			if (std::cin.fail())
				throw std::runtime_error("Invalid theta1");
			file.close();
		}
		std::cout << "theta0 : "<< b << std::endl << "theta1 : " << a << std::endl;
		std::cout << "Enter a mileage : ";
		std::cin >> nb;
		if (std::cin.fail())
			throw std::runtime_error("Bad entry");
		if (expo)
			std::cout << "Estimated price : " << estimatePriceExpo(nb, a, b) << std::endl;
		else
			std::cout << "Estimated price : " << estimatePrice(nb, a, b) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << RED << "Error : " << e.what() << EOC << std::endl;
	}
	return (0);
}
