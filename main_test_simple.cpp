/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_simple.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:29:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 14:28:24 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgen.h"

int	main(int ac, char **av)
{
	Test_simple				test_learning(50);
	Genetic_net_basic_mlp	genetic(test_learning, 100);

	for (int g = 0; g < 100; g++)
	{
		genetic.next_gen();
		std::cout << "gen(%d)", g;
		std::cout << " best score = " << genetic.get_best_score() << std:endl;
	}
	return (0);
}
