/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 20:22:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test_simple.h"

Test_simple::Test_simple(int max): m_max(max)
{
	m_sensor.resize(get_nb_input());
	m_grid.resize(m_max * m_max, 0);
}

int	Test_simple::eval_and_display(People_net &people, int generation)
{
	do_evalutation(people, generation);
	for (int i = 0; i < m_max * m_max; i++)
	{
		if (i > 0 && i % m_max == 0)
			std::cout << std::endl;
		if (m_grid[i] == 0)
			std::cout << ". ";
		else if (m_grid[i] < 10)
			std::cout << m_grid[i] << " ";
		else
			std::cout << "x ";
	}
	std::cout << std::endl;
}

int	Test_simple::do_evalutation(People_net &people, int generation)
{
	int	step;
	int	score = 0;
	int	r;

	for (int i = 0; i < m_max * m_max; i++)
	{
		m_grid[i] = 0;
	}
	m_pos.x = m_max / 2;
	m_pos.y = m_max / 2;
	if (m_grid[m_pos.x + m_pos.y * m_max] == 0)
		score += 2;
	m_grid[m_pos.x + m_pos.y * m_max] += 1;
	r = 0;
	for (step = 0; step < m_max * m_max + m_max * 2; step++)
	{
		m_sensor[0] = (double)m_pos.x / (double)m_max;
		m_sensor[1] = (double)m_pos.y / (double)m_max;
		m_sensor[2] = (double)step / (double)(m_max * m_max);
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
		if (m_grid[m_pos.x + m_pos.y * m_max] == 0)
			score+=2;
		else
			score--;
		m_grid[m_pos.x + m_pos.y * m_max] += 1;
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
	return (3);
}
