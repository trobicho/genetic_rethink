/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xor.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 01:25:26 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:51:52 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Xor.h"
#include <iostream>
#include <unistd.h>
#include <cmath>

using namespace std;

Xor::Xor()
{
	m_sensor.resize(get_nb_input());
	m_fail.resize(4, 0);
}

double	Xor::do_evalutation(People_net &people, int generation)
{
	double	score = 0;
	double	expect;
	int		cur_total_fail = 0;

	for (int i = 0; i < 4; i++)
	{
		m_sensor[0] = (double)(i % 2);
		m_sensor[1] = (double)(i / 2);
		if (m_sensor.size() == 3)
			m_sensor[3] = 1.0;
		auto& out = people.calc_output(m_sensor);
		if (((i % 2) ^ (i / 2)))
			expect = 1.0;
		else
			expect = 0.0;
		double	add = expect - (double)out[0];
		if (add < 0)
			add = -add;
		if (add > 0.5)
		{
			cur_total_fail++;
			m_fail[i]++;
		}
		score += add;
	}
	if (cur_total_fail == 0)
		std::cout << "WHOOOOAAAA!!!!!" << std::endl;
	return (4.0 - score);
}

void	Xor::test()
{
	for (int i = 0; i < 4; i++)
	{
		m_sensor[0] = (double)(i % 2);
		m_sensor[1] = (double)(i / 2);
		if (((i % 2) ^ (i / 2)))
			cout << "true : " << m_sensor[0] << ", " << m_sensor[1] << endl;
		else
			cout << "false : " << m_sensor[0] << ", " << m_sensor[1] << endl;
	}
}

void	Xor::fail()
{
	for (int i = 0; i < 4; i++)
	{
		m_sensor[0] = (double)(i % 2);
		m_sensor[1] = (double)(i / 2);
		if (((i % 2) ^ (i / 2)))
		{
			cout << "true : " << m_sensor[0] << ", " << m_sensor[1] << " fails: "<< m_fail[i] <<endl;
		}
		else if ((!((i % 2) ^ (i / 2))))
			cout << "false : " << m_sensor[0] << ", " << m_sensor[1] << " fails: " << m_fail[i] << endl;
	}
}
