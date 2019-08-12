/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_net_basic_mlp.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:03:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 19:10:47 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Genetic.h"
#include "People_basic_mlp.h"
#include "Learning_environment_net.h"
#include <vector>

using namespace std;

class	Genetic_net_basic_mlp: public Genetic
{
	public:
		Genetic_net_basic_mlp(Learning_environment_net &env, int nbPeople);
		People_basic_mlp&	get_best_ref() {return (m_people[0]);} //arf interface problem

	private:
		int		do_get_generation(void);
		int		do_get_best_score(void);
		void	do_next_gen(void);
		void	apply_evolving_rules(void);
		int		kill_one_people(int n);
		int		sigma_kill(int n);

		vector<People_basic_mlp>	m_people;
		int							m_generation = 1;
		double						m_mutate_prob = 0.8;
		Learning_environment_net	&m_env; //Temp have to be replace with a evaluator
		size_t						m_cur_people_alive;
};
