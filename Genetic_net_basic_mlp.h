/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_net_basic_mlp.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:03:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 15:41:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Genetic.h"
#include <vector>

using namespace std;

class	Genetic_net_basic_mlp: private Genetic
{
	public:
		Genetic_net_basic_mlp(Learning_net_environment &env, int nbPeople);

	private:
		int		do_get_generation(void);
		int		do_get_best_score(void);
		void	do_next_gen(void);

		vector<People_basic_mlp>	m_people;
		int							m_generation = 0;
};
