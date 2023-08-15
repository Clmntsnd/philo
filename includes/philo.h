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
# define ERR_DIGIT	"❌ Oops ! Error with an argument (only digits above 0 are accepted) ❌"
# define ERR_PH_NB	"❌ Oops ! Error with argv[1] (0 < philosophers numbers < 200) ❌"
# define ERR_INT	"❌ Oops ! Error with an argument (not a valid integer) ❌"
# define ERR_TIME	"❌ Oops ! Error with an argument (invalid time (< 60 ms)) ❌"
# define ERR_NB_EAT	"❌ Oops ! Error with an argument (invalid times to eat) ❌"
# define ERR_MEM	"❌ Memory allocation failed ❌"

/* ---------------- Status Msg ---------------- */
# define THINKING 1
# define THINK_MSG "is thinking"
# define EATING 2
# define EAT_MSG "is eating"
# define SLEEPING 3
# define SLEE_MSG "is sleeping"
# define PICK_RF "has taken the right fork"
# define PICK_LF "has taken the left fork"
# define DROP_RF "has dropped the right fork"
# define DROP_LF "has dropped the left fork"

//TODO To remove
/* ---------------- DEBUG & TEST ---------------- */
# define DEBUG	0
# define NB		3

/* ------------------ STRUCTS ------------------ */
//add a variable to keep track of the nb of meal taken by each philo
typedef struct s_ms
{
	int				philo_nb;	//number_of_philosophers
	int				tt_d;		//time_to_die
	int				tt_e;		//time_to_eat
	int				tt_s;		//time_to_sleep
	int 			meal_nb;	//number_of_times_each_philosopher_must_eat
	int				size;		//TODO seems obselete
	int				i;			//TBD
	int				status;		//while be assign to an int that will be defined above 
	pthread_mutex_t	m_lock;		
	pthread_mutex_t	msg;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
}	t_ms;

typedef struct s_ph
{
	int		id;
	int		eat_i;	//eat counter for each philo
	bool	eating;	//is a philo eating or not?
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

void	ft_err_exit(char *str);
void	*routine(void *arg);

//TODO To remove
void	print_debug(int ac, t_ms *ms);


#endif