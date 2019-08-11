/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/11 20:05:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "People_basic_mlp.h"

People_basic_mlp::People_basic_mlp(int nb_input, int nb_output):
	NeuralNet(nb_input, nb_output)
{
	init();
}

void	People_basic_mlp::do_set_score(int score)
{
	m_score = score;
}

int		People_basic_mlp::do_get_score(void) const
{
	return (m_score);
}

int		People_basic_mlp::do_get_answer(void)
{
	return (answer());
}

const vector<double>&
		People_basic_mlp::do_calc_output(const vector<double> &input)
{
	calc(input);
	return (m_layer.back().get_result());
}
