/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_simple.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:29:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 20:06:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgen.h"
#include "Test_simple.h"
#include <iostream>

int	main(int ac, char **av)
{
	Test_simple				test_learning(15);
	Genetic_net_basic_mlp	genetic(test_learning, 100);
	int						best_score_total = 0;
	int						gen_best_total = 0;

	for (int g = 0; g < 10000; g++)
	{
		genetic.next_gen();
		if (best_score_total < genetic.get_best_score())
		{
			best_score_total = genetic.get_best_score();
			gen_best_total = g;
			std::cout << "gen(" << g << ")";
			std::cout << " best score = " << genetic.get_best_score() << std::endl;
			test_learning.eval_and_display(genetic.get_best_ref(), g);
		}
		else if (g > 0 && g % 1000 == 0)
			std::cout << "gen(" << g << ")" << std::endl;
		/*
		std::cout << "gen(" << g << ")";
		std::cout << " best score = " << genetic.get_best_score() << std::endl;
		*/
	}
	return (0);
}
