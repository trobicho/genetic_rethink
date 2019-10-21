/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:58 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/20 23:38:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_neat.h"
#include "my_lib.h"
#include <algorithm>
#include <iostream>

People_neat::People_neat(int nb_input, int nb_output
	, int (*get_new_innov)(void)): m_nb_input(nb_input), m_nb_output(nb_output)
	, m_get_new_innov_number(get_new_innov)
{
	auto	&mt = trl::req_mt_ref();
	std::uniform_real_distribution<double>
			dis(-1, 1);

	m_result.resize(nb_output);
	m_node_gene.resize(nb_input + nb_output);
	m_connec_gene.resize(nb_input * nb_output);
	for (int o = 0; o < nb_output; o++)
	{
		m_node_gene[nb_input + o].layer = 2;
		m_node_gene[nb_input + o].rank = 0;
		for (int i = 0; i < nb_input; i++)
		{
			m_connec_gene[o * nb_input + i].node_in = i;
			m_connec_gene[o * nb_input + i].node_out = o + nb_input;
			m_connec_gene[o * nb_input + i].enabled = true;
			m_connec_gene[o * nb_input + i].weight = dis(mt);
		}
	}
}

void		People_neat::do_set_score(int score)
{
	m_score = score;
}

int			People_neat::do_get_score(void) const
{
	return (m_score);
}

int			People_neat::do_get_answer(void)
{
	double	max = m_result[0];
	int		curMax = 0;

	for(int i = 1; i < m_result.size(); i++)
	{
		if (m_result[i] > max)
		{
			max = m_result[i];
			curMax = i;
		}
	}
	return (curMax);
}

const vector<double>&
		People_neat::do_calc_output(const vector<double> &input)
{
	double	r;
	bool	finish = false;

	for(int n=0; n<m_node_gene.size(); n++)
	{
		if (m_node_gene[n].layer == 0)
		{
			m_node_gene[n].in = input[n];
			m_node_gene[n].nb_until_finish = 0;
		}
		else
		{
			m_node_gene[n].in = 0.0;
			m_node_gene[n].nb_until_finish = 0;
		}
	}
	for(int c=0; c < m_connec_gene.size(); c++)
	{
		if (m_connec_gene[c].enabled == true)
		{
			m_connec_gene[c].done = false;
			m_node_gene[m_connec_gene[c].node_out].nb_until_finish++;
		}
	}
	while (finish == false)
	{
		finish = true;
		for(int c=0; c < m_connec_gene.size(); c++)
		{
			if (m_connec_gene[c].done == false && m_connec_gene[c].enabled)
			{
				int	in = m_connec_gene[c].node_in;
				int	out = m_connec_gene[c].node_out;
				if (m_node_gene[in].nb_until_finish <= 0)
				{
					m_node_gene[out].in += m_node_gene[in].in * m_connec_gene[c].weight;
					m_node_gene[out].nb_until_finish--;
				}
				else
					finish = false;
			}
		}
	}
	int	res = 0;
	for(int n=0; n<m_node_gene.size(); n++)
	{
		if (m_node_gene[n].layer == 2)
			m_result[res++] = m_node_gene[n].in;
	}
	return (m_result);
}

