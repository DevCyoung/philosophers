/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:56:19 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/14 02:56:21 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	print_log(t_philosopher *p, t_state philo_action)
{
	unsigned long	global_time;
	unsigned long	philo_num;

	global_time = flow_time(p->global_time);
	philo_num = p->num;
	if (philo_action == TAKE_FORK)
		printf("%ld %ld %s\n", global_time, philo_num, "has taken a fork");
	else if (philo_action == TAKE_FORK)
		printf("%ld %ld %s\n", global_time, philo_num, "has taken a fork");
	else if (philo_action == EATING)
		printf("%ld %ld %s\n", global_time, philo_num, "is eating");
	else if (philo_action == THINKING)
		printf("%ld %ld %s\n", global_time, philo_num, "is thinking");
	else if (philo_action == SLEEPING)
		printf("%ld %ld %s\n", global_time, philo_num, "is sleeping");
	else if (philo_action == DIE)
		printf("%ld %ld %s\n", global_time, philo_num, "is dying");
}

t_state	try_print_log(t_philosopher *philo, t_state philo_action)
{
	if (flow_time(&philo->time) > philo->time_to_die)
		philo_action = DIE;
	if (philo_action == EAT_DONE)
	{
		++philo->eat;
		if (philo->eat == philo->must_eat)
			philo->state ^= HUNGRY;
		start_time(&philo->time);
	}
	if (philo_action == DIE)
		philo->state ^= ALIVE;
	print_log(philo, philo_action);
	return (philo->state);
}

t_state	philo_act(t_philosopher *philo, t_state philo_action)
{
	static char				is_print = 1;
	t_state					philo_state;
	t_state					thread_state;

	pthread_mutex_lock(philo->global_lock);
	thread_state = ALIVE;
	if (is_print)
	{
		philo_state = try_print_log(philo, philo_action);
		if ((philo_state & ALIVE) == 0 || philo_action == DIE)
			is_print = 0;
		if ((philo_state & ALIVE) == 0 || (philo_state & HUNGRY) == 0)
			thread_state = CLEAR;
	}
	else
		thread_state = CLEAR;
	pthread_mutex_unlock(philo->global_lock);
	return (thread_state);
}
