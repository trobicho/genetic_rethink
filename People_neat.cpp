/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:25:58 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/15 14:49:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_neat.h"

People_neat(int nb_input, int nb_output)
{
	m_node_gene().resize(nb_input + nb_output);
}

const vector<double>&
		People_neat::do_calc_output(const vector<double> &input)
{
	double	r;
	bool	finish = false;

	for(int n=0; n<m_node_gene->size(); n++)
	{
		if (m_node_gene[i].layer == 0)
		{
			m_node_gene[n].in = (double)input[n];
			m_node_gene[n].calc_finish = true;
		}
		else
		{
			m_node_gene[n].in = 0.0;
			m_node_gene[n].nb_until_finish = 0;
		}
	}
	for(int c=0; c < m_connec_gene->size(); c++)
	{
		m_connec_gene[c].done = false;
		m_node_gene[m_connec_gene[c].out].nb_until_finish++;
	}
	while (finish == false)
	{
		finish = true;
		for(int c=0; c < m_connec_gene->size(); c++)
		{
			if (m_connec_gene[c].done == false && m_connec_gene[c].enabled)
			{
				int	in = m_connec_gene[c].in;
				int	out = m_connec_gene[c].out;
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
	for(int n=0; n<m_node_gene->size(); n++)
	{
		if (m_node_gene[n].layer == 2)
			m_result[r++] = m_node_gene[n].in;
	}
}

void	People_neat::mutate_add_node(void)
{
	int r;

	while (int i = 0; i < 10; i++)
	{
		r = randMinMax(0, m_connec_gene->size);
		if (m_connec_gene[r].enabled)
			break;
	}
	if (m_connec_gene[r].enabled)
	{
		t_node	node;
		/*
		node.layer = m_node_gene[m_connec_gene[r].node_in].layer + 1;
		if (m_node_gene[m_connec_gene[r].node_out].layer
			> m_node_gene[m_connec_gene[r].node_in].layer)
			node.layer = m_node_gene[m_connec_gene[r].node_out].layer - 1;
		*/
		node.layer = 1;
		m_node_gene.push_back();
		m_connec_gene[r].enabled = false;
		m_connec_gene.push_back();
		m_connec_gene.back() = m_connec_gene[r];
		m_connec_gene.back().out = m_node_gene.size() - 1;
		m_connec_gene.back().innov = get_new_innovation_number();
	}
}
