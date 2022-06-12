/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:01:40 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/13 01:56:22 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	init_philo(t_philosopher *philo, size_t	number, t_info *info)
{
	//size_t	right;
	size_t	left;
	
	//right = number;
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
	philo->state = ALIIVE;
	philo->global_lock = &info->global_lock;
	philo->global_time = &info->global_time;
	
	philo->lock = 0;
	
	if (philo->num % 2)
	{

		philo->first_fork = &info->forks[philo->num];
		philo->second_fork = &info->forks[philo->left_num];
	}
	else
	{
		philo->first_fork = &info->forks[philo->left_num];
		philo->second_fork = &info->forks[philo->num];
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
	for (size_t i = 0; i < info->philo_count + 1; i++)
		pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_init(&info->global_lock, NULL);
	return 1;
}



int main(int argc, char **argv)
{
	t_info				info;
	if (init_info(argc, argv, &info) == 0)
		return 0;

	start_time(&info.global_time);
	for (size_t i = 0; i < info.philo_count; i++)
	{
		init_philo(&info.philosophers[i], i + 1, &info);
		start_time(&info.philosophers[i].time);
		pthread_create(&info.philosophers[i].t_id, NULL, philo_life_cycle, &info.philosophers[i]);
	}
	
	pthread_t m_id;
	pthread_create(&m_id, NULL, monitoring, &info);
	
	for (size_t i = 0; i < info.philo_count; i++)
		pthread_join(info.philosophers[i].t_id, NULL);
	pthread_join(m_id, NULL);
	state_print(&info);
	return 0;
}