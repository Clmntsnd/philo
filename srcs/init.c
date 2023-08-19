#include "../includes/philo.h"

void	ft_set_data(int ac, char **av, t_ms *ms)
{
	ms->philo_nb = ft_atoi(av[1]);
	ms->tt_d = ft_atoi(av[2]);
	ms->tt_e = ft_atoi(av[3]);
	ms->tt_s = ft_atoi(av[4]);
	if (ac == 6)
		ms->meal_nb = ft_atoi(av[5]);
	else 
		ms->meal_nb = INT_MAX;
	ms->dead = false;
	ms->start_time = 0;
}

t_ms *ft_init_ms(int ac, char **av)
{
	static t_ms	*ms;

	if (!ms)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		ms->m_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		ms->msg = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!ms || !ms->m_lock || !ms->msg)
		{
			ft_free_ms(ms);
			ft_err_exit(ERR_MEM);
		}
		ft_set_data(ac, av, ms);	
		pthread_mutex_init(ms->m_lock, NULL);
		pthread_mutex_init(ms->msg, NULL);
	}
	return(ms);
}

void	ft_init_fork(t_ph **ph, int	nb)
{
	int i;

	i = -1;
	while(++i < nb - 1)
	{
		pthread_mutex_init(ph[i]->right->f_lock, NULL);
		ph[i + 1]->left = ph[i]->right;
	}
	pthread_mutex_init(ph[i]->right->f_lock, NULL);
	if (nb > 1)
		ph[0]->left = ph[i]->right;
}

t_ph	**ft_init_ph(t_ms *ms)
{
	static t_ph	**ph;
	int	i;

	if(!ph)
	{
		ph = ft_calloc(ms->philo_nb + 1, sizeof(t_ph *));
		if(!ph)
		{
			ph = ft_free_null(ph);
			ft_err_exit(ERR_MEM);
		}
		i = -1;
		while (++i < ms->philo_nb)
		{
			ph[i] = ft_calloc(1, sizeof(t_ph));
			ph[i]->right = ft_calloc(1, sizeof(t_fork));
			ph[i]->right->f_lock = ft_calloc(1, sizeof(pthread_mutex_t));
			if (!ph[i] || !ph[i]->right || !ph[i]->right->f_lock)
			{
				ph[i]->right->f_lock = ft_free_null(ph[i]->right->f_lock);
				ph[i]->right = ft_free_null(ph[i]->right);
				ph[i] = ft_free_null(ph[i]);
				ft_err_exit(ERR_MEM);
			}
			ph[i]->id = i + 1;
			ph[i]->eat_i = 0;
			ph[i]->time_last_meal = 0;
			ft_memcpy(ms, &ph[i]->data, sizeof(t_ms));
		}
		ft_init_fork(ph, ms->philo_nb);
	}
	return(ph);
}
