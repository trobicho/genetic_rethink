/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_neat.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:14:30 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/24 04:21:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Genetic.h"
#include "People_neat.h"
#include "Learning_environment_net.h"
#include <vector>

using namespace std;

struct	s_species_var
{
	double	c1 = 1.0;
	double	c2 = 1.0;
	double	c3 = 0.4;
	double	delta_threshold = 1.5;
};

struct	s_species
{
	s_species(Learning_environment_net &env)
		: representative_people(env.get_nb_input(), env.get_nb_output()
		, nullptr){};
	int								nb_members;
	People_neat						representative_people;
	std::vector<People_neat>		people;
	double							sharing_fit;
};

class	Genetic_neat: public Genetic
{
	public:
		Genetic_neat(Learning_environment_net &env, int nb_people);
		People_net&		get_best_ref() {return (m_people[0]);} //arf interface problem
		People_neat&	get_best_debug_ref() {return (m_people[0]);} //arf interface problem

		vector<s_species>&		get_species_vec_ref(void){return m_species;}

	private:
		int		do_get_generation(void);
		int		do_get_best_score(void);
		void	do_next_gen(void);
		void	create_species(void);
		void	species_choose_representative(void);
		void	place_all_into_species(void);
		void	breed_all_species(void);
		int		breed_one_species(s_species &species, int nb_offspring);
		void	species_calc_sharing_fitness(void);
		void	apply_evolving_rules(void);
		void	mutate_one_people(People_neat &people);
		int		kill_one_people(int n);
		int		sigma_kill(int n);
		friend int		get_new_innov_number();

		vector<People_neat>			m_people;
		int							m_generation = 1;
		double						m_mutate_prob = 0.8;
		Learning_environment_net	&m_env; //Temp have to be replace with a evaluator
		size_t						m_cur_people_alive;
		s_species_var				m_species_var;
		vector<s_species>			m_species;
		double						m_total_species_fitness;
};

inline int		get_new_innov_number()
{
	static int	m_cur_innov_number = 1;
	return (m_cur_innov_number++);
}
