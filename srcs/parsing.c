/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:39:38 by csenand           #+#    #+#             */
/*   Updated: 2023/08/24 12:39:41 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_isdigit(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	return (true);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	ft_check(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (!ft_isdigit(av[i]))
			return (printf("%s%s%s\n", KRED, ERR_DIGIT, KRT), false);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (printf("%s%s%s\n", KRED, ERR_PH_NB, KRT), false);
	i = 1;
	while (av[++i])
	{
		if (ft_strlen(av[i]) > 10 || ft_atol(av[i]) > INT32_MAX)
			return (printf("%s%s%s\n", KRED, ERR_INT, KRT), false);
		if (i < 5 && ft_atoi(av[i]) < 60)
			return (printf("%s%s%s\n", KRED, ERR_TIME, KRT), false);
		if (i == 5 && ft_atoi(av[5]) < 1)
			return (printf("%s%s%s\n", KRED, ERR_NB_EAT, KRT), false);
	}
	return (true);
}

bool	ft_init_arg(int ac, char **av)
{
	if (ac < 5)
		return (printf("%s%s%s\n", KRED, ERR_ARG1, KRT), false);
	else if (ac > 6)
		return (printf("%s%s%s\n", KRED, ERR_ARG2, KRT), false);
	else if (!ft_check(av))
		return (false);
	return (true);
}
