/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat_handler.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:44:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/23 18:53:05 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_neat.h"

class People_neat_handler
{
	public:
		virtual int		set_new_innov_number(s_connec_gene &connec) = 0;
		virtual int		get_nb_input() = 0;		//?
		virtual int		get_nb_output() = 0;	//?
}
