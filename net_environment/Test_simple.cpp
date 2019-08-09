/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 01:20:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Test_simple::Test_simple(int max): m_max(max)
{
	sensor.resize(2);
}

int	Test_simple::do_evalutation(People_net &people, int generation)
{
	int	step;
	int	r;

	m_pos.x = max / 2;
	m_pos.y = max / 2;
	for (step = 0; step < 1000; step++)
	{
		sensor[0] = m_pos.x / (double)max;
		sensor[1] = m_pos.y / (double)max;
		people.calc(sensor);
		r = people.get_answer();
		switch (r)
		{
			case 0:
				pos.x--;
				break;
			case 1:
				pos.x++;
				break;
			case 2:
				pos.y--;
				break;
			case 3:
				pos.y++;
				break;
		}
		if (pos.x < 0 || pos.x >= max || pos.y < 0 || pos.y >= max)
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
	return (3);
}
