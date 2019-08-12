/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 04:14:37 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Layer.h"
#include "People_basic_mlp.h"
#include "my_lib.h"

People_basic_mlp::People_basic_mlp(int nb_input, int nb_output):
	NeuralNet(nb_input, nb_output)
{
	init();
	m_nb_total_neuron = 0;
	std::list<Layer>::iterator it=m_layer.begin();

	for(int i=1; i<m_nbLayer && it!=m_layer.end(); ++i, ++it)
	{
		m_nb_total_neuron += it->get_nbNeuron();
	}
}

void		People_basic_mlp::do_set_score(int score)
{
	m_score = score;
}

int			People_basic_mlp::do_get_score(void) const
{
	return (m_score);
}

int			People_basic_mlp::do_get_answer(void)
{
	return (answer());
}

const vector<double>&
			People_basic_mlp::do_calc_output(const vector<double> &input)
{
	calc(input);
	return (m_layer.back().get_result());
}

s_neuron&	People_basic_mlp::get_neuron_n_ref(int n)
{
	std::list<Layer>::iterator it=m_layer.begin();

	for (;it!=m_layer.end(); ++it)
	{
		if (n < it->get_nbNeuron())
			return (it->get_neuron_at_n(n));
		n -= it->get_nbNeuron();
	}
}

void		People_basic_mlp::mutate(void)
{
	int			neuron_index = trl::rand_uniform_int(0, m_nb_total_neuron);
	s_neuron	&neuron = get_neuron_n_ref(neuron_index);
	int			neuron_weight_index;

	neuron_weight_index = trl::rand_uniform_int(0, m_nb_total_neuron);
	neuron.weight[neuron_weight_index] *= trl::rand_uniform_double(0.75, 1.5);
}
