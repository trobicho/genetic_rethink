/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_net_basic_mlp.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 00:52:37 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 01:01:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Genetic_net_basic_mlp.h"

int		Genetic_net_basic_mlp::do_get_generation(void)
{
	return (m_generation);
}
int		Genetic_net_basic_mlp::do_get_best_score(void)
{
	return (m_people[0].get_score());
}

void	Genetic_net_basic_mlp::do_next_gen(void)
{
}