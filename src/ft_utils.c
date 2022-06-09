
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


