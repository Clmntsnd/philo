#include "../includes/philo.h"

void	ft_monitor(t_ph *ph)
{
	if (ph->time_last_meal < ft_timer())
	{
		pthread_mutex_lock(ph->print_msg);
		if (ph->data.dead == true)
			print_msg(DEAD, ph);
		pthread_mutex_unlock(ph->print_msg);
	}
}

bool	ft_fork_used(t_ph *ph)
{
	bool	used;

	// printf("fork_used starts\n");
	pthread_mutex_lock(ph->f_lock);
	// printf("ph->left->use = %d\n", ph->left.used);
	// printf("ph->right->use = %d\n", ph->right->used);
	if (ph->left.used == false && ph->right->used == false)
	{
		// printf("take fork\n");
		ph->left.used = true;
		ph->right->used = true;
		used = true;
	}
	else
		used = false;
	pthread_mutex_unlock(ph->f_lock);
	// return (true);
	// printf("fork_used ends\n");
	return (used);
}

bool	ft_think(t_ph *ph)
{
	// printf("fork_used entering\n");
	// printf("ph->data.msg = %p\n", ph->data.msg);

	pthread_mutex_lock(ph->print_msg);
	print_msg(THINKING, ph);
	pthread_mutex_unlock(ph->print_msg);
	usleep(1000);
	while(!ft_fork_used(ph)){
		ft_usleep(100);
	}
	ft_monitor(ph);
	pthread_mutex_lock(ph->f_lock);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
	pthread_mutex_unlock(ph->f_lock);
	return(true);
}

void	ft_drop_fork(t_ph *ph)
{
	pthread_mutex_lock(ph->f_lock);
	// printf("%ld %d %s\n", ft_timer(), ph->id, DROP_LF);
	// printf("%ld %d %s\n", ft_timer(), ph->id, DROP_RF);
	ph->left.used = false;
	ph->right->used = false;
	pthread_mutex_unlock(ph->f_lock);
}

bool	ft_eat(t_ph *ph)
{
	time_t time_to_eat;

	time_to_eat = ph->data.tt_e + ft_timer();
	ph->time_last_meal = ph->data.tt_d + ft_timer();
	
	pthread_mutex_lock(&ph->data.m_lock);
	// pthread_mutex_lock(ph->m_lock);
	print_msg(EATING, ph);
	usleep(ph->data.tt_e);
	// pthread_mutex_unlock(ph->m_lock);
	pthread_mutex_unlock(&ph->data.m_lock);
	// ft_drop_fork(ph);
	return (true);
}



void	*routine(void *arg)
{
	t_ph *ph;

	ph = (t_ph *)arg;
	// printf("routine starts\n");
	if (!(ph->id & 1))
		usleep(500);
	while(ph->eat_i < ph->data.meal_nb)
	{
		// printf("eat_i = %d\n", ph->eat_i);
		ft_think(ph);
		// ft_eat(ph);
		ft_drop_fork(ph);
		ph->eat_i++;
		// if (ph->eat_i == ph->data.meal_nb)
		// 	break;
		// pthread_mutex_lock(ph->m_lock);
		// ph->eat_i++;
		// pthread_mutex_unlock(ph->m_lock);
	}
	return(arg);
}