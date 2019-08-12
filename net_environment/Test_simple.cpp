/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/11 22:55:29 by trobicho         ###   ########.fr       */
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
	int	score = 0;
	int	r;
	std::vector<int>	grid;

	grid.resize(m_max * m_max, 0);
	m_pos.x = m_max / 2;
	m_pos.y = m_max / 2;
	r = 0;
	for (step = 0; step < 2600; step++)
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
		if (grid[m_pos.x + m_pos.y * m_max] == 0)
			score++;
		else
			score--;
		grid[m_pos.x + m_pos.y * m_max]++;
	}
	people.set_score(score);
	return (score);
}


int	Test_simple::do_get_nb_output(void)
{
	return (4);
}

int	Test_simple::do_get_nb_input(void)
{
	return (2);
}
