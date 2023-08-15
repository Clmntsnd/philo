#include "../includes/philo.h"

void	ft_err_exit(char *str)
{
	printf("%s%s%s\n", KRED, str, KRT);
	//TODO put free fts here to avoid leaks
	exit(EXIT_FAILURE);
}

void	print_debug(int ac, t_ms *ms)
{
	if (DEBUG)
	{
		printf(KITA KGRE"\n* --- DEBUG in ft_is_valid arg starts --- *\n");
		printf("philo_nb = %d\n", ms->philo_nb);
		printf("tt_d = %d\n", ms->tt_d);
		printf("tt_e = %d\n", ms->tt_e);
		printf("tt_s = %d\n", ms->tt_s);
		if (ac < 6)
			printf("* --- DEBUG in ft_is_valid arg ends --- *\n\n"KRT);
		else
		{
			printf("meal_nb = %d\n", ms->meal_nb);
			printf("* --- DEBUG in ft_is_valid arg ends --- *\n\n"KRT);
		}
	}	
}