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

t_ms	*ft_init_ms(int ac, char **av)
{
	static t_ms	*ms;

	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			ft_err_exit(ERR_MEM);
		ms->philo_nb = ft_atoi(av[1]);
		ms->tt_d = ft_atoi(av[2]);
		ms->tt_e = ft_atoi(av[3]);
		ms->tt_s = ft_atoi(av[4]);
		if (ac == 6)
			ms->meal_nb = ft_atoi(av[5]);
		else 
			ms->meal_nb = INT_MAX;
		ms->status = 0;
	}
	return (ms);
}

t_ph	*ft_init_ph(t_ms *ms)
{
	static t_ph	*ph;
	int 		i;

	if (!ph) 
	{ 
		ph = ft_calloc(1, sizeof(t_ph));
		if (!ph)
			ft_err_exit(ERR_MEM);
		//while 'i' is less than philo_nb, attributes the philo id value and attributes the ms struct where 
		// each philo will have its own data
		i = -1;
		while (++i < ms->philo_nb)
		{
			ph[i].eating = false;
			ph[i].eat_i = 0;
			ph[i].id = i + 1; //assign the id per 'i + 1' (to start the 1st id to 1)
			ph[i].data = ms; //assign the data to each philo
		}
	}
	return (ph);
}

void	ft_init_mutex(t_ms *ms)
{
	//Init mutexes needed, to use it in the routine ft
	pthread_mutex_init(&ms->m_lock, NULL);
	pthread_mutex_init(&ms->r_fork, NULL);
	pthread_mutex_init(&ms->l_fork, NULL);
	pthread_mutex_init(&ms->msg, NULL);
}

void	ft_destroy_mtx(t_ms *ms)
{
	//Destroy the mutex ('clean/free' it)
	pthread_mutex_destroy(&ms->m_lock);
	pthread_mutex_destroy(&ms->r_fork);
	pthread_mutex_destroy(&ms->l_fork);
	pthread_mutex_destroy(&ms->msg);
}

void	ft_philo(t_ms *ms)
{
	pthread_t	t[ms->philo_nb];
	t_ph		*ph;
	int			i;

	ph = ft_init_ph(ms);
	ft_init_mutex(ms);
	i = - 1;
	while (++i < ms->philo_nb)
		pthread_create(&t[i], NULL, &routine, &ph[i]); 
		//create all threads, each thread (t[i]) will execute the task 'routine' with each philo as the argument for the routine
	i = -1;
	while (++i < ms->philo_nb)
		pthread_join(t[i] , NULL); //join al threads
	ft_destroy_mtx(ms);
}

int main (int ac, char **av)
{ 	
	t_ms	*ms = NULL;

	if(!ft_init_arg(ac, av))
		return (1);
	ms = ft_init_ms(ac, av);
	print_debug(ac, ms);
	ft_philo(ms);
	// printf("\n🚧 "KYEL"Work In Progress 🚧\n"KRT);

	return(0);
}