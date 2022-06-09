/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 04:33:11 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 18:58:31 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_state(t_philosopher *philo)
{
	flow_time(&philo->time);
	if (philo->time.cur_time > (unsigned long)philo->time_to_die)
	{
		safe_print_action(philo, EAT);
		return DEAD;
	}
	else if (philo->eat >= philo->must_eat)
	{
		return IM_FULL;
	}
	return ALLIVE;
}


long long	safe_print_action(t_philosopher *philo, char *str)
{
	static t_time_helper	time;
	static pthread_mutex_t	time_lock;
	static char				checker = -1;	
	
	if (checker == -1)
	{
		pthread_mutex_init(&time_lock, NULL);
		start_time(&time);
		checker = ALLIVE;
		return 0;
	}
	
	
	pthread_mutex_lock(&time_lock);



	
	if (checker != ALLIVE)
	{
		pthread_mutex_unlock(&time_lock);
		return DEAD;
	}
	flow_time(&time);
	flow_time(&philo->time);
	if (philo->time.cur_time > philo->time_to_die)
	{
		str = "is died";
		checker = DEAD;
		printf("%ld %ld %s\n", time.cur_time, philo->num, str);
		pthread_mutex_unlock(&time_lock);
		return DEAD;
	}
	if (str != IS_DIE)
		printf("%ld %ld %s\n", time.cur_time, philo->num, str);
	if(philo->eat >= philo->must_eat)
	{
		pthread_mutex_unlock(&time_lock);	
		return IM_FULL;
	}
	pthread_mutex_unlock(&time_lock);
	return ALLIVE;
}


int	try_catch_fork(t_philosopher *philo)
{
	if (check_state(philo) != ALLIVE)
		return DEAD;
	philo->lock = 0;
	pthread_mutex_lock(philo->first_fork);
	philo->lock |= 1;
	if (safe_print_action(philo, TAKE_FORK) != ALLIVE)
		return DEAD;	
	pthread_mutex_lock(philo->second_fork);
	philo->lock |= 2;
	if (safe_print_action(philo, TAKE_FORK) != ALLIVE)
		return DEAD;
	return ALLIVE;
}

int	try_eat(t_philosopher *philo)
{
	if (safe_print_action(philo, EAT) != ALLIVE)
		return DEAD;
	ft_usleep(philo->time_to_eat);
	++philo->eat;
	if (safe_print_action(philo, IS_DIE) != ALLIVE)
		return DEAD;
	start_time(&philo->time);
	philo->lock = 0;
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
	return ALLIVE;
}

int	try_sleep(t_philosopher *philo)
{
	if (safe_print_action(philo, SLEEP) != ALLIVE)
		return DEAD;
	ft_usleep(philo->time_to_sleep);
	return ALLIVE;
}

int try_think(t_philosopher *philo)
{
	if (safe_print_action(philo, THINK) != ALLIVE)
		return DEAD;
	ft_usleep(2);
	return ALLIVE;
}

int	philo_action(t_philosopher *philo)
{
	if (try_catch_fork(philo) != ALLIVE)
		return DEAD;
	if (try_eat(philo) != ALLIVE)
		return DEAD;
	if (try_sleep(philo) != ALLIVE)
		return DEAD;
	if (try_think(philo) != ALLIVE)
		return DEAD;
	return ALLIVE;
}