/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment_net.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:55:21 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 18:43:10 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	Learning_environment_net
{
	public:
		Learning_net_environment();
		int		evaluate(People_net &people);
		int		evaluate(People_net &people, int generation);
		int		get_nb_output(void);
		int		get_nb_input(void);

	private:
		virtual int		do_evalutation(People_net &people, int generation) = 0;
		virtual int		do_evalutation(People_net &people) = 0;
		virtual int		do_get_nb_output(void) = 0;
		virtual int		do_get_nb_input(void) = 0;
}