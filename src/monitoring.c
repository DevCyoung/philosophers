#include "philosophers.h"

int	check_philosophers(t_info *info)
{
	unsigned int	i;
	unsigned int	is_philo_die;
	unsigned int	is_all_eat;
	t_philosopher *philo;

	i = 0;
	is_philo_die = ALIIVE;
	is_all_eat = 0;

	pthread_mutex_lock(&info->global_lock);

	while (i < info->philo_count)
	{
		philo = &info->philosophers[i];
		if (philo->state == ALIIVE && flow_time(&philo->time) > philo->time_to_die)
		{
			is_philo_die = DIE;
			break ;
		}
		if (philo->state == FULL && philo->eat == philo->must_eat)
			++is_all_eat;
		++i;
	}

	pthread_mutex_unlock(&info->global_lock);

	if (is_all_eat == info->philo_count)
		is_philo_die = CLEAR;
	if (is_philo_die == DIE)
		is_philo_die = philo_action(philo, is_philo_die);
	return is_philo_die;
}

void	*monitoring(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (check_philosophers(info) != ALIIVE)
			break ;
		ft_sleep(3);
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