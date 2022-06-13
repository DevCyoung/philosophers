/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:51:15 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/14 02:51:19 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_catch_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	philo->lock |= 1;
	if (philo_act(philo, TAKE_FORK) != ALIVE)
		return (CLEAR);
	pthread_mutex_lock(philo->second_fork);
	philo->lock |= 2;
	if (philo_act(philo, TAKE_FORK) != ALIVE)
		return (CLEAR);
	return (ALIVE);
}

int	try_eat(t_philosopher *philo)
{
	if (philo_act(philo, EATING) != ALIVE)
		return (CLEAR);
	ft_sleep(philo->time_to_eat);
	if (philo_act(philo, EAT_DONE) != ALIVE)
		return (CLEAR);
	philo->lock = 0;
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
	return (ALIVE);
}

int	try_sleep(t_philosopher *philo)
{
	if (philo_act(philo, SLEEPING) != ALIVE)
		return (CLEAR);
	ft_sleep(philo->time_to_sleep);
	return (ALIVE);
}

int	try_think(t_philosopher *philo)
{
	if (philo_act(philo, THINKING) != ALIVE)
		return (CLEAR);
	ft_sleep(3);
	return (ALIVE);
}

void	*life_cycle(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->num % 2)
		ft_sleep(3);
	while (1)
	{
		if (try_catch_fork(philo) == CLEAR)
			break ;
		if (try_eat(philo) == CLEAR)
			break ;
		if (try_sleep(philo) == CLEAR)
			break ;
		if (try_think(philo) == CLEAR)
			break ;
	}
	if (philo->lock & 2)
		pthread_mutex_unlock(philo->second_fork);
	if (philo->lock & 1)
		pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}
