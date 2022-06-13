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

// #define TAKE_FORK	"has taken a fork"
// #define EAT 		"is eating"
// #define SLEEP		"is sleeping"
// #define THINK		"is thinking"
// #define IS_DIE		0

// #define ALL_EAT		1
// #define EXIT		3
// #define SUCESS		4

// #define DEAD			1
// #define ALREADY_DEAD	2
// #define IM_FULL			4
// #define ALLIVE			0


typedef enum e_philo_state
{
	ALIIVE = 1,
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
}	t_state;

typedef struct s_philo_helper
{
	t_time_helper	global;
	
}	t_philo_helper;

typedef struct s_philosopher
{
	size_t		 	num;
	size_t			left_num;
	size_t			eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat;
	size_t			checker;
	size_t			lock;
	pthread_t		t_id;
	
	pthread_mutex_t *second_fork;
	pthread_mutex_t *first_fork;

	size_t			state;
	
	pthread_mutex_t *global_lock;
	t_time_helper 	*global_time;

	t_time_helper	time;
}	t_philosopher;

typedef struct s_info
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	size_t			philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat;

	pthread_mutex_t global_lock;
	t_time_helper 	global_time;
	
} 	t_info;

void			*philo_life_cycle(void *arg);
int				ft_atoi(char *str);
t_state			philo_action(t_philosopher *philo, t_state state);
void			print_log(t_philosopher *p, t_state s);
void			state_print(t_info	*info);
void			*monitoring(void *arg);
#endif