void	People_neat::mating(People_neat &p1, People_neat &p2)
{
	People_neat	&tmp;

	if (p2.get_score() > p1.get_score()) 
	{
		tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	m_node_gene.assign(p1.m_node_gene.begin(), p1.m_node_gene.end());
	m_connec_gene.assign(p1.m_connec_gene.begin(), p1.m_connec_gene.end());
}

void	People_neat::mutate_weight(void)
{
	int	index = trl::rand_uniform_int(0, m_connec_gene.size() - 1);

	m_connec_gene[index].weight += trl::rand_uniform_double(-0.5, 0.5);
	m_connec_gene[trl::rand_uniform_int(0, m_connec_gene.size() - 1)].weight
		+= trl::rand_uniform_double(-0.5, 0.5);
	m_connec_gene[trl::rand_uniform_int(0, m_connec_gene.size() - 1)].weight
		+= trl::rand_uniform_double(-0.5, 0.5);
	m_connec_gene[trl::rand_uniform_int(0, m_connec_gene.size() - 1)].weight
		+= trl::rand_uniform_double(-0.5, 0.5);
	m_connec_gene[trl::rand_uniform_int(0, m_connec_gene.size() - 1)].weight
		+= trl::rand_uniform_double(-0.5, 0.5);
}

void	People_neat::mutate_add_node(void)
{
	int		r;
	auto	&mt = trl::req_mt_ref();
	std::uniform_int_distribution<int>
		dis(0, m_connec_gene.size() - 1); // -1 ?

	for (int i = 0; i < 10; i++)
	{
		r = dis(mt);
		if (m_connec_gene[r].enabled)
			break;
	}
	if (m_connec_gene[r].enabled)
	{
		s_node_gene			node;
		s_connection_gene	connec;
		/*
		node.layer = m_node_gene[m_connec_gene[r].node_in].layer + 1;
		if (m_node_gene[m_connec_gene[r].node_out].layer
			> m_node_gene[m_connec_gene[r].node_in].layer)
			node.layer = m_node_gene[m_connec_gene[r].node_out].layer - 1;
		*/
		node.layer = 1;
		node.rank = m_node_gene[m_connec_gene[r].node_in].rank + 1;
		m_node_gene.push_back(node);
		add_connection(m_connec_gene[r].node_in, m_node_gene.size() - 1, true);
		m_connec_gene.back().weight = m_connec_gene[r].weight;
		add_connection(m_connec_gene.back().node_out, m_connec_gene[r].node_out, true);
		m_connec_gene[r].enabled = false;
		node_sort();
	}
}

void	People_neat::mutate_add_connection(void)
{
	int	node_in;
	int	node_out;

	node_in = trl::rand_uniform_int(0, (m_node_gene.size() - 1) - m_nb_output);
	if (node_in >= m_nb_input)
	{
		node_in += m_nb_output;
		node_out = trl::rand_uniform_int(get_node_idx(node_in) + 1
			, m_node_idx.size() + m_nb_output - 1);
		if (node_out >= m_node_idx.size())
			node_out -= (m_node_idx.size() - m_nb_input);
		else
			node_out = m_node_idx[node_out];
	}
	else
	{
		node_out = trl::rand_uniform_int(m_nb_input, m_node_gene.size() - 1);
	}
	//node_out = trl::rand_uniform_int(0, m_nb_output - 1) + m_nb_input;
	add_connection(node_in, node_out, true);
}

s_connection_gene&
	People_neat::add_connection(int node_in, int node_out, bool enabled)
{
	s_connection_gene	connec;

	connec.node_in = node_in;
	connec.node_out = node_out;
	connec.enabled = enabled;
	m_connec_gene.push_back(connec);
	if (m_node_gene[node_in].rank + 1 > m_node_gene[node_out].rank)
	{
		m_node_gene[node_out].rank = m_node_gene[node_in].rank + 1;
		node_sort();
	}
	m_connec_gene.back().weight = 1.0;
	m_connec_gene.back().innov = m_get_new_innov_number();
	return (m_connec_gene.back());
}

void	People_neat::node_sort()
{
	size_t	node1;
	size_t	node2;

	if (m_node_gene.size() > m_nb_input + m_nb_output)
	{
		size_t	nb_base_node = m_nb_input + m_nb_output;
		m_node_idx.resize(m_node_gene.size() - nb_base_node);
		iota(m_node_idx.begin(), m_node_idx.end(), nb_base_node);
		sort(m_node_idx.begin(), m_node_idx.end(), [&m_node_gene = m_node_gene]
			(size_t i1, size_t i2) {return m_node_gene[i1] < m_node_gene[i2];});
	}
}

size_t	People_neat::get_node_idx(size_t node)
{
	for (int i = 0; i < m_node_idx.size(); i++)
	{
		if (m_node_idx[i] == node)
			return (i);
	}
	return (0);
}

void	People_neat::debug_people_test()
{
	std::cout << "people bug!!" << std::endl;
}
