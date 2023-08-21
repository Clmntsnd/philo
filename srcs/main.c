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
**		◦ timestamp_in_ms X has taken a fork 
		◦ timestamp_in_ms X is eating
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

void	ft_destroy_mutex(t_ms *ms, t_ph *ph)
{
	pthread_mutex_destroy(&ms->m_lock);
	pthread_mutex_destroy(&ms->msg);
	pthread_mutex_destroy(&ms->f_lock);
	pthread_mutex_destroy(&ph->left.f_lock);
}


void	ft_philo(t_ms *ms, t_ph *ph)
{
	pthread_t	th[200];
	int 		i;

	i = -1;
	printf("ms->philo_nbr = %d\n", ms->philo_nb);
	pthread_mutex_lock(ph->m_lock);
	while(++i < ms->philo_nb)
		if(pthread_create(&th[i], NULL, &routine, &ph[i]) != 0)
			printf("Issue with pthread create\n");
	pthread_mutex_unlock(ph->m_lock);
	i = -1;
	pthread_mutex_lock(ph->m_lock);
	while(++i < ms->philo_nb)
		if(pthread_join(th[i], NULL) != 0)
			printf("Issue with pthread join\n");
	pthread_mutex_unlock(ph->m_lock);
}

int main (int ac, char **av)
{ 	
	t_ms	ms;
	t_ph	ph[200];

	if(!ft_init_arg(ac, av))
		return (1);
	ft_init_ms(&ms, ac, av);
	ft_init_ph(&ms, ph);
	print_debug(ac, &ms, ph);
	ft_philo(&ms, ph);
	ft_destroy_mutex(&ms, ph);
	return(0);
}