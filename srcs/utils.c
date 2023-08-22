#include "../includes/philo.h"

void	*ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*ft_get_ms(void *ptr)
{
	static void	*ms = NULL;

	if (ptr)
		ms = ptr;
	return (ms);
}

// Used to get a timer from the moment philo is starting
//
// To save the exact moment and not modify it each time the function is called,
// the usage of a static variable is helpfull (as in GNL)
time_t	ft_timer(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000));
}

bool	print_msg(int match, t_ph *ph)
{
	char 		*str;
	bool		error;

	// pthread_mutex_lock(&ph->data.msg);
	if (match == THINKING)
		str = THINK_MSG;
	if (match == EATING)
		str = EAT_MSG;
	if (match == SLEEPING)
		str = SLEEP_MSG;
	if (match == DEAD)
		str = DEAD_MSG;
	if (ph->data.dead == false)
	{
		printf("%ld %d %s\n", ft_timer(), ph->id, str);
		pthread_mutex_unlock(&ph->data.msg);
		error = false;
	}
	if (ph->data.dead == true)
	{
		printf("%ld %d %s\n", ft_timer(), ph->id, str);
		error = true;
	}
	//TODO add a variable to check if everyone has eaten ine this exemple : ./philo 4 410 60 800 1 
	return (error);
}

void	print_debug(int ac, t_ms *ms, t_ph *ph)
{
	int i;
	(void)ph;

	if (DEBUG)
	{
		printf(KITA KGRE"\n* --- DEBUG in ms starts --- *\n");
		printf("philo_nb = %d\n", ms->philo_nb);
		printf("tt_d = %d\n", ms->tt_d);
		printf("tt_e = %d\n", ms->tt_e);
		printf("tt_s = %d\n", ms->tt_s);
		printf("start_time = %ld\n", ms->start_time);
		printf("is_dead = %d\n", ms->dead);
		printf("addr m_lock = %p\n", &ms->m_lock);
		printf("addr msg = %p\n", &ms->msg);
		printf("addr f_lock = %p\n", &ms->f_lock);
		if (ac < 6){
			printf("meal_nb = %d\n", ms->meal_nb);
			printf("* --- DEBUG in ms ends --- *\n\n"KRT);
		}
		else
		{
			printf("meal_nb = %d\n", ms->meal_nb);
			printf("* --- DEBUG in ms ends --- *\n\n"KRT);
		}
		printf(KITA KGRE"\n* --- DEBUG in ph starts --- *\n");
		i = -1;
		while (++i < ms->philo_nb)
		{
			printf("ph[%d]->id = %d\n", i, ph[i].id);
			// printf("ph[%d].right.%d = %d\n", i, i, ph[i].right->i);
			printf("ph[%d]->eat_i = %d\n", i, ph[i].eat_i);
			printf("ph[%d]->time_last_meal = %ld\n", i, ph[i].time_last_meal);
			printf("ph[%d]->data.start_time = %ld\n", i, ph[i].data.start_time);
			printf("ph[%d]->data.philo_nb = %d\n", i, ph[i].data.philo_nb);
			printf("ph[%d]->data.tt_d = %d\n", i, ph[i].data.tt_d);
			printf("ph[%d]->data.tt_e = %d\n", i, ph[i].data.tt_e);
			printf("ph[%d]->data.tt_s = %d\n", i, ph[i].data.tt_s);
			printf("ph[%d]->data.is_dead = %d\n", i, ph[i].data.dead);
			printf("ph[%d]->data.meal_nb = %d\n", i, ph[i].data.meal_nb);
			printf("ph[%d].m_lock = %p\n", i, ph[i].m_lock);
			printf("ph[%d].print_msg = %p\n", i, ph[i].print_msg);
			printf("ph[%d].f_lock = %p\n\n", i, ph[i].f_lock);
		}
		printf(KITA KGRE"* --- DEBUG in ph ends --- *\n"KRT);
	}
}