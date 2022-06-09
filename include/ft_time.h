/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 04:37:34 by yoseo             #+#    #+#             */
/*   Updated: 2022/06/09 11:16:44 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <sys/time.h>
# include <unistd.h>
typedef struct s_time_helper
{
	struct timeval		start;
	struct timeval		end;
	unsigned long		cur_time;
} 	t_time_helper;

void			start_time(t_time_helper *time);
void			flow_time(t_time_helper *time);
unsigned long 	time_diff(struct timeval *s, struct timeval *e);
unsigned long	ft_usleep(unsigned long ms);
int				check_overtime(t_time_helper *time, unsigned long check);

#endif