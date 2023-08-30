/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:51:16 by csenand           #+#    #+#             */
/*   Updated: 2023/08/30 11:50:41 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_fork_used(t_ph *ph)
{
	bool	used;

	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
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
	t_ms	*ms;
	bool	dead;

	ms = ft_get_ms(NULL);
	dead = false;
	if (time < ft_timer())
	{
		pthread_mutex_lock(&ms->m_lock);
		pthread_mutex_lock(ph->print_msg);
		if (ms->dead == false)
		{
			printf("%ld %d %s\n", ft_timer(), ph->id, DEAD);
			ms->dead = true;
			dead = true;
		}
		else
			dead = false;
		pthread_mutex_unlock(&ms->m_lock);
		pthread_mutex_unlock(ph->print_msg);
	}
	usleep(100);
	return (dead);
}
