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
		if (flow_time(&philo->time) > philo->time_to_die)
		{
			is_philo_die = DIE;
			break ;
		}
		if (philo->eat == philo->must_eat)
			++is_all_eat;
		++i;
	}
	pthread_mutex_unlock(&info->global_lock);
	if (is_philo_die == DIE)
		is_philo_die = philo_action(philo, is_philo_die);
	if (is_all_eat == info->philo_count)
		is_philo_die = CLEAR;
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
		//ft_sleep(3);
	}
	return NULL;
}

// void	init_philo(t_philosopher *philo, size_t	number, t_info *info)
// {
// 	size_t	right;
// 	size_t	left;
	
// 	right = number;
// 	if (number == 1)
// 		left = info->philo_count;
// 	else
// 		left = number - 1;
	
// 	philo->num = number;
// 	philo->left_num = left;
// 	philo->eat = 0;
// 	philo->time_to_die = info->time_to_die;
// 	philo->time_to_eat = info->time_to_eat;
// 	philo->time_to_sleep = info->time_to_sleep;
// 	philo->must_eat = info->must_eat;
// 	philo->state = ALIIVE;
// 	philo->global_lock = &info->global_lock;
// 	philo->global_time = &info->global_time;
	
// 	philo->lock = 0;
	
// 	if (philo->num % 2)
// 	{

// 		philo->first_fork = &info->forks[right];
// 		philo->second_fork = &info->forks[left];
// 	}
// 	else
// 	{
// 		philo->first_fork = &info->forks[left];
// 		philo->second_fork = &info->forks[right];
// 	}
// 	// if (info->philo_count % 2 == 0)
// 	// {
// 	// 	if (philo->num % 2)
// 	// 	{
			
// 	// 		philo->first_fork = &info->forks[right];
// 	// 		philo->second_fork = &info->forks[left];
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		philo->first_fork = &info->forks[left];
// 	// 		philo->second_fork = &info->forks[right];
// 	// 	}
// 	// }
// 	// else
// 	// {
// 	// 	if (philo->num % 2)
// 	// 	{
// 	// 		philo->first_fork = &info->forks[left];
// 	// 		philo->second_fork = &info->forks[right];
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		philo->first_fork = &info->forks[right];
// 	// 		philo->second_fork = &info->forks[left];
// 	// 	}
// 	// }
	
	
// }

// int	init_info(int argc, char **argv, t_info *info)
// {
	
// 	if (argc < 5 && argc > 6)
// 		return 0;
// 	info->philo_count = ft_atoi(argv[1]);
// 	info->time_to_die = ft_atoi(argv[2]);
// 	info->time_to_eat = ft_atoi(argv[3]);
// 	info->time_to_sleep = ft_atoi(argv[4]);
// 	info->must_eat = 4294967295;
// 	if (argc == 6)
// 		info->must_eat = ft_atoi(argv[5]);
// 	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_count + 1);
// 	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * info->philo_count);
// 	if (info->forks == NULL || info->philosophers == NULL)
// 		return 0;
// 	for (size_t i = 0; i < info->philo_count + 1; i++)
// 		pthread_mutex_init(&info->forks[i], NULL);
// 	return 1;
// }

void	state_print(t_info	*info)
{
	for (size_t i = 0; i < info->philo_count; i++)
	{
		printf("id : %ld eat : %ld \n", info->philosophers[i].num, info->philosophers[i].eat);
	}
}
	
// 	// while (1)
// 	// {
// 	// 	sleep(60);
// 	// 	system("cls");
// 	// 	for (size_t i = 0; i < info.philo_count; i++)
// 	// 	{
// 	// 		printf("id : %ld eat : %ld \n", info.philosophers[i].num ,info.philosophers[i].eat);
// 	// 	}
// 	// 	exit(1);
// 	// }
// }

// int main(int argc, char **argv)
// {
// 	t_info				info;
// 	if (init_info(argc, argv, &info) == 0)
// 		return 0;

	
// 	for (size_t i = 0; i < info.philo_count; i++)
// 	{
// 		init_philo(&info.philosophers[i], i + 1, &info);
// 		start_time(&info.philosophers[i].time);
// 		pthread_create(&info.philosophers[i].t_id, NULL, philo_life_cycle, &info.philosophers[i]);
// 	}
	
// 	for (size_t i = 0; i < info.philo_count; i++)
// 		pthread_join(info.philosophers[i].t_id, NULL);
		
// 	// pthread_t		m_id;
// 	// pthread_create(&m_id, NULL, monitoring, &info);
// 	return 0;
// }

// void	state_print(t_info	*info)
// {
// 	for (size_t i = 0; i < info->philo_count; i++)
// 	{
// 		printf("id : %ld eat : %ld \n", info->philosophers[i].num, info->philosophers[i].eat);
// 	}
	
// 	// while (1)
// 	// {
// 	// 	sleep(60);
// 	// 	system("cls");
// 	// 	for (size_t i = 0; i < info.philo_count; i++)
// 	// 	{
// 	// 		printf("id : %ld eat : %ld \n", info.philosophers[i].num ,info.philosophers[i].eat);
// 	// 	}
// 	// 	exit(1);
// 	// }
// }