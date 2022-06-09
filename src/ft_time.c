/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 04:42:33 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 16:26:21 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

unsigned long time_diff(struct timeval *s, struct timeval *e)
{
	unsigned long	sec_ms;
	unsigned long	ms;
	
	sec_ms = (e->tv_sec-s->tv_sec)*1000;
	ms = (e->tv_usec - s->tv_usec)/1000;
	return sec_ms + ms;
}

unsigned long ft_usleep(unsigned long ms)
{
	struct timeval	start;
	struct timeval	end;
	unsigned long	diff;
	
	gettimeofday(&start, 0);
	while (1)
	{
		gettimeofday(&end, 0);
		diff = time_diff(&start, &end);
		if (diff >= ms)
			break ;
		usleep(1000);
	}
	return diff;
}

void	start_time(t_time_helper *time)
{
	gettimeofday(&time->start, 0);
	time->cur_time = 0;
}

void	flow_time(t_time_helper *time)
{
	gettimeofday(&time->end, 0);
	time->cur_time = time_diff(&time->start, &time->end);
}

int	check_overtime(t_time_helper *time, unsigned long check)
{
	if (time->cur_time > check)
		return 0;
	return 1;
}