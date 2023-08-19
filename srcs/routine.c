#include "../includes/philo.h"

bool	ft_fork_used(t_ph *ph)
{
	pthread_mutex_lock(ph->data.m_lock);
	if(!ph->left)
		return (false);
	else if (ph->left->use == 0 && ph->right->use == 0)
	{
		ph->left->use = 1;
		ph->right->use = 1;
		return (true);
	}
	else
		return (pthread_mutex_unlock(ph->data.m_lock), true);
}

bool	ft_think(t_ph *ph)
{
	print_msg(THINKING, ph);
	usleep(1000);
	while(!ft_fork_used(ph))
		usleep(100);
	pthread_mutex_lock(ph->left->f_lock);
	pthread_mutex_lock(ph->right->f_lock);
	return(true);
}

void	*routine(void *arg)
{
	t_ph *ph;

	ph = (t_ph *)arg;
	if (ph->id % 2)
		usleep(ph->data.tt_e * 500);
	while(ph->eat_i < ph->data.meal_nb)
	{
		ft_think(ph);
		ph->eat_i++;
	}
	return(arg);
}