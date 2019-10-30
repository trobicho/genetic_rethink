/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat_handler.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:36:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/28 00:55:33 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_neat_handler.h"

People_neat_handler::People_neat_handler(int reserve)
{
	m_innov_connec.reserve(reserve);
}

void	People_neat_handler::flush_innov(void)
{
	m_innov_connec.clear();
}

int		People_neat_handler::set_new_innov_number(s_connection_gene &connec)
{
	for (auto it = m_innov_connec.begin(); it != m_innov_connec.end(); ++it)
	{
		if (it->node_in == connec.node_in && it->node_out == connec.node_out)
		{
			connec.innov = it->innov;
			return (it->innov);
		}
	}
	connec.innov = m_cur_innov_number++;
	m_innov_connec.push_back(connec);
	return (m_cur_innov_number);
}
