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
	if (ms->m_lock)
		ms->m_lock = ft_free_null(ms->m_lock);
	if (ms->msg)
		ms->msg = ft_free_null(ms->msg);
	if (ms)
		ms = ft_free_null(ms);
}

void	ft_destroy_mutex(t_ms *ms)
{
	pthread_mutex_destroy(ms->m_lock);
	pthread_mutex_destroy(ms->msg);
}

int main (int ac, char **av)
{ 	
	t_ms	*ms;
	t_ph	**ph;

	if(!ft_init_arg(ac, av))
		return (1);
	ms = ft_init_ms(ac, av);
	ph = ft_init_ph(ms);
	print_debug(ac, ms, ph);
	ft_destroy_mutex(ms);
	ft_free_all(ms);
	return(0);
}