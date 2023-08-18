#include "../includes/philo.h"

/*
**	RULES
**	Your(s) program(s) should take the following arguments: 
**	◦ number_of_philosophers: The number of philosophers and also the number of forks.
**	◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their 
**									last meal or the beginning of the sim- ulation, they die.
**	◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
**	◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
**	◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times,
**																	the simulation stops. If not specified, the simulation stops when a philosopher dies.
**	• Each philosopher has a number ranging from 1 to number_of_philosophers.
**	• Philosopher number 1 sits next to philosopher number number_of_philosophers. 
**	• Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
**
**	LOGS
**	About the logs of your program:
**	• Any state change of a philosopher must be formatted as follows:
**		◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
**		◦ timestamp_in_ms X is sleeping
**		◦ timestamp_in_ms X is thinking
**		◦ timestamp_in_ms X died
**
**	Replace timestamp_in_ms with the current timestamp in milliseconds
**	and X with the philosopher number.
**	• A displayed state message should not be mixed up with another message.
**	• A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
**	• Again, philosophers should avoid dying!
*/

void	*ft_get_ms(void *ptr)
{
	static void	*ms = NULL;

	if (ptr)
		ms = ptr;
	return (ms);
}

void	ft_init_ms(t_ms *ms, int ac, char **av)
{
	ms->philo_nb = ft_atoi(av[1]);
	ms->tt_d = ft_atoi(av[2]);
	ms->tt_e = ft_atoi(av[3]);
	ms->tt_s = ft_atoi(av[4]);
	if (ac == 6)
		ms->meal_nb = ft_atoi(av[5]);
	else 
		ms->meal_nb = INT_MAX;
	ms->start_time = 0;
	ms->is_dead = false;
	pthread_mutex_init(&ms->m_lock, NULL);
	pthread_mutex_init(&ms->msg, NULL);
	ft_get_ms(ms);
}

void	ft_init_ph(t_ms *ms, t_ph *ph)
{
	int	i;

	i = -1;
	while (++i < ms->philo_nb)
	{
		ph[i].id = i;
		ph[i].dead = false;
		ph[i].left.i = -1;
		ph[i].right = ft_calloc(1, sizeof(t_fork));
		ph[i].right->i = -1;
		ph[i].eat_i = 0;
		ph[i].time_last_meal = 0;
		ph[i].time_to_eat = 0;
		ph[i].time_to_sleep = 0;
		ph[i].data = ms;
	}
}

// void	ft_init_mutex(t_ms *ms)
// {
// 	//Init mutexes needed, to use it in the routine ft
// 	pthread_mutex_init(&ms->m_lock, NULL);
// 	pthread_mutex_init(&ms->f_lock, NULL);
// 	pthread_mutex_init(&ms->msg, NULL);
// }

void	ft_destroy_mtx(t_ms *ms)
{
	//Destroy the mutex ('clean/free' it)
	pthread_mutex_destroy(&ms->m_lock);
	pthread_mutex_destroy(&ms->msg);
}

void	ft_init_fork(t_ph *ph)
{
	int		i;

	i = -1;
	while (++i < ph->data->philo_nb - 1)
	{
		if (i < ph->data->philo_nb)
			ph[i].right = &ph[i + 1].left;
		if (i == ph->data->philo_nb - 1)
			ph[i].right = &ph[0].left;
		pthread_mutex_init(&ph[i].right->f_lock, NULL);
	}
}

void	ft_philo(t_ms *ms, t_ph *ph)
{
	pthread_t	t[200];
	int			i;

	ft_init_fork(ph);
	i = - 1;
	pthread_mutex_lock(&ph->data->m_lock);
	while (++i < ms->philo_nb)
	{
		// printf("ph->data->start_time = %d\n", ph->data->start_time);
		ph[i].time_last_meal = ph->data->start_time;
		// printf("ph[%d].time = %d\n", i, ph->data->start_time);
		pthread_create(&t[i], NULL, &routine, &ph[i]);
	}
	ph->data->start_time = ft_timer();
	pthread_mutex_unlock(&ph->data->m_lock);
	// 	//create all threads, each thread (t[i]) will execute the task 'routine' with each philo as the argument for the routine
	i = -1;
	while (++i < ms->philo_nb)
		pthread_join(t[i] , NULL); //join al threads
	ft_destroy_mtx(ms);
}

int main (int ac, char **av)
{ 	
	// int		i;
	t_ms	ms;
	t_ph	ph[200];

	if(!ft_init_arg(ac, av))
		return (1);
	ft_init_ms(&ms, ac, av);
	ft_init_ph(&ms, ph);
	ft_philo(&ms, ph);
	print_debug(ac, &ms, ph);
	printf("ph->right addr : %p\n", ph->right);
	// ft_free_null(ph->right);
	// ft_free_null(ph);
	// printf("\n🚧 "KYEL"Work In Progress 🚧\n"KRT);

	return(0);
}