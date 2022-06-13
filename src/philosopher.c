#include "philosophers.h"

void	print_log(t_philosopher *p, t_state s)
{
	unsigned long	global_time;
	unsigned long	philo_num;
	
	global_time = flow_time(p->global_time);
	philo_num = p->num;
	if (s == TAKE_FORK)
		printf("%ld %ld %s\n", global_time, philo_num, "has taken a fork");
	else if (s == EATING)
		printf("%ld %ld %s\n", global_time, philo_num, "is eating");
	else if (s == THINKING)
		printf("%ld %ld %s\n", global_time, philo_num, "is thinking");
	else if (s == SLEEPING)
		printf("%ld %ld %s\n", global_time, philo_num, "is sleeping");
	else if (s == DIE)
		printf("%ld %ld %s\n", global_time, philo_num, "is die");
}

t_state	try_print_log(t_philosopher *philo, t_state state)
{
	if (philo->state == ALIIVE && flow_time(&philo->time) > philo->time_to_die)
	{
		state = DIE;
		philo->state = DIE;
	}
	else if (philo->state == ALIIVE && state == EAT_DONE)
	{
		++philo->eat;
		if (philo->eat >= philo->must_eat)
		{
			philo->state = FULL;
			state = CLEAR;
			return FULL;
		}
		start_time(&philo->time);
	}
	print_log(philo, state);
	return state;
}

t_state	philo_action(t_philosopher *philo, t_state philo_state)
{
	static char				is_print = 1;
	t_state 				thread_state;

	pthread_mutex_lock(philo->global_lock);
	thread_state = ALIIVE;
	if (is_print)
	{
		philo_state = try_print_log(philo, philo_state);
		if (philo_state == DIE)
		{
			thread_state = CLEAR;
			is_print = 0;
		}
		if (philo_state == FULL)
		{
			thread_state = CLEAR;
		}
	}
	else
		thread_state = CLEAR;
	pthread_mutex_unlock(philo->global_lock);
	return thread_state;
}
