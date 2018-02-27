/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 10:56:50 by qhonore           #+#    #+#             */
/*   Updated: 2018/02/27 16:01:50 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Learn.class.hpp"

int main(int ac, char **av)
{
	Learn learn;
	bool graphic = false;

	if (ac >= 2)
	{
		if (ac >= 3 && av[2] == std::string("-g"))
			graphic = true;
		learn.run(av[1], graphic);
	}
	return (0);
}
