#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

/* ------------------ COLORS ------------------- */
# define KNRM "\x1B[m"
# define BLD "\x1B[1m"
# define KGRE "\x1B[2m"
# define KITA "\x1B[3m"
# define KUND "\x1B[4m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"
# define KRT  "\033[1;0m"

//TODO To remove
/* ---------------- DEBUG & TEST ---------------- */
# define DEBUG 1
# define NB	3

/* ------------------ STRUCTS ------------------ */
typedef struct s_ms
{
	int				philo_nb; //number_of_philosophers
	int				tt_d; //time_to_die
	int				tt_e; //time_to_eat
	int				tt_s; //time_to_sleep
	int 			meal_nb; //number_of_times_each_philosopher_must_eat
	int				size; 
	int				i;
	pthread_mutex_t	m_lock;
}	t_ms;

typedef struct s_ph
{
	int		id;
	t_ms	*data;
}	t_ph;

/* -------------- Libft functions -------------- */
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
bool	ft_isdigit(const char *str);
long	ft_atol(const char *str);

/* ------------------ Parsing ------------------ */
bool ft_init_arg(int ac, char **av);

//TODO To remove
void	print_debug(int ac);


#endif