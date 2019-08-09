/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 18:28:54 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Test_simple(int max): m_max(max)
{
}

int		do_evalutation(People_net &people, int generation);
{
	do_evalutation();
}

int		do_evalutation(People_net &people);
{
	int					step;
	std::vector<double>	sensor;

	m_pos.x = max / 2;
	m_pos.y = max / 2;
	for (step = 0; step < 1000; step++)
	{
		sensor[0] = m_pos.x / max;
		sensor[1] = m_pos.y / max;
		std::vector<double>	&result = people->calc(sensor);
	}
}


int		do_get_nb_output(void);
{
	return (2);
}

int		do_get_nb_input(void);
{
	return (2);
}
