// #include "../includes/philo.h"

// bool	ft_fork_used(t_ph *ph)
// {
// 	bool	used;

// 	// printf("fork_used starts\n");
// 	pthread_mutex_lock(ph->data.m_lock);
// 	printf("ph->left->use = %d\n", ph->left->use);
// 	printf("ph->right->use = %d\n", ph->right->use);
// 	if(!ph->left)
// 		used = false;
// 	else if (ph->left->use == 0 && ph->right->use == 0)
// 	{
// 		// printf("take fork\n");
// 		ph->left->use = 1;
// 		ph->right->use = 1;
// 		used = true;
// 		printf("took fork\n");
// 		// return (true);
// 	}
// 	else
// 		used = false;
// 	pthread_mutex_unlock(ph->data.m_lock);
// 	// return (true);
// 	printf("fork_used ends\n");
// 	return (used);
// }

// bool	ft_think(t_ph *ph)
// {
// 	// printf("fork_used entering\n");
// 	// printf("ph->data.msg = %p\n", ph->data.msg);

// 	// pthread_mutex_lock(ph->data.msg);
// 	print_msg(THINKING, ph);
// 	// pthread_mutex_unlock(ph->data.msg);
// 	// usleep(1000);
// 	// while(!ft_fork_used(ph))
// 	// 	ft_usleep(100);
// 	ft_fork_used(ph);
// 	return(true);
// }

// void	ft_drop_fork(t_ph *ph)
// {
// 	if (ph->left){
// 		pthread_mutex_unlock(ph->left->f_lock);
// 		printf("%ld %d %s\n", ft_timer(), ph->id, DROP_LF);
// 	}
// 	pthread_mutex_unlock(ph->right->f_lock);
// 	printf("%ld %d %s\n", ft_timer(), ph->id, DROP_RF);
// 	pthread_mutex_lock(ph->data.m_lock);
// 	ph->left->use = 0;
// 	ph->right->use = 0;
// 	pthread_mutex_lock(ph->data.m_lock);
// }

// // bool	ft_eat(t_ph *ph)
// // {
// // 	time_t time_to_eat;
	
// // 	printf("allo\n");


// // 	time_to_eat = ph->data.tt_e + ft_timer();
// // 	ph->time_last_meal = ph->data.tt_d + ft_timer();	
// // 	pthread_mutex_lock(ph->left->f_lock);
// // 	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_LF);
// // 	pthread_mutex_lock(ph->right->f_lock);
// // 	printf("%ld %d %s\n", ft_timer(), ph->id, PICK_RF);
	
// // 	pthread_mutex_lock(ph->data.m_lock);
// // 	print_msg(EATING, ph);
// // 	ph->eat_i++;
// // 	usleep(time_to_eat);
// // 	pthread_mutex_unlock(ph->data.m_lock);
// // 	ft_drop_fork(ph);
// // 	return (true);
// // }



// void	*routine(void *arg)
// {
// 	t_ph *ph;

// 	ph = (t_ph *)arg;
// 	// printf("routine starts\n");
// 	if (ph->id % 2)
// 		usleep(500);
// 	while(ph->eat_i < ph->data.meal_nb)
// 	{
// 		// printf("eat_i = %d\n", ph->eat_i);
// 		ft_think(ph);
// 		ft_drop_fork(ph);
// 		// ft_eat(ph);
// 		// if (ph->eat_i == ph->data.meal_nb)
// 		// 	break;
// 		ph->eat_i++;
// 	}
// 	return(arg);
// }