/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_neat.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:14:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/15 12:31:59 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Genetic_neat.h"
#include "my_lib.h"
#include <algorithm>
#include <iostream>

Genetic_neat::
	Genetic_neat(Learning_environment_net &env, int nb_people):
		m_env(env)
{
	m_people.reserve(nb_people);
	for (int i = 0; i < nb_people; i++)
	{
		m_people.push_back(
			People_neat(env.get_nb_input(), env.get_nb_output()));
	}
}

int		Genetic_neat::do_get_generation(void)
{
	return (m_generation);
}

int		Genetic_neat::do_get_best_score(void)
{
	return (m_people[0].get_score());
}

void	Genetic_neat::do_next_gen(void)
{
	if (m_generation > 0)
	{
		apply_evolving_rules();
	}
	for (auto i = 0; i < m_people.size(); i++)
	{
		m_people[i].set_score(m_env.evaluate(m_people[i], m_generation));
	}
	std::sort(m_people.rbegin(), m_people.rend());
	m_generation++;
}

int		Genetic_neat::kill_one_people(int n)
{

	if (m_cur_people_alive > 1 && n < m_cur_people_alive)
	{
		if (n < m_cur_people_alive - 1)
		{
			auto	&temp = m_people[n];
			m_people[n] = m_people[m_cur_people_alive - 1];
			m_people[m_cur_people_alive - 1] = temp;
		}
		m_cur_people_alive--;
		return (1);
	}
	return (0);
}

int		Genetic_neat::sigma_kill(int nb)
{
	int	nb_kill;

	nb_kill = 0;
	for (int i = 0; i < nb; i++)
	{
		int n = trl::wheel_sigma(m_cur_people_alive - 1);
		nb_kill += kill_one_people(n);
		//std::cout << n << " ";
	}
	//std::cout << std::endl;
	return (nb_kill);
}

void	Genetic_neat::apply_evolving_rules(void)
{
	int		nb_kill;
	auto&	mt = trl::req_mt_ref();
	std::uniform_real_distribution<double>
			dis(0.0, 1.0);

	m_cur_people_alive = m_people.size();
	std::sort(m_people.rbegin(), m_people.rend());
	nb_kill = sigma_kill(m_cur_people_alive / 3);
	for (auto i = 0; nb_kill > 0; i++)
	{
		if (i >= m_cur_people_alive)
			i = 0;
		if (dis(mt) < m_mutate_prob)
		{
			m_people[m_cur_people_alive + (nb_kill - 1)].mutate_weight();
			m_people[m_cur_people_alive + (nb_kill - 1)].mutate_add_node();
			m_people[m_cur_people_alive + (nb_kill - 1)].mutate_add_connection();
			nb_kill--;
		}
	}
	m_cur_people_alive = m_people.size();
}
