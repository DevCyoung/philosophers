/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:02:18 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/13 01:17:35 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_time.h"

typedef enum e_philo_state
{
	ALIVE = 1,
	TAKE_FORK = 2,
	EATING = 4,
	FIN_CHECK = 8,
	FULL = 16,
	THINKING = 32,
	SLEEPING = 64,
	DIE = 128,
	FINISH = 256,
	EAT_DONE = 512,
	CLEAR = 1024,
	HUNGRY = 2048,
	INF_EAT = HUNGRY << 1,
}	t_state;

typedef struct s_philosopher
{
	size_t		num;
	size_t		left_num;
	size_t		eat;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		must_eat;
	size_t		lock;
	size_t		state;
	pthread_t	t_id;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t 	*global_lock;
	t_time_helper 		*global_time;
	t_time_helper		time;
}	t_philosopher;

typedef struct s_info
{
	pthread_mutex_t global_lock;
	pthread_mutex_t	*fork;
	t_philosopher	*philos;
	int				cnt;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat;
	t_state			is_Inf_eat;
	t_time_helper 	global_time;
	
} 	t_info;

void			*life_cycle(void *arg);
int				ft_atoi(char *str);
t_state			philo_act(t_philosopher *philo, t_state state);
void			print_log(t_philosopher *p, t_state s);
void			state_print(t_info	*info);
void			*monitoring(void *arg);
int				check_philo_die(t_philosopher *philo);
int				check_philo_full(t_philosopher *philo);
void			philo_unlock(t_philosopher *philo);
int				is_error(int argc, char **argv);

#endif