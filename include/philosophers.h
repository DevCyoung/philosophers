/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:02:18 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 16:48:13 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_time.h"

#define TAKE_FORK	"has taken a fork"
#define EAT 		"is eating"
#define SLEEP		"is sleeping"
#define THINK		"is thinking"
#define IS_DIE		0

#define ALL_EAT		1
#define EXIT		3
#define SUCESS		4

#define DEAD			1
#define ALREADY_DEAD	2
#define IM_FULL			4
#define ALLIVE			0

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
} 	t_info;

size_t	philo_eat(int number, size_t eat_ms);
size_t	philo_think(int number, size_t think_ms);
size_t	philo_sleep(int number, size_t sleep_ms);
int	philo_action(t_philosopher *philo);

size_t	eat(t_philosopher *philo);
int		ft_atoi(char *str);
long long	prt_act(t_philosopher *philo, char *str);
long long	safe_print_action(t_philosopher *philo, char *str);

#endif