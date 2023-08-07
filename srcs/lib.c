#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (sign * res);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*dest;

	dest = (void *)malloc(size * count);
	if (!dest)
		return (0);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}