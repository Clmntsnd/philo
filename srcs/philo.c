#include "../includes/philo.h"

void	ft_destroy_mutex(t_ms *ms, t_ph *ph)
{
	pthread_mutex_destroy(&ms->m_lock);
	pthread_mutex_destroy(&ms->msg);
	pthread_mutex_destroy(&ms->f_lock);
	pthread_mutex_destroy(&ph->left.f_lock);
}

void	*routine_solo(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
	usleep(ph->data.tt_d * 1000);
	printf("%ld %d %s\n", ft_timer(), ph->id, DEAD);
	return(0);
}

bool	ft_philo(t_ms *ms, t_ph *ph)
{
	pthread_t	th[200];
	int			i;


	if (ms->philo_nb == 1)
	{
		if (pthread_create(&th[0], NULL, &routine_solo, &ph[0]) != 0)
			return (printf("%s%s%s\n", KRED, PTHC, KRT), false);
		if (pthread_join(th[0], NULL) != 0)
			return (printf("%s%s%s\n", KRED, PTHJ, KRT), false);
	}
	else
	{
		i = -1;
		while (++i < ms->philo_nb)
			if (pthread_create(&th[i], NULL, &routine, &ph[i]) != 0)
				return (printf("%s%s%s\n", KRED, PTHC, KRT), false);
		i = -1;
		while (++i < ms->philo_nb)
			if (pthread_join(th[i], NULL) != 0)
				return (printf("%s%s%s\n", KRED, PTHJ, KRT), false);
	}
	return (true);
}
