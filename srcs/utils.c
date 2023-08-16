#include "../includes/philo.h"
// Used to get a timer from the moment philo is starting
// To save the exact moment and not modify it each time the function is called,
// the usage of a static variable is helpfull (as in GNL)
long long int	ft_timer(void)
{
	static struct timeval	start;
	struct timeval			now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000));
}

void	print_msg(int match, t_ph *ph)
{
	char *str;

	pthread_mutex_lock(&ph->data->msg);
	if (match == THINKING)
		str = THINK_MSG;
	if (match == EATING)
		str = EAT_MSG;
	if (match == SLEEPING)
		str = SLEEP_MSG;
	printf("%lld %d %s\n", ft_timer(), ph->id, str);
	pthread_mutex_unlock(&ph->data->msg);
}

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