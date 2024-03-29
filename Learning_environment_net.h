/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment_net.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:55:21 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:06:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_net.h"

class	Learning_environment_net
{
	public:
		Learning_environment_net(){};
		double	evaluate(People_net &people, int generation = -1);
		int		get_nb_output(void);
		int		get_nb_input(void);

	private:
		virtual double	do_evalutation(People_net &people, int generation) = 0; //const People
		virtual int		do_get_nb_input(void) = 0;
		virtual int		do_get_nb_output(void) = 0;
};
