/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/13 06:02:50 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_net.h"
#include "NeuralNet.h"
#include <vector>

class	People_basic_mlp: public People_net, private NeuralNet
{
	public:
		People_basic_mlp(int nb_input, int nb_output);
		void	mutate();
		void	copy_weight_same_net(People_basic_mlp &people);

	private:
		void					do_set_score(int score);
		int						do_get_score(void) const;
		int						do_get_answer(void);
		const vector<double>&	do_calc_output(const vector<double> &input);
		s_neuron&				get_neuron_n_ref(int n);
		void					mutate_swap_same_layer(void);
		void					mutate_mul(void);
		void					mutate_add(void);

		int	m_score = 0;
		int	m_nb_total_neuron;
};
