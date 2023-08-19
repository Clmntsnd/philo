#include "../includes/philo.h"

bool	ft_fork_used(t_ph *ph)
{
	pthread_mutex_lock(&ph->data.m_lock);
	if(!ph->left)
		return (false);
	else if (ph->left->use == 0 && ph->right->use == 0)
	{
		ph->left->use = 1;
		ph->right->use = 1;
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&ph->data.m_lock);
		return (true);
	}
}

bool	ft_think(t_ph *ph)
{
	// pthread_mutex_lock(&ph->data.msg);
	print_msg(THINKING, ph);
	// pthread_mutex_unlock(&ph->data.msg);
	usleep(1000);
	while(!ft_fork_used(ph))
		ft_usleep(50);
	return(true);
}

void	ft_drop_fork(t_ph *ph)
{
	if (ph->left)
		pthread_mutex_unlock(&ph->left->f_lock);
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_lock(&ph->data.m_lock);
	ph->left->use = 0;
	ph->right->use = 0;
	pthread_mutex_lock(&ph->data.m_lock);
}

bool	ft_eat(t_ph *ph)
{
	time_t time_to_eat;

	time_to_eat = ph->data.tt_e + ft_timer();
	ph->time_last_meal = ph->data.tt_d + ft_timer();	
	pthread_mutex_lock(&ph->left->f_lock);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
	pthread_mutex_lock(&ph->right->f_lock);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
	
	pthread_mutex_lock(&ph->data.m_lock);
	print_msg(EATING, ph);
	ph->eat_i++;
	usleep(time_to_eat);
	pthread_mutex_unlock(&ph->data.m_lock);
	ft_drop_fork(ph);
	return (true);
}



void	*routine(void *arg)
{
	t_ph *ph;

	ph = (t_ph *)arg;
	if (!(ph->id & 1))
		usleep(500);
	while(ph->eat_i < ph->data.meal_nb)
	{
		ft_think(ph);
		ft_eat(ph);
		if (ph->eat_i == ph->data.meal_nb)
			break;
	}
	return(arg);
}