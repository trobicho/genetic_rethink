/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_net.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:30:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 03:58:08 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

using namespace std;

class	People_net
{
	public:
		People_net(){};
		void					set_score(double score);
		double					get_score(void)const;
		int						get_answer();
		const vector<double>&	calc_output(const vector<double> &input);

		friend bool operator< (const People_net &p1, const People_net &p2);
		friend bool operator> (const People_net &p1, const People_net &p2);
		friend bool operator<=(const People_net &p1, const People_net &p2);
		friend bool operator>=(const People_net &p1, const People_net &p2);
		friend bool operator==(const People_net &p1, const People_net &p2);
		friend bool operator!=(const People_net &p1, const People_net &p2);

	private:
		virtual void	do_set_score(double score) = 0;
		virtual double	do_get_score(void) const = 0;
		virtual int		do_get_answer(void) = 0;
		virtual const vector<double>&
						do_calc_output(const vector<double> &input) = 0;
};

inline bool				operator< (const People_net &p1, const People_net &p2)
{
	return (p1.get_score() < p2.get_score());
}

inline bool				operator> (const People_net &p1, const People_net &p2)
{
	return (p1.get_score() > p2.get_score());
}

inline bool				operator<=(const People_net &p1, const People_net &p2)
{
	return (!(p1 > p2));
}

inline bool				operator>=(const People_net &p1, const People_net &p2)
{
	return (!(p1 < p2));
}

inline bool				operator==(const People_net &p1, const People_net &p2)
{
	return (!(p1.get_score() == p2.get_score()));
}

inline bool				operator!=(const People_net &p1, const People_net &p2)
{
	return (!(p1 == p2));
}
