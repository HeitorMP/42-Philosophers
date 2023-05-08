/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/08 23:26:50 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef struct s_input
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						times_each_philo_must_eat;
	int						mili_eat;
	long int				start_time;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t			eat_mutex;
	pthread_mutex_t			finish_mutex;
	int						nb_p_finish;
	int						stop;
}	t_input;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_input					*philo_input;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}							t_philo;

typedef struct s_root
{
	t_input	input;
	t_philo	*philo;
}	t_root;

long long	current_time(void);
long long	wait_time(long long time);
long long	convert_time(t_philo *ph);
int			ft_atoi(const char *str);
int			ft_str_is_numeric(char *str);
int			init_philo(t_root *root);
int			init_input(int argc, char **argv, t_root *root);
void		*simulation(void *philo);
void		try_to_eat_odd(t_philo *ph);
void		try_to_eat_even(t_philo *ph);
void		sleep_and_think(t_philo *ph);
int			is_dead(t_philo *ph);
void		print_action(t_philo *ph, char *action);
#endif
