/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:28:58 by csenand           #+#    #+#             */
/*   Updated: 2023/08/24 12:29:07 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

/* ------------------ COLORS ------------------- */
# define KNRM	"\x1B[m"
# define BLD	"\x1B[1m"
# define KGRE	"\x1B[2m"
# define KITA	"\x1B[3m"
# define KUND	"\x1B[4m"
# define KRED	"\x1B[31m"
# define KGRN	"\x1B[32m"
# define KYEL	"\x1B[33m"
# define KBLU	"\x1B[34m"
# define KMAG	"\x1B[35m"
# define KCYN	"\x1B[36m"
# define KWHT	"\x1B[37m"
# define KRT	"\033[1;0m"

/* ---------------- Error Msgs ---------------- */
# define ERR_ARG1	"❌ Oops ! Not enough arguments ❌"
# define ERR_ARG2	"❌ Oops ! Too many arguments ❌"
# define ERR_DIGIT	"❌ Oops ! Error with an arg (digits > 0 accepted only) ❌"
# define ERR_PH_NB	"❌ Oops ! Error with argv[1] (0 < philo nbr < 200) ❌"
# define ERR_INT	"❌ Oops ! Error with an argument (not a valid integer) ❌"
# define ERR_TIME	"❌ Oops ! Error with an argument (invalid time (< 60 ms)) ❌"
# define ERR_NB_EAT	"❌ Oops ! Error with an argument (invalid times to eat) ❌"
# define ERR_MEM	"❌ Memory allocation failed ❌"
# define PTHC		"❌ pthread_create error ❌"
# define PTHJ		"❌ pthread_join error ❌"

/* ---------------- Status Msg ---------------- */
# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DEAD "died"

# define PICK_RF "has taken a fork"
# define PICK_LF "has taken a fork"
# define DROP_RF "has dropped the right fork"
# define DROP_LF "has dropped th¨e left fork"

//TODO To remove
/* ---------------- DEBUG & TEST ---------------- */
# define DEBUG	0

/* ------------------ STRUCTS ------------------ */
//add a variable to keep track of the nb of meal taken by each philo

typedef struct s_ms
{
	int				philo_nb;	//number_of_philosophers
	int				tt_d;		//time_to_die
	int				tt_e;		//time_to_eat
	int				tt_s;		//time_to_sleep
	int				meal_nb;	//number_of_times_each_philosopher_must_eat
	time_t			start_time;	
	bool			dead;
	pthread_mutex_t	m_lock;		
	pthread_mutex_t	msg;
	pthread_mutex_t	f_lock;
}	t_ms;

typedef struct s_fork
{
	pthread_mutex_t	f_lock;
	bool			used;
}	t_fork;

typedef struct s_ph
{
	int					id;
	int					eat_i;	//eat counter for each philo
	t_fork				left;
	t_fork				*right;
	t_ms				data;
	time_t				time_last_meal;
	pthread_mutex_t		*m_lock;
	pthread_mutex_t		*print_msg;
	pthread_mutex_t		*f_lock;
}	t_ph;

/* ------------------ Parsing ------------------ */
bool	ft_init_arg(int ac, char **av);

/* -------------------- Init ------------------- */
void	ft_init_ms(t_ms *ms, int ac, char **av);
void	ft_init_ph(t_ms *ms, t_ph *ph);

/* ------------------ Routine ------------------ */
void	*routine(void *arg);
void	*routine_solo(void *arg);

/* -------------------- Utils ------------------ */
bool	ft_check_dead();
// bool	print_msg(int match, t_ph *ph);
bool	print_msg(char *str, t_ph *ph);
time_t	ft_timer(void);
void	*ft_free_null(void *ptr);
void	*ft_get_ms(void *ptr);
bool	ft_philo(t_ms *ms, t_ph *ph);
void	ft_destroy_mutex(t_ms *ms, t_ph *ph);


/* -------------- Libft functions -------------- */
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
bool	ft_isdigit(const char *str);
long	ft_atol(const char *str);
void	ft_memcpy(void *src, void *dest, size_t size);


//TODO To remove
void	print_debug(int ac, t_ms *ms, t_ph *ph);

#endif