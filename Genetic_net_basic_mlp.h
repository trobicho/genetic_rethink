/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Genetic_net_basic_mlp.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:03:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/07 17:07:42 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Genetic.h"

class	Genetic_net_basic_mlp: private Genetic
{
	public:
		Genetic_net_basic_mlp(Learning_net_environment *env);

	private:
		int		do_get_generation(void);
		int		do_get_best_score(void);
		void	do_next_gen(void);
}
