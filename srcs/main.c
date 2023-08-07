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
**	• Any other philosopher number N sits between philosopher number N - 1 and philoso- pher number N + 1.
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

void	ft_err_exit(void)
{
	printf("❌"KRED" Memory allocation failed ❌\n"KRT);
	exit (0);
}

t_ms	*ft_init_ms()
{
	static t_ms	*ms;

	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			ft_err_exit();
	}
	return (ms);
}

bool ft_valid_arg(int ac, char **av, t_ms *ms)
{
	if (ac < 5)
		return(printf("❌"KRED" Not enough arguments ❌\n"KRT), false);
	else if (ac > 6)
		return(printf("❌"KRED" Too many arguments ❌\n"KRT), false);
	else
	{
		printf("Welcome to my "KCYN"%s"KRT" program\n", av[0]);
		ms->philo_nb = ft_atoi(av[1]);
		ms->tt_d = ft_atoi(av[2]);
		ms->tt_e = ft_atoi(av[3]);
		ms->tt_s = ft_atoi(av[4]);
		if (DEBUG)
		{
			printf(KITA KGRE"\n* --- DEBUG in ft_is_valid arg starts --- *\n");
			printf("philo_nb = %d\n", ms->philo_nb);
			printf("tt_d = %d\n", ms->tt_d);
			printf("tt_e = %d\n", ms->tt_e);
			printf("tt_s = %d\n", ms->tt_s);
			if (ac < 6)
				printf("* --- DEBUG in ft_is_valid arg ends --- *\n"KRT);
		}
		
		if (ac == 6)
		{
			ms->meal_nb = ft_atoi(av[5]);
			if (DEBUG)
			{
				printf("meal_nb = %d\n", ms->meal_nb);
				printf("* --- DEBUG in ft_is_valid arg ends --- *\n"KRT);
			}
		}
	}
	return(true);
}


int main (int ac, char **av)
{ 	
	t_ms	*ms;

	ms = ft_init_ms();
	if(!ft_valid_arg(ac, av, ms))
		return (1);
	printf("\n🚧 "KYEL"Work In Progress 🚧\n"KRT);
	return(0);
}