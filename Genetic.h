/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:20:05 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 21:18:43 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	Genetic
{
	public:
		Genetic(){};
		int		get_generation(void);
		int		get_best_score(void);
		void	next_gen(void);
	
	private:
		virtual int		do_get_generation(void) = 0;
		virtual int		do_get_best_score(void) = 0;
		virtual void	do_next_gen(void) = 0;
}
