/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 12:44:15 by hmaciel-         ###   ########.fr       */
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
	int						stop;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			dead_mutex;
}	t_input;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_mutex_t			left_fork;
	pthread_mutex_t			*right_fork;
	long int				last_meal;
	int						number_of_eats;
	long int				start_time;
	t_input					*philo_input;
}							t_philo;

int			init_threads(t_philo *ph, t_input *input);
long		current_time(void);
long long	wait_time(long long time);
long		convert_time(t_philo *ph);
int			ft_atoi(const char *str);
int			ft_str_is_numeric(char *str);
t_philo		*init_philo(t_input *input);
int			init_input(int argc, char **argv, t_input *input);
void		*simulation(void *philo);
void		try_to_eat_odd(t_philo *ph);
void		try_to_eat_even(t_philo *ph);
void		sleep_and_think(t_philo *ph);
int			is_dead(t_philo *ph);
void		print_action(t_philo *ph, char *action);
void		*monitoring_dead(void	*root);
int			all_philo_ate(t_philo *ph);
#endif
