/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 23:56:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test_simple.h"

Test_simple::Test_simple(int max): m_max(max)
{
	m_sensor.resize(get_nb_input());
	m_grid.resize(m_max * m_max, 0);
}

int		Test_simple::eval_and_display(People_net &people, int generation)
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
		if (m_extra_sensor)
			extra_sensor_update();
		else
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

void	Test_simple::extra_sensor_update(void)
{
	int x, y;

	for (x = m_pos.x + 1, y = m_pos.y; x < m_max; x++)
	{
		if (m_grid[x + y * m_max] > 0)
			break;
	}
	m_sensor[2] = (x - m_pos.x);
	for (x = m_pos.x, y = m_pos.y + 1; y < m_max; y++)
	{
		if (m_grid[x + y * m_max] > 0)
			break;
	}
	m_sensor[3] = (y - m_pos.y);
	for (x = m_pos.x - 1, y = m_pos.y; x >= 0; x--)
	{
		if (m_grid[x + y * m_max] > 0)
			break;
	}
	m_sensor[4] = (m_pos.x - x);
	for (x = m_pos.x, y = m_pos.y - 1; y >= 0; y--)
	{
		if (m_grid[x + y * m_max] > 0)
			break;
	}
	m_sensor[5] = (m_pos.y - y);
}

int		Test_simple::do_get_nb_output(void)
{
	return (4);
}

int		Test_simple::do_get_nb_input(void)
{
	if (m_extra_sensor)
		return (6);
	else
		return (3);
}
