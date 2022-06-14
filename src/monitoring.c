/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:56:44 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/14 11:08:34 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosophers(t_info *info)
{
	int				i;
	unsigned int	philos_state;
	t_philosopher	*philo;

	pthread_mutex_lock(&info->global_lock);
	i = -1;
	philos_state = ALIVE;
	while (++i < info->cnt)
	{
		philo = &info->philos[i];
		if (philo->state & HUNGRY)
			if (flow_time(&philo->time) > philo->time_to_die)
				philos_state |= DIE;
		philos_state |= (philo->state & HUNGRY);
	}
	pthread_mutex_unlock(&info->global_lock);
	if ((philos_state & DIE))
	{
		philos_state ^= ALIVE;
		philo_act(philo, DIE);
		if (info->cnt == 1)
			pthread_mutex_unlock(philo->first_fork);
	}
	return (philos_state);
}

void	*monitoring(void *arg)
{
	t_info			*info;
	unsigned int	philos_state;

	info = (t_info *)arg;
	while (1)
	{
		philos_state = check_philosophers(info);
		if ((philos_state & ALIVE) == 0)
			break ;
		if ((philos_state & HUNGRY) == 0)
			break ;
		ft_sleep(3);
	}
	return (NULL);
}
