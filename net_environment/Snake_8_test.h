/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake_8_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 00:36:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/22 02:30:01 by trobicho         ###   ########.fr       */
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
        s_vec2i	rand_apple_one();
        void	rand_apple_vec();
        void	add_len(int l=1);
        void	init_body();
        void	move();
        void	change_dir(int dir);
		int		item_dist(int dir, int id, int maxD);
		void	next_apple();

		s_vec2i			m_pos;
		vector<double>	m_sensor;
        vector<int>		m_viewTab;
        s_snake			m_snake;
        s_vec2i			m_max;
        s_vec2i			m_apple;
        vector<s_vec2i>	m_apple_vec;
		int				m_apple_cur = 0;
        int				m_basicLen=10;
        int				m_starving=700;
        int				m_score = 0;
        int				m_moveNoEat=0;
        int				m_nbOutPerDir = 3;
        int				m_nbMove;
		int				m_nb_direction = 7;
        int				m_activFoodGen = 0;
        bool			m_dead = false;
		bool			m_bFood = false;
		bool			m_bEat=false;
		const int		m_extra_sensor = 0;
		int				m_applePoint = 1;
};
