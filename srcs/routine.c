#include "../includes/philo.h"

bool	ft_fork_used(t_ph *ph)
{
	bool	used;

	pthread_mutex_lock(ph->f_lock);
	//TODO put an if, when philo_nb == 1, to return false
	if (ph->left.used == false && ph->right->used == false)
	{
		ph->left.used = true;
		ph->right->used = true;
		used = true;
	}
	else
		used = false;
	pthread_mutex_unlock(ph->f_lock);
	return (used);
}

bool	ft_think(t_ph *ph)
{
	pthread_mutex_lock(ph->print_msg);
	print_msg(THINKING, ph);
	pthread_mutex_unlock(ph->print_msg);
	usleep(1000);
	while(!ft_fork_used(ph))
	{
		if(ph->time_last_meal < ft_timer())
		{
			pthread_mutex_lock(ph->print_msg);
			if(ph->data.dead == false)
				print_msg(THINKING, ph);
			ph->data.dead = true;
			pthread_mutex_unlock(ph->print_msg);
		}
		ft_usleep(1000);
	}
	//this mutex will be unlicked only after eating (i.e to unlock when dropping forks)
	pthread_mutex_lock(ph->f_lock);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
	return(true);
}


bool	ft_eat(t_ph *ph)
{
	time_t time_to_eat;

	time_to_eat = ph->data.tt_e + ft_timer();
	ph->time_last_meal = ph->data.tt_d + ft_timer();
	pthread_mutex_lock(&ph->data.m_lock);
	// pthread_mutex_lock(ph->m_lock);
	print_msg(EATING, ph);
	// pthread_mutex_unlock(ph->m_lock);
	while (ft_timer() < time_to_eat)
	{
		if(ph->time_last_meal < ft_timer())
		{
			pthread_mutex_lock(ph->print_msg);
			if(ph->data.dead == false)
				print_msg(DEAD, ph);
			ph->data.dead = true;
			pthread_mutex_unlock(ph->print_msg);
		}
		usleep(100);
	}
	pthread_mutex_unlock(&ph->data.m_lock);
	return (true);
}

void	ft_drop_fork(t_ph *ph)
{
	pthread_mutex_unlock(ph->f_lock);
	printf("%ld %d %s\n", ft_timer(), ph->id, DROP_LF);
	printf("%ld %d %s\n", ft_timer(), ph->id, DROP_RF);

	pthread_mutex_unlock(&ph->data.m_lock);
	ph->left.used = false;
	ph->right->used = false;
	pthread_mutex_unlock(&ph->data.m_lock);
}

void	ft_sleep(t_ph *ph)
{
	time_t	time_to_sleep;

	time_to_sleep = ph->data.tt_s + ft_timer();
	if(ph->data.dead == true)
		return ;
	print_msg(SLEEPING, ph);
	while (ft_timer() < time_to_sleep)
	{
		if(ph->time_last_meal < ft_timer())
		{
			pthread_mutex_lock(ph->print_msg);
			if(ph->data.dead == false)
				print_msg(DEAD, ph);
			ph->data.dead = true;
			pthread_mutex_unlock(ph->print_msg);
		}
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_ph *ph;

	ph = (t_ph *)arg;
	// printf("routine starts\n");
	ph->time_last_meal = ph->data.tt_d;
	if (!(ph->id & 1))
		usleep(500);
	while(ph->eat_i < ph->data.meal_nb)
	{
		ft_think(ph);
		ft_eat(ph);
		ft_drop_fork(ph);
		ph->eat_i++;
		ft_sleep(ph);
		// if (ph->eat_i == ph->data.meal_nb)
		// 	break;
		// pthread_mutex_lock(ph->m_lock);
		// ph->eat_i++;
		// pthread_mutex_unlock(ph->m_lock);
	}
	return (arg);
}