#include "../includes/philo.h"

/*

https://github.com/TommyJD93/Philosophers#routine

The routine will be the function executed over and over by the philos, and is also going to start the supervisor for each philo.
Basically we have to create a loop that will be interrupted by the death of one of the philos or by reaching the times that each 
of them must eat, in this loop we'll tell them to: eat, sleep and think. But how? Starting from the thinking action, 
a philo has to think whenever he can't eat so it's pretty simple we just have to insert the message "Philo x is thinking". 

Moving on we have the eating action, this one is going to be divided in four main actions: picking the two forks needed, eating, 
dropping the forks and sleeping (you can also make sleeping action apart).

**	1st action
Let's start with the forks picking, this is pretty simple, a philo to pick a fork locks the mutex refered to it so we are going 
to use the pthread_mutex_lock function. Note that if you consider the philos disposed clockwise you are going to lock the right fork 
before the left one, if you consider them disposed counterclockwise then you are going to lock the left one first.

** 2nd action
Now that the philo has taken the forks he need to eat and here we update the status (to do that I've made an int inside the philo struct) 
of the philo so that the supervisor will know that he's eating and he don't have to die, and then we simply use an usleep 
(i suggest you to recode it by your self for making it faster, you can find mine in src/utils/utils.c).

Right after that, before dropping the forks, we update the philo status.
At this point the philo have to drop the froks, we replicate the pick fork function but this time we use the function pthread_muted_unlock 
to unlock the mutexes previously locked. At this point we make the philo sleep using another time the usleep function.

*/

bool	ft_take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->data->msg);
	printf("ph->left.i = %d\n", ph->left.i);
	printf("ph->right.i = %d\n", ph->right->i);
	pthread_mutex_unlock(&ph->data->msg);
	//takes fork
	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	if(ph->left.i == -1 && ph->right->i == -1)
	{
		ph->left.i = ph->id;
		ph->right->i = ph->id;
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
		// pthread_mutex_unlock(&ph->right->f_lock);
		// pthread_mutex_unlock(&ph->left.f_lock);
	}
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->left.f_lock);
	return (true);
}

void	ft_drop_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	ph->left.i = -1;
	ph->right->i = -1;
	printf("%ld %d %s\n", ft_timer(), ph->id, DROP_LF);
	printf("%ld %d %s\n", ft_timer(), ph->id, DROP_RF);
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->left.f_lock);
}

/*
	1st action is to take one dork at a time 
	each philo needs to lock the r_fork before the l_fork

	2nd action is flip the flag if the philo is eating or not
	use the ph->eating to flip to true (inited to false)

	3rd action is to print a message that a philo is eating


*/
void	ft_eat(t_ph *ph) 
{
	ph->time_to_eat = ft_t_stamp(ph) + ph->data->tt_e;
	ph->time_last_meal = ft_t_stamp(ph) + ph->data->tt_d;
	//update eating status
	pthread_mutex_lock(&ph->data->m_lock);

	//print 'is eating' msg
	pthread_mutex_lock(&ph->data->msg);
	print_msg(EATING, ph);
	pthread_mutex_unlock(&ph->data->msg);

	//Increment eat_i variable, to count how many times a philo has eaten
	ph->eat_i++;

	//TODO put a usleep here to represent the time to eat
	usleep(ph->data->tt_e);
	pthread_mutex_unlock(&ph->data->m_lock);

	//drops fork
}

void	ft_think(t_ph *ph)
{
	print_msg(THINKING, ph);
	ft_take_fork(ph);
	ft_drop_fork(ph);
}

void	*routine(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	ph->time_last_meal = ph->data->tt_d;
	if (ph->id % 2 == 0)
		usleep(500);
	while (ph->eat_i < ph->data->meal_nb)
	{
		ft_think(ph);
		// ft_eat(ph);
		ph->eat_i++;

	}
		//TODO add a ft_eat
		//TODO add a ft_sleep

	/*
	**	I needed to put a usleep(10000) and a mutex lock/unlock
	**	for the message to be correctly printed on the prompt
	*/
	usleep(1000);
	pthread_mutex_lock(&ph->data->m_lock);
	printf("id %d was called %d times\n", ph->id, ph->eat_i);
	pthread_mutex_unlock(&ph->data->m_lock);
	return (arg);
}