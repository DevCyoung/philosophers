#include "philosophers.h"

int	try_catch_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (philo_action(philo, TAKE_FORK_FIRST) != ALIIVE)
		return CLEAR;
	pthread_mutex_lock(philo->second_fork);
	if (philo_action(philo, TAKE_FORK_SECOND) != ALIIVE)
		return CLEAR;
	return ALIIVE;
}

int	try_eat(t_philosopher *philo)
{
	if (philo_action(philo, EATING) != ALIIVE)
		return CLEAR;
	ft_sleep(philo->time_to_eat);
	if (philo_action(philo, EAT_DONE) != ALIIVE)
		return CLEAR;
	return ALIIVE;
}

int	try_sleep(t_philosopher *philo)
{
	if (philo_action(philo, SLEEPING) != ALIIVE)
		return CLEAR;
	ft_sleep(philo->time_to_sleep);
	return ALIIVE;
}

int try_think(t_philosopher *philo)
{
	if (philo_action(philo, THINKING) != ALIIVE)
		return CLEAR;
	ft_sleep(3);
	return ALIIVE;
}

void	*philo_life_cycle(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	if (philo->num % 2)
		ft_sleep(3);
	while (1)
	{
		if (try_catch_fork(philo) == CLEAR)
			break;
		if (try_eat(philo) == CLEAR)
			break;
		if (try_sleep(philo) == CLEAR)
			break;
		if (try_think(philo) == CLEAR)
			break;
	}

	//printf("lock : %ld break\n", philo->lock);
	// if ((philo->lock & 2) == 2)
	// 	pthread_mutex_unlock(philo->second_fork);
	// if ((philo->lock & 1) == 1)
	// 	pthread_mutex_unlock(philo->first_fork);
	return NULL;
}