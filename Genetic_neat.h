/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_neat.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:14:30 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/16 02:11:01 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Genetic.h"
#include "People_neat.h"
#include "Learning_environment_net.h"
#include <vector>

using namespace std;

class	Genetic_neat: public Genetic_net
{
	public:
		Genetic_neat();

	private:
		int		do_get_generation(void);
		int		do_get_best_score(void);
		void	do_next_gen(void);
		void	apply_evolving_rules(void);
		int		kill_one_people(int n);
		int		sigma_kill(int n);

		vector<People_neat>			m_people;
		int							m_generation = 1;
		double						m_mutate_prob = 0.8;
		Learning_environment_net	&m_env; //Temp have to be replace with a evaluator
		size_t						m_cur_people_alive;
};
