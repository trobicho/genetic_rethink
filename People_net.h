/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_net.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:30:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 18:33:51 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

using namespace std;

class	People_net
{
	public:
		People_net(){};
		void					set_score(double score);
		double					get_score(void);
		const vector<double>&	calc_output(const vector<double> &input);


	private:
		virtual void	do_set_score(double score) = 0;
		virtual double	do_get_score(void) = 0;
}
