/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_basic_mlp.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:56:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 20:11:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "People_net.h"
#include <vector>

class	People_basic_mlp: public People_net
{
	public:
		People_basic_mlp();

	private:
		void					do_set_score(int score);
		int						do_get_score(void);
		int						do_get_answer(void);
		const vector<double>&	do_calc_output(const vector<double> &input);

		int		m_score = 0;
};
