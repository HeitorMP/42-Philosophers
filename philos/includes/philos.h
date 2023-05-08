/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/02 10:24:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define	TRUE 1
# define	FALSE 0

# define	EATING 1
# define	SLEEPING 2
# define	THINKING 3

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
int			ft_atoi(const char *str);
int			ft_str_is_numeric(char *str);
void		free_philos(t_philo *philo);
int			init_philo(t_root *root);
int			init_input(int argc, char **argv, t_root *root);
#endif
