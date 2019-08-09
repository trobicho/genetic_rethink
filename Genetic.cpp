/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 00:49:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 01:01:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Genetic.h"

int		Genetic::get_generation(void)
{
	return (do_get_generation());
}

int		Genetic::get_best_score(void)
{
	return (do_get_best_score());
}

void	Genetic::next_gen(void)
{
	next_gen();
}
