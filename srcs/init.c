#include "../includes/philo.h"

void	ft_ms_data(int ac, char **av, t_ms *ms)
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

void	ft_init_ms(t_ms *ms, int ac, char **av)
{
	ft_ms_data(ac, av, ms);
	pthread_mutex_init(&ms->msg, NULL);
	pthread_mutex_init(&ms->m_lock, NULL);
	pthread_mutex_init(&ms->f_lock, NULL);
	ft_get_ms(ms);
}

void	ft_init_fork(t_ph *ph, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (i != nb - 1)
			ph[i].right = &ph[i + 1].left;
		else
			ph[i].right = &ph[0].left;
		pthread_mutex_init(&ph[i].left.f_lock, NULL);
	}
}

void	ft_init_ph(t_ms *ms, t_ph *ph)
{
	int	i;

	i = -1;
	while (++i < ms->philo_nb)
	{
		ph[i].id = i + 1;
		ph[i].eat_i = 0;
		ph[i].left.used = false;
		ft_memcpy(ms, &ph[i].data, sizeof(t_ms));
		ph[i].m_lock = &ms->m_lock;
		ph[i].print_msg = &ms->msg;
		ph[i].f_lock = &ms->f_lock;
	}
	ft_init_fork(ph, ph->data.philo_nb);
}
