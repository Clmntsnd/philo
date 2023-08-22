#include "../includes/philo.h"

bool	ft_fork_used(t_ph *ph)
{
	bool	used;

	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	//TODO put an if, when philo_nb == 1, to return false
	if (ph->left.used == false && ph->right->used == false)
	{
		ph->left.used = true;
		ph->right->used = true;
		used = true;
	}
	else
		used = false;
	pthread_mutex_unlock(&ph->left.f_lock);
	pthread_mutex_unlock(&ph->right->f_lock);
	return (used);
}

void	ft_monitor_th(t_ph *ph)
{
	t_ms *ms;

	ms = ft_get_ms(NULL);
	pthread_mutex_lock(ph->print_msg);
	if (ms->dead == false)
		print_msg(DEAD, ph);
	ms->dead = true;
}

bool	ft_think(t_ph *ph)
{
	print_msg(THINKING, ph);
	usleep(500);
	while(ft_fork_used(ph) == false)
	{
		if(ph->time_last_meal < ft_timer())
			ft_monitor_th(ph);
		usleep(100);
	}
	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	if (ph->data.dead == false)
	{
		pthread_mutex_lock(ph->print_msg);
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
		pthread_mutex_unlock(ph->print_msg);
	}
	return(false);
}

void	ft_drop_fork(t_ph *ph)
{
	pthread_mutex_unlock(&ph->left.f_lock);
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->data.m_lock);
	ph->left.used = false;
	ph->right->used = false;
	pthread_mutex_unlock(&ph->data.m_lock);
}

bool	ft_eat(t_ph *ph)
{
	time_t time_to_eat;

	time_to_eat = ph->data.tt_e + ft_timer();
	ph->time_last_meal = ph->data.tt_d + ft_timer();
	pthread_mutex_lock(&ph->data.m_lock);
	print_msg(EATING, ph);
	while (ft_timer() < time_to_eat)
	{
		if(ph->time_last_meal < ft_timer())
			ft_monitor_th(ph);
		usleep(100);
	}
	pthread_mutex_unlock(&ph->data.m_lock);
	ft_drop_fork(ph);
	return (false);
}


bool	ft_sleep(t_ph *ph)
{
	time_t	time_to_sleep;

	time_to_sleep = ph->data.tt_s + ft_timer();
	// if(ph->data.dead == true)
	// 	return (true);
	print_msg(SLEEPING, ph);
	while (ft_timer() < time_to_sleep)
	{
		if(ph->time_last_meal < ft_timer())
			ft_monitor_th(ph);
		usleep(100);
	}
	printf("allo\n");
	return(false); 
}

void	*routine(void *arg)
{
	t_ph *ph;

	ph = (t_ph *)arg;
	ph->time_last_meal = ph->data.tt_d;
	if (!(ph->id & 1))
		usleep(500);
	while(ph->eat_i < ph->data.meal_nb)
	{
		if (ft_think(ph))
			break;
		if (ft_eat(ph))
			break;
		ph->eat_i++;
		if (ft_sleep(ph))
			break ;
	}
	//TODO to remove
	printf("Salut"); 
	//TODO Close all mutex here
	pthread_mutex_unlock(&ph->left.f_lock);
	pthread_mutex_unlock(&ph->right->f_lock);
	return (arg);
}