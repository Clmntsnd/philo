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

t_ms	*ft_init_ms(char **av)
{
	static t_ms	*ms;

	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			ft_err_exit();
		ms->i = 0;
		ms->philo_nb = ft_atoi(av[1]);
		ms->tt_d = ft_atoi(av[2]);
		ms->tt_e = ft_atoi(av[3]);
		ms->tt_s = ft_atoi(av[4]);
		ms->meal_nb = ft_atoi(av[5]);
	}
	return (ms);
}

bool ft_valid_arg(int ac, t_ms *ms)
{
	if (ac < 5)
		return(printf("❌"KRED" Not enough arguments ❌\n"KRT), false);
	else if (ac > 6)
		return(printf("❌"KRED" Too many arguments ❌\n"KRT), false);
	else
	{
		printf("Welcome to my "KCYN"%s"KRT" program\n", "./philo");
		if (DEBUG)
		{
			printf(KITA KGRE"\n* --- DEBUG in ft_is_valid arg starts --- *\n");
			printf("philo_nb = %d\n", ms->philo_nb);
			printf("tt_d = %d\n", ms->tt_d);
			printf("tt_e = %d\n", ms->tt_e);
			printf("tt_s = %d\n", ms->tt_s);
			if (ac < 6)
				printf("* --- DEBUG in ft_is_valid arg ends --- *\n\n"KRT);
		}
		
		if (ac == 6)
		{
			if (DEBUG)
			{
				printf("meal_nb = %d\n", ms->meal_nb);
				printf("* --- DEBUG in ft_is_valid arg ends --- *\n\n"KRT);
			}
		}
	}
	return(true);
}

void	*routine(void *arg)
{
	/* --	Remember that this fucntion will be executed by each threads ! ---	*/

	//to pass arg to 'routine' we need to use a 'void *arg' to the ft, and then cast the correct data value to it.
	t_ph	*ph;
	int		loop = 1;
	int		time = 0;

	//cast the void *arg to the correct value type
	ph = (t_ph *)arg;

	//if philo is an even number, sleep for 500ms to staggered when they are called
	if (ph->id % 2 == 0)
		usleep(500);
	
	//while loop until loop is equal to 0 (i.e that'd break the loop)
	while (loop)
	{
		usleep(500);
		//lock the values, 'time', 'i' and 'loop' 
		pthread_mutex_lock(&ph->data->m_lock);
		//until the NB value is reached print the message [id X eat Y], X is the philo's id, Y is the index (i.e the nbr of time they eat) 
		if (ph->data->i < NB)
		{
			printf("id %d eat %d\n", ph->id, ph->data->i);
			(ph->data->i)++; //increment the index (i.e the nbr of time they eat)
			time++; //increment this value to count each time a philo is called
		}
		//once there is no philo left, flip the switch to break the loop
		else
			loop = 0;
		pthread_mutex_unlock(&ph->data->m_lock);
	}
	//print message, [id X time called]
	printf("[id %d] called %d times\n", ph->id, time);
	return (arg);
}

void	ft_create_th(t_ms *ms)
{
	pthread_t	t[NB];
	t_ph		ph[NB];
	int			i = 0;

	//Init mutex 'm_lock' to use it in the routine ft
	pthread_mutex_init(&ms->m_lock, NULL);
	//while 'i' is less than NB, attributes the philo id value and attributes the ms struct where each philo will have its own data
	while (i < NB)
	{
		ph[i].id = i + 1; //assign the id per 'i + 1' (to start the 1st id to 1)
		ph[i].data = ms; //assign the data to each philo
		i++;
	}
	i = - 1;
	while (++i < NB)
		pthread_create(&t[i], NULL, &routine, &ph[i]); //create all threads
	i = -1;
	while (++i < NB)
		pthread_join(t[i] , NULL); //join al threads
	//Destroy the mutex ('clean/free' it)
	pthread_mutex_destroy(&ms->m_lock);
}

int main (int ac, char **av)
{ 	
	(void)ac;
	t_ms	*ms;

	ms = ft_init_ms(av); //TODO init the structure only if the args are valid (i.e move it in ft_valid_args)
	// if(!ft_valid_arg(ac, ms))
	// 	return (1);
	ft_create_th(ms);
	printf("\n🚧 "KYEL"Work In Progress 🚧\n"KRT);
	return(0);
}