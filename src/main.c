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

#include "philosophers.h"

void	init_philo(t_philosopher *philo, size_t	idx, t_info *info)
{
	size_t	left_idx;

	if (idx == 0)
		left_idx = info->cnt - 1;
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
	if (philo->num % 2)
	{
		philo->first_fork = &info->fork[idx];
		philo->second_fork = &info->fork[left_idx];
	}
	else
	{
		philo->first_fork = &info->fork[left_idx];
		philo->second_fork = &info->fork[idx];
	}
}

int	try_init_info(int argc, char **argv, t_info *info)
{
	int	i;

	i = -1;
	info->cnt = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = 4294967295;
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->cnt);
	if (info->fork == NULL)
		return (0);
	info->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * info->cnt);
	if (info->philos == NULL)
	{
		free(info->fork);
		return (0);
	}
	while (++i < info->cnt)
		pthread_mutex_init(&info->fork[i], NULL);
	pthread_mutex_init(&info->global_lock, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	int			i;
	t_info		info;
	pthread_t	monitor_id;

	if (is_error(argc, argv))
		return (0);
	if (try_init_info(argc, argv, &info) == 0)
		return (0);
	start_time(&info.global_time);
	i = -1;
	while (++i < info.cnt)
		init_philo(&info.philos[i], i, &info);
	i = -1;
	while (++i < info.cnt)
		pthread_create(&info.philos[i].t_id, NULL, life_cycle, &info.philos[i]);
	pthread_create(&monitor_id, NULL, monitoring, &info);
	pthread_join(monitor_id, NULL);
	i = -1;
	while (++i < info.cnt)
		pthread_join(info.philos[i].t_id, NULL);
	return (0);
}
