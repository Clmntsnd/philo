/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:39:04 by csenand           #+#    #+#             */
/*   Updated: 2023/08/30 11:50:43 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_get_ms(void *ptr)
{
	static void	*ms = NULL;

	if (ptr)
		ms = ptr;
	return (ms);
}

// Used to get a timer from the moment philo is starting
//
// To save the exact moment and not modify it each time the function is called,
// the usage of a static variable is helpfull (as in GNL)
time_t	ft_timer(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000));
}

bool	ft_check_dead(void)
{
	t_ms	*ms;
	bool	dead;

	ms = ft_get_ms(NULL);
	pthread_mutex_lock(&ms->m_lock);
	if (ms->dead == true)
		dead = true;
	else
		dead = false;
	pthread_mutex_unlock(&ms->m_lock);
	return (dead);
}

bool	print_msg(char *str, t_ph *ph)
{
	bool	error;

	if (ft_check_dead() == false)
	{
		pthread_mutex_lock(ph->print_msg);
		printf("%ld %d %s\n", ft_timer(), ph->id, str);
		pthread_mutex_unlock(ph->print_msg);
		error = false;
	}
	else
		error = true;
	return (error);
}
