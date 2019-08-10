/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_net.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:30:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/10 14:04:16 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

using namespace std;

class	People_net
{
	public:
		People_net(){};
		void					set_score(int score);
		int						get_score(void);
		int						get_answer();
		const vector<double>&	calc_output(const vector<double> &input);


	private:
		virtual void	do_set_score(int score) = 0;
		virtual int		do_get_score(void) = 0;
		int				do_get_answer();
		virtual const vector<double>&
						do_calc_output(const vector<double> &input) = 0;
};
