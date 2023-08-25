/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loulou <loulou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:46:08 by csenand           #+#    #+#             */
/*   Updated: 2023/08/25 12:18:55 by loulou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_think(t_ph *ph)
{
	if (ft_check_dead() == true)
		return (1);
	print_msg(THINKING, ph);
	usleep(500);
	while (ft_fork_used(ph) == false)
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
			return (1);
	if (ft_check_dead() == false)
	{
		pthread_mutex_lock(ph->print_msg);
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
		printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
		pthread_mutex_unlock(ph->print_msg);
		return (0);
	}
	return (1);
}

void	ft_drop_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->left.f_lock);
	pthread_mutex_lock(&ph->right->f_lock);
	ph->left.used = false;
	ph->right->used = false;
	pthread_mutex_unlock(&ph->right->f_lock);
	pthread_mutex_unlock(&ph->left.f_lock);
}

int	ft_eat(t_ph *ph)
{
	time_t	time_to_eat;

	if (ft_check_dead() == true)
	{
		ft_drop_fork(ph);
		return (1);
	}
	time_to_eat = ph->data.tt_e + ft_timer();
	if (print_msg(EATING, ph) == true)
	{
		ft_drop_fork(ph);
		return (1);
	}
	while (ft_timer() < time_to_eat)
	{
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
		{
			ft_drop_fork(ph);
			return (1);
		}
	}
	ph->time_last_meal = ph->data.tt_d + ft_timer();
	ft_drop_fork(ph);
	return (0);
}

int	ft_sleep(t_ph *ph)
{
	time_t	time_to_sleep;

	if (ft_check_dead() == true)
		return (1);
	time_to_sleep = ph->data.tt_s + ft_timer();
	print_msg(SLEEPING, ph);
	while (ft_timer() < time_to_sleep)
		if (ft_monitor_th(ph->time_last_meal, ph) == 1)
			return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	ph->time_last_meal = ph->data.tt_d;
	if (!(ph->id & 1))
		usleep(500);
	while (ph->eat_i < ph->data.meal_nb)
	{
		if (ft_think(ph) == 1)
			break ;
		if (ft_eat(ph) == 1)
			break ;
		ph->eat_i++;
		if (ft_sleep(ph) == 1)
			break ;
	}
	ft_drop_fork(ph);
	return (arg);
}
