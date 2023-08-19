#include "../includes/philo.h"

void	*ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	ft_free_all(t_ms *ms)
{
	// int 	i;
	if(ms->m_lock)
		ms->m_lock = ft_free_null(ms->m_lock);
	if(ms->msg)
		ms->msg = ft_free_null(ms->msg);
	if(ms)
		ms = ft_free_null(ms);
	//TODO put future struct here
}

// Used to get a timer from the moment philo is starting
// To save the exact moment and not modify it each time the function is called,
// the usage of a static variable is helpfull (as in GNL)
time_t	ft_timer(void)
{
	struct timeval	start;
	time_t			now;

	gettimeofday(&start, NULL);
	now = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (now);
}

time_t	ft_t_stamp(t_ph *ph)
{
	time_t		time;
	time_t		now;

	now = ft_timer();
	time = now - ph->data.start_time;
	return (time);
}

void	print_msg(int match, t_ph *ph)
{
	char *str;

	pthread_mutex_lock(ph->data.msg);
	if (match == THINKING)
		str = THINK_MSG;
	if (match == EATING)
		str = EAT_MSG;
	if (match == SLEEPING)
		str = SLEEP_MSG;
	printf("%ld %d %s\n", ft_timer(), ph->id, str);
	pthread_mutex_unlock(ph->data.msg);
}

void	ft_err_exit(char *str)
{
	printf("%s%s%s\n", KRED, str, KRT);
	//TODO put free fts here to avoid leaks
	exit(EXIT_FAILURE);
}

void	print_debug(int ac, t_ms *ms, t_ph **ph)
{
	int i;

	if (DEBUG)
	{
		printf(KITA KGRE"\n* --- DEBUG in ms starts --- *\n");
		printf("philo_nb = %d\n", ms->philo_nb);
		printf("tt_d = %d\n", ms->tt_d);
		printf("tt_e = %d\n", ms->tt_e);
		printf("tt_s = %d\n", ms->tt_s);
		printf("start_time = %ld\n", ms->start_time);
		printf("is_dead = %d\n", ms->dead);
		if (ac < 6)
			printf("* --- DEBUG in ms ends --- *\n\n"KRT);
		else
		{
			printf("meal_nb = %d\n", ms->meal_nb);
			printf("* --- DEBUG in ms ends --- *\n\n"KRT);
		}
		printf(KITA KGRE"\n* --- DEBUG in ph starts --- *\n");
		i = -1;
		while (++i < ms->philo_nb)
		{
			printf("ph[%d]->id = %d\n", i, ph[i]->id);
			// printf("ph[%d].right.%d = %d\n", i, i, ph[i].right->i);
			printf("ph[%d]->eat_i = %d\n", i, ph[i]->eat_i);
			printf("ph[%d]->time_last_meal = %ld\n", i, ph[i]->time_last_meal);
			printf("ph[%d]->data.start_time = %ld\n", i, ph[i]->data.start_time);
			printf("ph[%d]->data.philo_nb = %d\n", i, ph[i]->data.philo_nb);
			printf("ph[%d]->data.tt_d = %d\n", i, ph[i]->data.tt_d);
			printf("ph[%d]->data.tt_e = %d\n", i, ph[i]->data.tt_e);
			printf("ph[%d]->data.tt_s = %d\n", i, ph[i]->data.tt_s);
			printf("ph[%d]->data.is_dead = %d\n", i, ph[i]->data.dead);
			printf("ph[%d]->data.meal_nb = %d\n\n", i, ph[i]->data.meal_nb);
		}
		printf(KITA KGRE"* --- DEBUG in ph ends --- *\n"KRT);
	}
}