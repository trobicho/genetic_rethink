/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/31 12:16:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_neat_handler.h"
#include "People_net.h"
#include <vector>

struct	s_node_gene
{
	int		layer;
	double	in;
	int		nb_until_finish;
	int		rank;

	bool	operator< (const s_node_gene &n) const
	{
		return (rank < n.rank);
	}
	bool	operator> ( const s_node_gene &n) const
	{
		return (rank > n.rank);
	}
	bool	operator<=( const s_node_gene &n) const
	{
		return (rank <= n.rank);
	}
	bool	operator>=(const s_node_gene &n) const
	{
		return (rank >= n.rank);
	}
	bool	operator==(const s_node_gene &n) const
	{
		return (rank == n.rank);
	}
};

using namespace std;

class	People_neat: public People_net
{
	public:
		People_neat(){};
		People_neat(int nb_input, int nb_output, People_neat_handler *handler);
		void	copy_gene(People_neat &people);
		void	mutate_weight_mul(void);
		void	mutate_weight_add(void);
		void	mutate_weight_full_rand(void);
		void	mutate_add_node(void);
		void	mutate_add_connection(void);
		void	mating(People_neat &p1, People_neat &p2);
		int		choose_rand_enabled_connec(void);

		void	set_sharing_score(double sharing_score)
			{m_sharing_score = sharing_score;}
		double	get_sharing_score(){return (m_sharing_score);}
		void	set_species(int species){m_species = species;}
		int		get_species(){return (m_species);}
		size_t	get_nb_input_node(){return (m_nb_input);}
		size_t	get_nb_output_node(){return (m_nb_output);}
		size_t	get_node_idx(size_t node);
		vector<s_node_gene>&		get_node_gene_ref()
			{return (m_node_gene);}
		vector<size_t>&				get_node_idx_ref()
			{return (m_node_idx);}
		vector<s_connection_gene>&	get_connection_gene_ref()
			{return (m_connec_gene);}
		static double				get_delta_dist(
			People_neat &p1, People_neat &p2, double c1, double c2, double c3);

	private:
		void					do_set_score(double score);
		double					do_get_score(void) const;
		int						do_get_answer(void);
		const vector<double>&	do_calc_output(const vector<double> &input);
		s_connection_gene&		add_connection(int node_in, int node_out
			, bool enabled = true);
		void					debug_people_test();
		void					node_sort();
		void					node_rerank(int index);
		void					swap_node(size_t n1, size_t n2);

		vector<s_node_gene>			m_node_gene;
		vector<s_connection_gene>	m_connec_gene;
		vector<double>				m_result;
		vector<size_t>				m_node_idx;
		double						m_score;
		double						m_sharing_score;
		size_t						m_nb_input, m_nb_output;
		int							m_species;
		People_neat_handler			*m_handler;
};
