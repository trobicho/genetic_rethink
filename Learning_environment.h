/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Learning_environment.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:50:45 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/09 18:33:58 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	Learning_environment
{
	public:
		int		evaluate(People &people);
		int		evaluate(People &people, int generation);

	private:
		virtual int		do_evalutation(People &people) = 0;
		virtual int		do_evalutation(People &people, int generation) = 0;
}
