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

void	ft_free_ms(t_ms *ms)
{
	if(ms->m_lock)
		ms->m_lock = ft_free_null(ms->m_lock);
	if(ms->msg)
		ms->msg = ft_free_null(ms->msg);
	if(ms)
		ms = ft_free_null(ms);
}

void	ft_set_data(int ac, char **av, t_ms *ms)
{
	ms->philo_nb = ft_atoi(av[1]);
	ms->tt_d = ft_atoi(av[2]);
	ms->tt_e = ft_atoi(av[3]);
	ms->tt_s = ft_atoi(av[4]);
	if (ac == 6)
		ms->meal_nb = ft_atoi(av[5]);
	else 
		ms->meal_nb = INT_MAX;
	ms->dead = false;
	ms->start_time = 0;
}

t_ms *ft_init_ms(int ac, char **av)
{
	static t_ms	*ms;

	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		ms->m_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		ms->msg = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!ms || !ms->m_lock || !ms->msg)
		{
			ft_free_ms(ms);
			ft_err_exit(ERR_MEM);
		}
		ft_set_data(ac, av, ms);	
		pthread_mutex_init(ms->m_lock, NULL);
		pthread_mutex_init(ms->msg, NULL);
	}
	return(ms);
}

void	ft_destroy_mutex(t_ms *ms)
{
	pthread_mutex_destroy(ms->m_lock);
	pthread_mutex_destroy(ms->msg);
}

int main (int ac, char **av)
{ 	
	t_ms		*ms;


	if(!ft_init_arg(ac, av))
		return (1);
	ms = ft_init_ms(ac, av);
	print_debug(ac, ms);
	ft_destroy_mutex(ms);
	ft_free_all(ms);
	return(0);
}