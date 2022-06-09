/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:01:40 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 18:57:46 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void *thread_philosopher(void *arg)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)arg;

	start_time(&philo->time);
	if (philo->num % 2)
	{
		ft_usleep(3);
	}
	while(1)
	{
		if (philo_action(philo) != ALLIVE)
			break;
	}
	if (philo->lock & 2)
		pthread_mutex_unlock(philo->second_fork);
	if (philo->lock & 1)
		pthread_mutex_unlock(philo->first_fork);
	return NULL;
}

void	init_philo(t_philosopher *philo, size_t	number, t_info *info)
{
	size_t	right;
	size_t	left;
	
	right = number;
	if (number == 1)
		left = info->philo_count;
	else
		left = number - 1;
	
	philo->num = number;
	philo->left_num = left;
	philo->eat = 0;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
	philo->lock = 0;

	// philo->first_fork = &info->forks[right];
	// philo->second_fork = &info->forks[left];

	// if (philo->num % 2)
	// {
	// 	philo->first_fork = &info->forks[left];
	// 	philo->second_fork = &info->forks[right];
	// }
	// else
	// {
	// 	philo->first_fork = &info->forks[right];
	// 	philo->second_fork = &info->forks[left];
	// }
	if (info->philo_count % 2 == 0)
	{
		if (philo->num % 2)
		{
			philo->first_fork = &info->forks[right];
			philo->second_fork = &info->forks[left];
		}
		else
		{
			philo->first_fork = &info->forks[left];
			philo->second_fork = &info->forks[right];
		}
	}
	else
	{
		if (philo->num % 2)
		{
			philo->first_fork = &info->forks[left];
			philo->second_fork = &info->forks[right];
		}
		else
		{
			philo->first_fork = &info->forks[right];
			philo->second_fork = &info->forks[left];
		}
	}
	
	
}

int	init_info(int argc, char **argv, t_info *info)
{
	
	if (argc < 5 && argc > 6)
		return 0;
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = 4294967295;
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_count + 1);
	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * info->philo_count);
	if (info->forks == NULL || info->philosophers == NULL)
		return 0;
	for (size_t i = 0; i < info->philo_count + 10; i++)
		pthread_mutex_init(&info->forks[i], NULL);
	return 1;
}

int main(int argc, char **argv)
{
	t_info				info;
	if (init_info(argc, argv, &info) == 0)
		return 0;
		
	safe_print_action(NULL, NULL);
	
	// for (size_t i = 0; i < info.philo_count; i++)
	// {
	// 	if ((i + 1) % 2 == 0)
	// 	{
	// 		init_philo(&info.philosophers[i], i + 1, &info);
	// 		pthread_create(&info.philosophers[i].t_id, NULL, thread_philosopher, &info.philosophers[i]);
	// 	}
	// }
	
	// for (size_t i = 0; i < info.philo_count; i++)
	// {
	// 	if ((i + 1) % 2)
	// 	{
	// 		init_philo(&info.philosophers[i], i + 1, &info);
	// 		pthread_create(&info.philosophers[i].t_id, NULL, thread_philosopher, &info.philosophers[i]);
	// 	}
	// }

	for (size_t i = 0; i < info.philo_count; i++)
	{
		init_philo(&info.philosophers[i], i + 1, &info);
		pthread_create(&info.philosophers[i].t_id, NULL, thread_philosopher, &info.philosophers[i]);
	}

		
	for (size_t i = 0; i < info.philo_count; i++)
		pthread_join(info.philosophers[i].t_id, NULL);
	
	for (size_t i = 0; i < info.philo_count; i++)
	{
		printf("id : %ld eat : %ld \n", info.philosophers[i].num, info.philosophers[i].eat);
	}
	
	// while (1)
	// {
	// 	sleep(60);
	// 	system("cls");
	// 	for (size_t i = 0; i < info.philo_count; i++)
	// 	{
	// 		printf("id : %ld eat : %ld \n", info.philosophers[i].num ,info.philosophers[i].eat);
	// 	}
	// 	exit(1);
	// }
	return 0;
}