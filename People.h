/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:22:09 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 21:19:42 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
class	People
{
	public:
		People(){};
		void	set_score(int score);
		int		get_score(void);
		T		get_gene(void);

	private:
		virtual	void	do_set_score(int score) = 0;
		virtual int		do_get_score(void) = 0;
		virtual	T		do_get_gene(void) = 0;
}
