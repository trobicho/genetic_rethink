/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 19:50:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test_simple.h"

Test_simple::Test_simple(int max): m_max(max)
{
	m_sensor.resize(2);
}

int	Test_simple::do_evalutation(People_net &people, int generation)
{
	int	step;
	int	r;

	m_pos.x = m_max / 2;
	m_pos.y = m_max / 2;
	for (step = 0; step < 1000; step++)
	{
		m_sensor[0] = m_pos.x / (double)m_max;
		m_sensor[1] = m_pos.y / (double)m_max;
		people.calc_output(m_sensor);
		r = people.get_answer();
		switch (r)
		{
			case 0:
				m_pos.x--;
				break;
			case 1:
				m_pos.x++;
				break;
			case 2:
				m_pos.y--;
				break;
			case 3:
				m_pos.y++;
				break;
		}
		if (m_pos.x < 0 || m_pos.x >= m_max || m_pos.y < 0 || m_pos.y >= m_max)
			break;
	}
	return (step);
}


int	Test_simple::do_get_nb_output(void)
{
	return (4);
}

int	Test_simple::do_get_nb_input(void)
{
	return (2);
}
