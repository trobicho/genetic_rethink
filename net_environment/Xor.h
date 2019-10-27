/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xor.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 01:19:02 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:45:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libgen.h"
#include "People_net.h"
#include <vector>

using namespace std;

class Xor : public Learning_environment_net
{
	public :
		Xor();
		~Xor(){};

		void	test();
		void	fail();

	private:
		double	do_evalutation(People_net &people, int generation);
		int		do_get_nb_output(void){return (1);}
		int		do_get_nb_input(void){return (3);}

		vector<double>	m_sensor;
		vector<size_t>	m_fail;
};
