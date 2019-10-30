/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   People_neat_handler.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:44:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/28 00:47:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

struct	s_connection_gene
{
	int		node_in;
	int		node_out;
	double	weight;
	bool	enabled;
	int		innov;
	bool	done;
};


class People_neat_handler
{
	public:
		People_neat_handler(int reserve = 100);
		int		set_new_innov_number(s_connection_gene &connec);
		void	flush_innov(void);
		int		get_innov_number(void)
			{return (m_cur_innov_number);}
		void	set_innov_number(int innov_num)
			{m_cur_innov_number = innov_num;}
		//int		get_nb_input() = 0;		//?
		//int		get_nb_output() = 0;	//?
	private:
		int								m_cur_innov_number = 1;
		std::vector<s_connection_gene>	m_innov_connec;
};
