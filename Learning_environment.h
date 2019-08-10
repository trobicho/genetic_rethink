/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:50:45 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 15:43:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People.h"

class	Learning_environment
{
	public:
		int	evaluate(People &people, int generation = -1);

	private:
		virtual int	do_evalutation(People &people, int generation) = 0;
};
