/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test_simple.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:10:19 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/11 17:07:04 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libgen.h"
#include "People_net.h"

typedef struct	s_pos
{
	int	x, y;
}				t_pos;

using namespace std;

class	Test_simple: public Learning_environment_net
{
	public:
		Test_simple(int max = 25);
		~Test_simple(){};

	private:
		int	do_evalutation(People_net &people, int generation);
		int	do_get_nb_output(void);
		int	do_get_nb_input(void);

		int				m_max;
		t_pos			m_pos;
		vector<double>	m_sensor;
};
