/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_neat.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:14:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/29 21:22:37 by trobicho         ###   ########.fr       */
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
	m_target_population = nb_people;
	m_people.reserve(nb_people);
	for (int i = 0; i < nb_people; i++)
	{
		m_people.push_back(
			People_neat(env.get_nb_input(), env.get_nb_output()
				, &m_handler));
	}
	create_species();
}

int		Genetic_neat::do_get_generation(void)
{
	return (m_generation);
}

double	Genetic_neat::do_get_best_score(void)
{
	return (m_people[0].get_score());
}

void	Genetic_neat::do_next_gen(void)
{
	m_handler.flush_innov();
	if (m_generation > 1)
	{
		//apply_evolving_rules();
		breed_all_species();
	}
	for (auto i = 0; i < m_people.size(); i++)
	{
		m_people[i].set_score(m_env.evaluate(m_people[i], m_generation));
	}
	species_choose_representative();
	std::sort(m_people.rbegin(), m_people.rend(), [&m_people = m_people]
			(People_neat p1, People_neat p2) {return (p1.get_sharing_score() 
			< p2.get_sharing_score());});
	place_all_into_species();
	species_calc_sharing_fitness();
	std::sort(m_people.rbegin(), m_people.rend());
	m_generation++;
}

void	Genetic_neat::create_species(void)
{
	int	p = trl::rand_uniform_int(0, m_people.size() - 1);

	m_species.push_back(s_species(m_env));
	m_species[0].nb_members = 0;
	m_species[0].representative_people.copy_gene(m_people[p]);
	place_all_into_species();
}

void	Genetic_neat::species_choose_representative(void)
{
	int	p_s;

	for (int s = 0; s < m_species.size(); s++)
	{
		p_s = trl::rand_uniform_int(0, m_species[s].nb_members - 1);
		m_species[s].nb_members = 0;
		for (int p = 0, cur_p_s = 0; p < m_people.size(); p++)
		{
			if (m_people[p].get_species() == s)
			{
				if (cur_p_s == p_s)
				{
					m_species[s].representative_people = m_people[p];
					m_species[s].representative_people.copy_gene(m_people[p]);
					break;
				}
				cur_p_s++;
			}
		}
	}
}

void	Genetic_neat::species_calc_sharing_fitness(void)
{
	std::vector<People_neat>::iterator	p;
	std::vector<People_neat>::iterator	p_sh;
	int									sh;
	double								delta;

	for (int s = 0; s < m_species.size(); ++s)
	{
		m_species[s].sharing_fit = 0.0;
		m_species[s].people.clear();
		m_species[s].people.reserve(m_species[s].nb_members);
	}
	for (p = m_people.begin(); p != m_people.end(); ++p)
	{
		if (p->get_score() == 0)
			p->set_sharing_score(0.001);
		else
		{
			sh = 1;
			for (p_sh = m_people.begin(); p_sh != m_people.end(); ++p_sh)
			{
				if (p_sh == p)
					continue ;
				delta = People_neat::get_delta_dist(*p, *p_sh
					, m_species_var.c1, m_species_var.c2, m_species_var.c3);
				if (delta < m_species_var.delta_threshold)
					sh++;
			}
			p->set_sharing_score((double)p->get_score() / (double)sh);
			m_species[p->get_species()].sharing_fit += p->get_sharing_score();
		}
		m_species[p->get_species()].people.push_back(*p);
	}
	m_total_species_fitness = 0.0;
	for (auto spi = m_species.begin(); spi != m_species.end();)
	{
		m_total_species_fitness += spi->sharing_fit;
		if (spi->nb_members != spi->people.size())
		{
			std::cout << "BUG!!! {" << spi->nb_members << ", " << spi->people.size() << "}" << std::endl;
			spi->nb_members = spi->people.size();
		}
		if (spi->nb_members == 0)
		{
			m_species.erase(spi);
		}
		else
			spi++;
	}
}

void	Genetic_neat::place_all_into_species(void)
{
	bool	found;
	double	delta;

	for (int s = 0; s < m_species.size(); s++)
		m_species[s].nb_members = 0;
	for (int p = 0; p < m_people.size(); p++)
	{
		found = false;
		for (int s = 0; s < m_species.size(); s++)
		{
			delta = People_neat::get_delta_dist(
					m_species[s].representative_people, m_people[p]
					, m_species_var.c1, m_species_var.c2, m_species_var.c3);
			if (delta < m_species_var.delta_threshold)
			{
				m_people[p].set_species(s);
				m_species[s].nb_members++;
				found = true;
				break;
			}
			//std::cout << "delta = " << delta << std::endl;
		}
		if (!found)
		{
			m_people[p].set_species(m_species.size());
			m_species.push_back(s_species(m_env));
			m_species.back().nb_members = 1;
			m_species.back().representative_people.copy_gene(m_people[p]);
		}
	}
	int s = 0;
	for (auto spi = m_species.begin(); spi != m_species.end();)
	{
		if (spi->nb_members == 0)
		{
			m_species.erase(spi);
			for (int p = 0; p < m_people.size(); p++)
			{
				if (m_people[p].get_species() > s)
				{
					m_people[p].set_species(m_people[p].get_species() - 1);
				}
			}
		}
		else
		{
			++s;
			++spi;
		}
	}
}

