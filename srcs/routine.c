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
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->left.f_lock);
	return (used);
}

int	ft_monitor_th(time_t time, t_ph *ph)
{
	t_ms *ms;

	ms = ft_get_ms(NULL);
	if(time < ft_timer())
	{
		pthread_mutex_lock(&ms->m_lock);
		pthread_mutex_lock(ph->print_msg);
		if (ms->dead == false)
		{
			printf("%ld %d %s\n", ft_timer(), ph->id, DEAD_MSG);
			ms->dead = true;
		}
		pthread_mutex_unlock(ph->print_msg);
		pthread_mutex_unlock(&ms->m_lock);
		return (1);
	}
	usleep(100);
	return (0);
}

int	ft_think(t_ph *ph)
{
	print_msg(THINKING, ph);
	usleep(500);
	while(ft_fork_used(ph) == false)
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
			return (1);
	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	if (ft_check_dead() == false)
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
	pthread_mutex_unlock(&ph->data.m_lock);
	ph->left.used = false;
	ph->right->used = false;
	pthread_mutex_unlock(&ph->data.m_lock);
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->left.f_lock);
}

int	ft_eat(t_ph *ph)
{
	time_t time_to_eat;

	time_to_eat = ph->data.tt_e + ft_timer();
	ph->time_last_meal = ph->data.tt_d + ft_timer();
	pthread_mutex_lock(&ph->data.m_lock);
	print_msg(EATING, ph);
	while (ft_timer() < time_to_eat)
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
			return (1);
	pthread_mutex_unlock(&ph->data.m_lock);
	ft_drop_fork(ph);
	return (0);
}


int	ft_sleep(t_ph *ph)
{
	time_t	time_to_sleep;

	time_to_sleep = ph->data.tt_s + ft_timer();
	if(ft_check_dead() == true)
		return (1);
	print_msg(SLEEPING, ph);
	while (ft_timer() < time_to_sleep)
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
			return (1);
	return(0); 
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
		if (ft_think(ph) == 1)
			break ;
		if (ft_eat(ph) == 1)
			break ;
		ph->eat_i++;
		if (ft_sleep(ph) == 1)
			break ;
	}
	return (arg);
}