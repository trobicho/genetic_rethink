/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/13 21:45:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_net.h"
#include <vector>

typedef struct	s_node_gene
{
	int		layer;
	double	in;
	int		nb_until_finish;
}				t_node_gene;

typedef struct	s_connection_gene
{
	int		node_in;
	int		node_out;
	double	weight;
	bool	enabled;
	int		innov;
	bool	done;
}				t_connection_gene;

using namespace std;

class	People_neat: public People_net
{
	public:
		People_neat(int nb_input, int nb_output);
		void	mutate_weight(void);
		void	mutate_add_node(void);
		void	mutate_add_connection(void);

	private:
		void					do_set_score(int score);
		int						do_get_score(void) const;
		int						do_get_answer(void);
		const vector<double>&	do_calc_output(const vector<double> &input);
		t_connection_gene&		add_connection(int node_in, int node_out, bool enabled);

		vector<t_node_gene>			m_node_gene;
		vector<t_connection_gene>	m_connec_gene;
		vector<double>				m_result;
		int							m_score;
		int							m_nb_input, m_nb_output;
};
