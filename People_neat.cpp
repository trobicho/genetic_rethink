/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:58 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/16 22:28:10 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_neat.h"
#include "my_lib.h"

People_neat(int nb_input, int nb_output)
{
	auto	mt = trl::req_mt_ref();
	std::uniform_real_distribution<double>
			dis(-1, 1);

	m_result.resize(nb_output);
	m_node_gene.resize(nb_input + nb_output);
	m_connec_gene.resize(nb_input * nb_output);
	for (int o = 0; o < nb_output; o++)
	{
		for (int i = 0; i < nb_input; i++)
		{
			m_connec_gene[o * nb_input + i].node_in = i;
			m_connec_gene[o * nb_input + i].node_out = o;
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
	return (answer());
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
		m_connec_gene[c].done = false;
		m_node_gene[m_connec_gene[c].out].nb_until_finish++;
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
	int	r = 0;
	for(int n=0; n<m_node_gene.size(); n++)
	{
		if (m_node_gene[n].layer == 2)
			m_result[r++] = m_node_gene[n].in;
	}
}

void	People_neat::mutate_weight(void)
{
	int	index = trl::rand_uniform_int(0, m_connec_gene.size());

	m_connec_gene[index].weight += trl::rand_uniform_double(-0.5, 0.5);
}

void	People_neat::mutate_add_node(void)
{
	int		r;
	auto	mt = trl::req_mt_ref();
	std::uniform_int_distribution<int>
		dis(0, m_connec_gene.size());

	for (int i = 0; i < 10; i++)
	{
		r = dis(mt);
		if (m_connec_gene[r].enabled)
			break;
	}
	if (m_connec_gene[r].enabled)
	{
		t_node_gene			node;
		t_connection_gene	connec;
		/*
		node.layer = m_node_gene[m_connec_gene[r].node_in].layer + 1;
		if (m_node_gene[m_connec_gene[r].node_out].layer
			> m_node_gene[m_connec_gene[r].node_in].layer)
			node.layer = m_node_gene[m_connec_gene[r].node_out].layer - 1;
		*/
		node.layer = 1;
		m_node_gene.push_back(node);
		m_connec_gene.push_back(m_connec_gene[r]);
		m_connec_gene.back().node_out = m_node_gene.size() - 1;
		m_connec_gene.back().innov = 2;//get_new_innovation_number();
		m_connec_gene[r].enabled = false;
	}
}

t_connection_gene&
	People_neat::add_connection(int node_in, int node_out, bool enabled)
{
	t_connection_gene	connec;

	m_connec_gene.push_back(connec);
}