void	Genetic_neat::breed_all_species(void)
{
	size_t	nb_offspring;
	size_t	nb_breed = 0;

	m_people.clear();
	for (int s = 0; s < m_species.size() && nb_breed < m_target_population; s++)
	{
		//m_species.people.erase(m_species.people.back());
		if (m_species[s].sharing_fit > 0.001)
		{
			nb_offspring = (m_species[s].sharing_fit / m_total_species_fitness)
				* m_target_population;
			nb_breed += breed_one_species(m_species[s], nb_offspring);
		}
	}
	int nb_error = 0;
	while (nb_breed < m_target_population)
	{
		nb_breed += breed_one_species_round_error(
			m_species[trl::rand_uniform_int(0, m_species.size() - 1)]);
		nb_error++;
	}
	std::cout << "nb round error: " << nb_error << std::endl;
}

int		Genetic_neat::breed_one_species_round_error(s_species &species)
{
	int p = trl::rand_uniform_int(0, species.nb_members - 1);

	m_people.push_back(species.people[p]);
	m_people.back().copy_gene(species.people[p]);
	mutate_one_people(m_people.back());
	return (1);
}

int		Genetic_neat::breed_one_species(s_species &species, int nb_offspring)
{
	std::vector<People_neat>::iterator	p = species.people.begin();
	int									people_breed;
	int									breed = 0;
	auto&								mt = trl::req_mt_ref();
	std::uniform_real_distribution<double>
										dis(0.0, 1.0);

	for (; p != species.people.end() && breed < nb_offspring; ++p)
	{
		people_breed = std::round(
				(p->get_sharing_score() / species.sharing_fit) * nb_offspring);
		for (int b = 0; b < people_breed && breed + b < nb_offspring; b++)
		{
			m_people.push_back(*p);
			dis(mt);
			if (dis(mt) < m_mutate_prob || species.nb_members == 1)
			{
				m_people.back().copy_gene(*p);
				mutate_one_people(m_people.back());
			}
			else
			{
				int p2 = trl::rand_uniform_int(0, species.nb_members - 2);
				if (p == species.people.begin() + p2)
					p2++;
				m_people.back().mating(*p, species.people[p2]);
			}
		}
		breed += people_breed;
	}
	return (breed);
}

int		Genetic_neat::kill_one_people(int n)
{

	if (m_cur_people_alive > 1 && n < m_cur_people_alive)
	{
		m_people.erase(m_people.begin() + n);
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
	double	p;
	auto&	mt = trl::req_mt_ref();
	std::uniform_real_distribution<double>
			dis(0.0, 1.0);

	m_cur_people_alive = m_people.size();
	std::sort(m_people.rbegin(), m_people.rend());
	nb_kill = sigma_kill(m_cur_people_alive / 3);
	while (nb_kill > 0)
	{
		if (dis(mt) < m_mutate_prob)
		{
			int p = trl::rand_uniform_int(0, m_cur_people_alive - 1);

			m_people.push_back(m_people[p]);
			m_people.back().copy_gene(m_people[p]);
			mutate_one_people(m_people.back());
			nb_kill--;
		}
		else
		{
			int p1 = trl::wheel_sigma_rank(m_cur_people_alive - 1);
			int p2 = trl::wheel_sigma_rank(m_cur_people_alive - 2);

			if (p2 == p1)
				p2++;
			m_people.push_back(m_people[p1]);
			m_people.back().mating(m_people[p1], m_people[p2]);
			nb_kill--;
		}
	}
	m_cur_people_alive = m_people.size();
}

void	Genetic_neat::mutate_one_people(People_neat &people)
{
	double	d = trl::rand_uniform_double(0, 1);

	if (d < 0.97)
	{
		if (d > 0.87)
			people.mutate_weight_full_rand();
		else if (d > 0.8)
			people.mutate_weight_add();
		else
			people.mutate_weight_mul();
	}
	else if (d < 0.985)
		people.mutate_add_node();
	else
		people.mutate_add_connection();
}
