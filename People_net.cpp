/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_net.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 00:59:30 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/11 20:41:25 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_net.h"

using namespace std;

void					People_net::set_score(int score)
{
	do_set_score(score);
}

int						People_net::get_score(void) const
{
	return (do_get_score());
}

int						People_net::get_answer(void)
{
	return (do_get_answer());
}

const vector<double>&	People_net::calc_output(const vector<double> &input)
{
	return (do_calc_output(input));
}
