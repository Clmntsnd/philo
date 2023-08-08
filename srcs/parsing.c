#include "../includes/philo.h"

bool	ft_isdigit(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	return (true);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool ft_init_arg(int ac, char **av)
{
	int i;

	if (ac < 5)
		return(printf("❌"KRED" Not enough arguments ❌\n"KRT), false);
	else if (ac > 6)
		return(printf("❌"KRED" Too many arguments ❌\n"KRT), false);
	else
	{
		i = 0;
		//first check to look for a non digit character
		while (av[++i])
			if (ft_isdigit(av[i]) == false) 
				return (printf("❌"KRED" Oups ! Issues with an argument (only digits above 0 are accepted) ❌\n"KRT), false);
		//check if 0 < philo_nb < 200
		if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200) 
			return (printf("❌"KRED" Oups ! Issues with argv[1] (0 < philosophers numbers < 200) ❌\n"KRT), false);
		//check to see there is a nbr above INT_MAX
		i = 1;
		while(av[++i])
		{
			if (ft_strlen(av[i]) > 10 || ft_atol(av[i]) > INT32_MAX) 
				return (printf("❌"KRED" Oups ! Issues with an argument (not a valid integer) ❌\n"KRT), false);
			if (i < 5 && ft_atoi(av[i]) < 60)
					return (printf("❌"KRED" Oups ! Issues with an argument (invalid time (< 60 ms)) ❌\n"KRT), false);
			if (i == 5 && ft_atoi(av[5]) < 1)
					return (printf("❌"KRED" Oups ! Issues with an argument (invalid times to eat) ❌\n"KRT), false);
		}
	}
		printf("Welcome to my "KCYN"%s"KRT" program\n", "./philo");
	return(true);
}
