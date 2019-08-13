/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake_copy_test.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:17:00 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/13 06:47:57 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libgen.h"
#include "People_net.h"
#include <vector>

typedef struct
{
    int x, y;
}s_vec2i;

typedef struct
{
    int x, y, dir;
}s_body;

typedef struct
{
    s_vec2i head;
    std::vector<s_body> body;
    int dir, len, vLen;
}s_snake;

class	Snake: public Learning_environment_net
{
	public:
		Snake(int w = 50, int h = 50);
		~Snake(){};
		int		eval_and_display(People_net &people, int generation);
        void	set_food(bool);

	private:
		int		do_evalutation(People_net &people, int generation);
		int		do_get_nb_output(void);
		int		do_get_nb_input(void);

		void	step(People_net &people);
		bool	fillViewTab();
        void	snake_init();
        void	sensor_update();
        void	rand_one_apple();
        void	add_len(int l=1);
        void	init_body();
        void	move();
        void	change_dir(int dir);
		int		item_dist(int dir, int id, int maxD);

		s_vec2i			m_pos;
		vector<double>	m_sensor;
        vector<int>		m_viewTab;
        s_snake			m_snake;
        s_vec2i			m_max, m_apple;
        int				m_basicLen=10;
        int				m_starving=700;
        int				m_score = 0;
        int				m_moveNoEat=0;
        int				m_nbOutPerDir = 3;
        int				m_nbMove;
		int				m_nb_direction = 3;
        int				m_activFoodGen = 0;
        bool			m_dead = false;
		bool			m_bFood = false;
		bool			m_bEat=false;
		const int		m_extra_sensor = 2;
		int				m_applePoint = 100;
};
