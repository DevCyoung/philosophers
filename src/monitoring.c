#include "philosophers.h"

int	check_philo_die(t_philosopher *philo)
{	
	if (philo->state & ALIVE)
	{
		if ((philo->state & HUNGRY) == 0)
			return ALIVE;
		if (flow_time(&philo->time) < philo->time_to_die)
			return ALIVE;
	}
	return DIE;
}

int	check_philo_full(t_philosopher *philo)
{
	if (philo->state & HUNGRY)
		return HUNGRY;
	return FULL;
}

int	check_philosophers(t_info *info)
{
	unsigned int	i;
	unsigned int	philos_state;
	t_philosopher 	*philo;

	pthread_mutex_lock(&info->global_lock);
	i = 0;
	philos_state = 0;
	while (i < info->philo_count)
	{
		philo = &info->philosophers[i];
		philos_state |= check_philo_die(philo) | check_philo_full(philo);
		if ((philos_state & ALIVE) == 0)
			break;
		++i;
	}
	pthread_mutex_unlock(&info->global_lock);
	if ((philos_state & ALIVE) == 0)
	{
		philo_act(philo, DIE);
		if (info->philo_count == 1)
			pthread_mutex_unlock(philo->first_fork);
	}
	return philos_state;
}

void	*monitoring(void *arg)
{
	t_info			*info;
	unsigned int	philos_state;
	info = (t_info *)arg;
	while (1)
	{
		philos_state = check_philosophers(info);
		if ((philos_state & ALIVE) == 0 ||
			(philos_state & HUNGRY) == 0)
			break ;
		ft_sleep(2);
	}
	return NULL;
}

void	state_print(t_info	*info)
{
	for (size_t i = 0; i < info->philo_count; i++)
	{
		printf("id : %ld eat : %ld \n", info->philosophers[i].num, info->philosophers[i].eat);
	}
}