/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment_net.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 01:05:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 15:50:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Learning_environment_net.h"

int	Learning_environment_net::evaluate(People_net &people, int generation)
{
	return (do_evalutation(people, generation));
}

int	Learning_environment_net::get_nb_input(void)
{
	return (do_get_nb_input());
}

int	Learning_environment_net::get_nb_output(void)
{
	return (do_get_nb_output());
}
