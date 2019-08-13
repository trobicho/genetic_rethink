/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_simple.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:29:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/13 18:41:43 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgen.h"
#include "Snake_copy_test.h"
#include <iostream>

int	main(int ac, char **av)
{
	Snake					test_learning(45, 45);
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
			test_learning.eval_and_display(genetic.get_best_ref(), g);
			std::cout << "gen(" << g << ")";
			std::cout << " best score = " << genetic.get_best_score() << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------------------------------"
				<< std::endl << std::endl;
		}
		else if (g > 0 && g % 1000 == 0)
		{
			test_learning.eval_and_display(genetic.get_best_ref(), g);
			std::cout << "gen(" << g << ")" << std::endl;
		}
		else if (g > 0 && g % 100 == 0)
		{
			test_learning.eval_and_display(genetic.get_best_ref(), g);
			std::cout << "gen(" << g << ")" << std::endl;
		}
	}
	return (0);
}
