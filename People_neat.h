/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/18 17:46:39 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

struct	s_connection_gene
{
	int		node_in;
	int		node_out;
	double	weight;
	bool	enabled;
	int		innov;
	bool	done;
};

using namespace std;

class	People_neat: public People_net
{
	public:
		People_neat(int nb_input, int nb_output, int (*get_new_innov)(void));
		void	mutate_weight(void);
		void	mutate_add_node(void);
		void	mutate_add_connection(void);
		void	mating(People_neat &p1, People_neat &p2);

		size_t	get_nb_input_node(){return (m_nb_input);}
		size_t	get_nb_output_node(){return (m_nb_output);}
		vector<s_node_gene>&		get_node_gene_ref()
			{return (m_node_gene);}
		vector<s_connection_gene>&	get_connection_gene_ref()
			{return (m_connec_gene);}

	private:
		void					do_set_score(int score);
		int						do_get_score(void) const;
		int						do_get_answer(void);
		const vector<double>&	do_calc_output(const vector<double> &input);
		s_connection_gene&		add_connection(int node_in, int node_out, bool enabled);
		void					debug_people_test();
		void					node_sort();
		void					swap_node(size_t n1, size_t n2);

		vector<s_node_gene>			m_node_gene;
		vector<s_connection_gene>	m_connec_gene;
		vector<double>				m_result;
		int							m_score;
		size_t						m_nb_input, m_nb_output;
		int							(*m_get_new_innov_number)(void);
};
