/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learn.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:42:05 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/23 22:45:24 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEARN_HPP
# define LEARN_HPP

# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <regex>
# include <vector>
# include <cmath>
# include <unistd.h>
# include <iomanip>
# include <SFML/Graphics.hpp>

# define GREEN "\033[32m"
# define RED "\033[31m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define EOC "\033[0m"

# define WINOFFSET 50

class Learn
{

public:

	Learn(void);
	~Learn(void);

	bool isNumber(std::string const &str);
	void parseDatas(char *path);
	void saveTheta(void);

	void drawText(sf::RenderWindow &window, std::string str, int x, int y, int size);
	void drawNumber(sf::RenderWindow &window, double nb, int x, int y, int size);
	void drawGrid(sf::RenderWindow &window);
	void drawPoints(sf::RenderWindow &window);
	void drawUI(sf::RenderWindow &window, int i);

	int graphicLearning(void);
	int basicLearngin(void);
	void run(char *path, bool graphic);
	void avgError(void);
	double estimatePrice(double x, double a, double b);

private:

	std::vector<double> _vecX;
	std::vector<double> _vecY;
	int _m;
	double _a;
	double _b;
	double _errorA;
	double _errorB;
	double _avgX;
	int _winX;
	int _winY;
	int _maxX;
	int _maxY;

};

#endif
