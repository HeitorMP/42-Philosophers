/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/02/22 09:30:58 by hmaciel-         ###   ########.fr       */
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

# define	IDLE 0
# define	EATING 1
# define	SLEEPING 2
# define	THINKING 3

typedef struct s_input
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_philo_must_eat;
}	t_input;

typedef struct s_philo
{
	int		philo_id;
	int		time_to_die;
	char	action;
	int		is_alive;
	int		has_left_fork;
	int		has_right_fork;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t lock_left_fork;
	pthread_mutex_t lock_right_fork;
}	t_mutex;

typedef struct s_root
{
	t_input	input;
	t_philo	*philos;
	t_mutex	forks;
}	t_root;

long long	time_in_milliseconds(void);
int			ft_atoi(const char *str);
int			ft_str_is_numeric(char *str);
void		free_philos(t_root *root);
int			init_philo(t_root *root);
int			init_input(int argc, char **argv, t_root *root);
#endif
