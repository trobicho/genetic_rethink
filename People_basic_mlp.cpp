/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/12 20:50:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Layer.h"
#include "People_basic_mlp.h"
#include "my_lib.h"

#include <iostream>

People_basic_mlp::People_basic_mlp(int nb_input, int nb_output):
	NeuralNet(nb_input, nb_output)
{

	addLayerFront(Layer(4));
	init();
	m_nb_total_neuron = 0;
	std::list<Layer>::iterator it=m_layer.begin();

	for(; it!=m_layer.end(); ++it)
	{
		m_nb_total_neuron += it->get_nbNeuron();
	}
}

void		People_basic_mlp::copy_weight_same_net(People_basic_mlp &people)
{
	int			nb_neuron;

	std::list<Layer>::iterator it=m_layer.begin();
	std::list<Layer>::iterator it_copy=people.m_layer.begin();
	for (; it != m_layer.end() && it_copy != people.m_layer.end(); ++it, ++it_copy)
	{
		nb_neuron = it->get_nbNeuron();
		for (int n = 0; n < nb_neuron; n++)
		{
			s_neuron	&neuron = it->get_neuron_at_n(n);
			neuron = it_copy->get_neuron_at_n(n);
		}
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
	it--;
	return (it->get_neuron_at_n(0));
}

void		People_basic_mlp::mutate(void)
{
	int			neuron_index = trl::rand_uniform_int(0, m_nb_total_neuron - 1);
	s_neuron	&neuron = get_neuron_n_ref(neuron_index);
	int			neuron_weight_index;

	neuron_weight_index = trl::rand_uniform_int(0, neuron.weight.size() - 1);
	neuron.weight[neuron_weight_index] += trl::rand_uniform_double(-1.0, 1.0);
}
