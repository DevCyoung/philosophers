/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 04:42:33 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/13 01:39:45 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

unsigned long	time_diff(t_time_helper *time)
{
	unsigned long	sec_ms;
	unsigned long	ms;

	sec_ms = (time->end.tv_sec - time->start.tv_sec) * 1000;
	ms = (time->end.tv_usec - time->start.tv_usec) / 1000;
	return (sec_ms + ms);
}

unsigned long	flow_time(t_time_helper *time)
{
	gettimeofday(&time->end, 0);
	return (time_diff(time));
}

void	ft_sleep(unsigned long milisec)
{
	t_time_helper	time;

	start_time(&time);
	while (1)
	{
		if (flow_time(&time) >= milisec)
			break ;
		usleep(1000);
	}
}

void	start_time(t_time_helper *time)
{
	gettimeofday(&time->start, 0);
}
