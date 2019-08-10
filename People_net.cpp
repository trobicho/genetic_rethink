/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_net.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 00:59:30 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 01:01:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_net.h"

void					set_score(int score);
{
	do_set_score(score);
}

int						get_score(void);
{
	return (do_get_score());
}

const vector<double>&	calc_output(const vector<double> &input);
{
	return (do_calc_output(input));
}