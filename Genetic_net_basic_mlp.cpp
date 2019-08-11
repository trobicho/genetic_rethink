/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_net_basic_mlp.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 00:52:37 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/11 20:43:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Genetic_net_basic_mlp.h"
#include <algorithm>

Genetic_net_basic_mlp::
	Genetic_net_basic_mlp(Learning_environment_net &env, int nb_people):
		m_env(env)
{
	m_people.reserve(nb_people);
	for (int i = 0; i < nb_people; i++)
	{
		m_people.push_back(
			People_basic_mlp(env.get_nb_input(), env.get_nb_output()));
	}
}

int		Genetic_net_basic_mlp::do_get_generation(void)
{
	return (m_generation);
}

int		Genetic_net_basic_mlp::do_get_best_score(void)
{
	return (m_people[0].get_score());
}

void	Genetic_net_basic_mlp::do_next_gen(void)
{
	for (int i = 0; i < m_people.size(); i++)
	{
		m_env.evaluate(m_people[i], m_generation);
	}
	std::sort(m_people.rbegin(), m_people.rend());
	m_generation++;
}
