/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake_copy_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:16:58 by trobicho          #+#    #+#             */
/*   Updated: 2019/10/27 04:04:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"
#include "Snake_copy_test.h"
#include <iostream>
#include <unistd.h>

Snake::Snake(int w, int h)
{
	m_sensor.resize(get_nb_input());
	m_viewTab.resize(w * h, 0);
	m_max.x = w;
	m_max.y = h;
	m_apple_vec.resize(1000);
}

void Snake::snake_init()
{
    m_snake.head={.x = m_max.x/2, .y=m_max.y/2};
	//m_snake.head = m_head_pos_gen;
    m_snake.len=m_basicLen;
    m_snake.vLen=1;
    init_body();
    m_snake.dir=0;
    m_score=1;
    m_dead=false;
    m_moveNoEat=0;
    m_nbMove=0;
}

int		Snake::item_dist(int dir, int id, int maxD)
{
	auto	p = m_snake.head;
	int		dx = 0;
	int		dy = 0;
	int		d;

	if (dir % 2 == 0)
		dx = dir-1;
	else
		dy = dir-2;
	for(d=1; d<maxD; d++)
	{
		p.x += dx;
		p.y += dy;
		if (m_viewTab[p.x + p.y * m_max.x] == id
			|| m_viewTab[p.x + p.y * m_max.x] == 3)
			return (d);
	}
	return (-1);
}

void Snake::sensor_update()
{
    int	head=m_snake.head.y*m_max.x+m_snake.head.x, d;
    int	maxD;

    for(int i=0; i<m_nb_direction; i++)
    {
        int dir = ((m_snake.dir == 0 ? 3 : m_snake.dir - 1) + i) % 4;
        if(dir<2)
            maxD=(dir%2)?m_snake.head.y:m_snake.head.x;
        else
            maxD=((dir%2)?m_max.y-m_snake.head.y:m_max.x-m_snake.head.x)-1;
        int t=head;
        m_sensor[i]= 1.0 - maxD / (double)m_max.x;
        for(int a=0; a<2; a++)
        {
            if(a==1 && !m_bFood)
                m_sensor[6+i]=-1.0;
            else
            {
                if((d = item_dist(dir, a + 1, maxD)) >= 0)
				{
					m_sensor[3+a*3+i] = 1.0 - d / (double)m_max.x;
				}
                else
				{
					m_sensor[3 + a * 3 + i] = -1.0;
				}
            }
        }
    }
	if (m_extra_sensor)
	{
		if (m_bFood)
			m_sensor[m_nbOutPerDir * m_nb_direction] = 
				(m_starving + m_snake.len - m_moveNoEat) / (double)m_starving;
		else
			m_sensor[m_nbOutPerDir * m_nb_direction] = 0.0;
		if (m_extra_sensor > 1)
			m_sensor[m_nbOutPerDir * m_nb_direction + 1] = m_snake.len / 300.0;
	}
}

int	Snake::eval_and_display(People_net &people, int generation)
{
	snake_init();
	m_apple_cur = 0;
	next_apple();
	while(!m_dead)
	{
		system("clear");
		for (int i=0; i<m_viewTab.size(); i++)
		{
			if (i > 0 && i % m_max.x == 0)
				std::cout << "\n";
			if (m_viewTab[i] == 1)
				std::cout << "# ";
			else if (m_viewTab[i] == 2)
				std::cout << "$ ";
			else if (m_viewTab[i] == 3)
				std::cout << "@ ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
		step(people);
		usleep(5000);
	}
	return (m_score);
}

double	Snake::do_evalutation(People_net &people, int generation)
{
	static int	last_gen = -1;

	if (last_gen != generation)
	{
		m_head_pos_gen.x = trl::rand_uniform_int(0, m_max.x - 1);
		m_head_pos_gen.y = trl::rand_uniform_int(0, m_max.y - 1);
		rand_apple_vec();
		last_gen = generation;
	}
    if(m_activFoodGen>=0 && generation>=m_activFoodGen)
        set_food(true);
	snake_init();
	m_apple_cur = 0;
	next_apple();
	while(!m_dead)
	{
		step(people);
	}
	return ((double)m_score);
}

void Snake::step(People_net& people)
{
	int rep;

    fillViewTab();
    sensor_update();
	people.calc_output(m_sensor);
	rep = people.get_answer();
	if(rep==0)
		change_dir(3);
	else if(rep==1)
		change_dir(1);
    move();
    if(!m_bFood)
    {
        if(m_score%5==0)
            add_len(1);
    }
    else if(m_bEat)
    {
        m_bEat=false;
        m_score+=m_applePoint;
        m_moveNoEat=0;
        add_len(m_apple_add_len);
        next_apple();
    }
    else if(m_moveNoEat>(m_starving+m_snake.len))
        m_dead=true;
    else
        m_moveNoEat++;
	if (!m_bFood)
		m_score++;
}

void Snake::next_apple()
{
	if (m_apple_cur >= m_apple_vec.size())
		m_apple_cur = 0;
	m_apple = m_apple_vec[m_apple_cur];
	m_apple_cur++;
}

void Snake::rand_apple_vec()
{
	for (int i = 0; i < m_apple_vec.size(); i++)
	{
		m_apple_vec[i] = rand_apple_one();
	}
}

s_vec2i	Snake::rand_apple_one()
{
	s_vec2i	apple;

	apple.x = trl::rand_uniform_int(2, m_max.x - 3);
	apple.y = trl::rand_uniform_int(2, m_max.y - 3);
	return (apple);
}

void Snake::set_food(bool b)
{
    m_bFood=b;
    if(m_bFood)
        next_apple();
}

void Snake::move()
{
    m_snake.head.x+=(!(m_snake.dir%2))*(m_snake.dir-1);
    m_snake.head.y+=(m_snake.dir%2)*(m_snake.dir-2);
    s_body temp=m_snake.body[0], temp2;
    m_snake.body[0]=(s_body){.x=m_snake.head.x, .y=m_snake.head.y, .dir=m_snake.dir};
    for(int i=1; i<m_snake.len; i++)
    {
        temp2=m_snake.body[i];
        m_snake.body[i]=temp;
        temp=temp2;
    }
    if(m_snake.vLen<m_snake.len)
        m_snake.vLen++;
    fillViewTab();
    if(m_bFood && m_snake.head.x==m_apple.x && m_snake.head.y==m_apple.y)
        m_bEat=true;
    m_nbMove++;
}

bool Snake::fillViewTab()
{
    if(m_snake.head.x<0 || m_snake.head.y<0\
    || m_snake.head.x>=m_max.x || m_snake.head.y>=m_max.y)
        m_dead=true;
    else
    {
        for(int i=0; i<m_viewTab.size(); i++){m_viewTab[i]=0;}
        for(int i=0; i<m_snake.vLen; ++i) //carrement moyen d'accelerer le tout en passant jusqu'au prochain rot
        {
            if(i && m_snake.head.x==m_snake.body[i].x && m_snake.head.y==m_snake.body[i].y)
                m_dead=true;
            m_viewTab[m_snake.body[i].x+m_snake.body[i].y*m_max.x]=1;
        }
    }
    if(m_bFood)
        m_viewTab[m_apple.x+m_apple.y*m_max.x] += 2;
    return m_dead;
}

void Snake::init_body()
{
    m_snake.body.resize(m_snake.len);
    s_vec2i v=m_snake.head;
    int dir=m_snake.dir;
    for(int i=0; i<m_snake.len; i++)
    {
        m_snake.body[i].x=v.x;
        m_snake.body[i].y=v.y;
        m_snake.body[i].dir=dir;
        v.x-=(!(dir%2))*(dir-1);
        v.y-=(dir%2)*(dir-2);
    }
}

void Snake::add_len(int l)
{
    m_snake.body.resize(m_snake.len+l);
    for(int i=m_snake.len; i<m_snake.len+l; i++)
    {
        if(!i && !m_snake.len)
            m_snake.body[i]=(s_body){.x=m_snake.head.x, .y=m_snake.head.y, .dir=m_snake.dir};
        else
            m_snake.body[i]=m_snake.body[i-1];
    }
    m_snake.len+=l;
}

void Snake::change_dir(int dir)
{
    if(!m_dead)
    {
        m_snake.dir+=dir;
        m_snake.dir%=4;
    }
}

int		Snake::do_get_nb_output(void)
{
	return (3);
}

int		Snake::do_get_nb_input(void)
{
	return (m_nbOutPerDir * m_nb_direction + m_extra_sensor);
}
