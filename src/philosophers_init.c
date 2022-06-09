/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:24:54 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 18:59:32 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	init_info(int argc, char **argv, t_info *info)
// {
// 	if (argv < 5 && argv > 6)
// 		return 0;
// 	info->philo_count = ft_atoi(argv[0]);
// 	info->time_to_die = ft_atoi(argv[1]);
// 	info->time_to_eat = ft_atoi(argv[2]);
// 	info->time_to_sleep = ft_atoi(argv[3]);
// 	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_count + 1);
// 	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * info->philo_count + 1);
// 	if (info->forks == NULL || info->philosophers == NULL)
// 		return 0;
// }