/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:02:18 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/14 11:10:51 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_time.h"

typedef enum e_philo_state
{
	ALIVE =			0x0001,
	TAKE_FORK =		0x0002,
	EATING =		0x0004,
	EAT_DONE =		0x0008,
	FIN_CHECK =		0x0010,
	FULL =			0x0020,
	THINKING =		0x0040,
	SLEEPING =		0x0080,
	DIE =			0x0100,
	CLEAR =			0x0200,
	HUNGRY =		0x0400,
	INF_EAT =		0x0800,
}	t_state;

typedef struct s_philosopher
{
	size_t				num;
	size_t				left_num;
	size_t				eat;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				must_eat;
	size_t				lock;
	size_t				state;
	pthread_t			t_id;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*global_lock;
	t_time_helper		*global_time;
	t_time_helper		time;
}	t_philosopher;

typedef struct s_info
{
	int					cnt;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				must_eat;
	pthread_mutex_t		global_lock;
	pthread_mutex_t		*fork;
	t_philosopher		*philos;
	t_state				is_inf_eat;
	t_time_helper		global_time;
}	t_info;

int				ft_atoi(char *str);
int				is_error(int argc, char **argv);
void			*life_cycle(void *arg);
void			*monitoring(void *arg);
void			print_log(t_philosopher *p, t_state s);
t_state			philo_act(t_philosopher *philo, t_state state);

#endif
