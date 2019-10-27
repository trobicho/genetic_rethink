/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 01:03:50 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:04:56 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Learning_environment.h"

double	Learning_environment::evaluate(People &people, int generation)
{
	return (do_evalutation(people, generation));
}
