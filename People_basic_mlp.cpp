/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 20:16:56 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_basic_mlp.h"

People_basic_mlp::People_basic_mlp()
{
}

void	People_basic_mlp::do_set_score(int score)
{
	m_score = score;
}

int		People_basic_mlp::do_get_score(void)
{
	return (m_score);
}

int		People_basic_mlp::do_get_answer(void)
{
}

const vector<double>&
		People_basic_mlp::do_calc_output(const vector<double> &input)
{
}
