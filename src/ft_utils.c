# include "philosophers.h"

int	ft_atoi(char *str)
{
	long long	answer;
	int			is_plus;

	answer = 0;
	is_plus = 1;
	if (*str == '-')
		is_plus = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str != ' ')
	{
		if ('0' <= *str && *str <= '9')
			answer = answer * 10 + *str - '0';
		++str;
	}
	return (((int)answer) * is_plus);
}

void	 print_error(int error)
{
	if (error & ERROR_ARGC)
	{
		printf("check your arguments: \n");
		printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	if (error & ERROR_PHILO_COUNT)
		printf("ERROR_PHILO_COUNT: check your number_of_philosophers\n");
	if (error & ERROR_DIE_TIME)
		printf("ERROR_DIE_TIME: check your time_to_die\n");
	if (error & ERROR_EAT_TIME)
		printf("ERROR_EAT_TIME: check your time_to_eat\n");
	if (error & ERROR_SLEEP_TIME)
		printf("ERROR_SLEEP_TIME: check your time_to_sleep\n");
	if (error & ERROR_MUST_EAT)
		printf("ERROR_MUST_EAT: check your [number_of_times_each_philosopher_must_eat]\n");
}

int	is_error(int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc < 5 || argc > 6)
	{
		error = ERROR_ARGC;
		print_error(error);
		return error;
	}
	if (ft_atoi(argv[1]) <= 0)
		error |= ERROR_PHILO_COUNT;
	if (ft_atoi(argv[2]) <= 0)
		error |= ERROR_DIE_TIME;
	if (ft_atoi(argv[3]) <= 0)
		error |= ERROR_EAT_TIME;
	if (ft_atoi(argv[4]) <= 0)
		error |= ERROR_SLEEP_TIME;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		error |= ERROR_MUST_EAT;
	print_error(error);
	return error;
}