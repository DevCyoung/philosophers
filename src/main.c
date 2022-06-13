/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:01:40 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/13 12:56:45 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	init_philo(t_philosopher *philo, size_t	idx, t_info *info)
{
	size_t	left_idx;

	if (idx == 0)
		left_idx = info->philo_count - 1;
	else
		left_idx = idx - 1;	
	start_time(&philo->time);
	philo->num = idx + 1;
	philo->eat = 0;
	philo->lock = 0;
	philo->state = ALIVE | HUNGRY;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
	philo->global_lock = &info->global_lock;
	philo->global_time = &info->global_time;
	philo->first_fork = &info->forks[left_idx];
	philo->second_fork = &info->forks[idx];
	if (philo->num % 2)
	{
		philo->first_fork = &info->forks[idx];
		philo->second_fork = &info->forks[left_idx];
	}
}

int	try_init_info(int argc, char **argv, t_info *info)
{
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = 4294967295;
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (info->forks == NULL)
		return 0;
	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * info->philo_count);
	if (info->philosophers == NULL)
	{
		free(info->forks);
		return 0;
	}
	for (size_t i = 0; i < info->philo_count; i++)
		pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_init(&info->global_lock, NULL);
	return 1;
}



int main(int argc, char **argv)
{
	t_info				info;
	pthread_t 			monitor_id;
	if (is_error(argc, argv))
		return 0;
	if (try_init_info(argc, argv, &info) == 0)
		return 0;
	
	start_time(&info.global_time);
	for (size_t i = 0; i < info.philo_count; i++)
		init_philo(&info.philosophers[i], i, &info);

	for (size_t i = 0; i < info.philo_count; i++)
		pthread_create(&info.philosophers[i].t_id, NULL, philo_life_cycle, &info.philosophers[i]);
	pthread_create(&monitor_id, NULL, monitoring, &info);
	pthread_join(monitor_id, NULL);
	for (size_t i = 0; i < info.philo_count; i++)
		pthread_join(info.philosophers[i].t_id, NULL);
	//state_print(&info);
	return 0;
}