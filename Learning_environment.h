/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:50:45 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:05:11 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People.h"

class	Learning_environment
{
	public:
		double	evaluate(People &people, int generation = -1);

	private:
		virtual double	do_evalutation(People &people, int generation) = 0;
};
