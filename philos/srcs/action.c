/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:02:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/08 23:47:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	all_philo_ate(t_philo *ph)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (i < ph->philo_input->number_of_philosophers)
	{
		if (ph->nb_eat != ph->philo_input->times_each_philo_must_eat)
		{
			ret = 0;
			break ;
		}
		i++;
	}
	return (ret);
}

int	is_dead(t_philo *ph)
{
	if ((current_time() - ph->ms_eat) >= (long)ph->philo_input->time_to_die)
		return (TRUE);
	return (FALSE);
}

void	sleep_and_think(t_philo *ph)
{
	print_action(ph, "is sleeping");
	wait_time(ph->philo_input->time_to_sleep);
	print_action(ph, "is thinking");
}

void	try_to_eat_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	print_action(ph, "has taken a fork");
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	ph->ms_eat = current_time();
	ph->nb_eat++;
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	wait_time(ph->philo_input->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_and_think(ph);
}

void	try_to_eat_odd(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	pthread_mutex_lock(&ph->left_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	ph->ms_eat = current_time();
	ph->nb_eat++;
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	wait_time(ph->philo_input->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_and_think(ph);
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (is_dead(ph))
			break ;
		if (all_philo_ate(ph))
			exit (0) ;
		if (ph->id % 2 == 0)
			try_to_eat_even(ph);
		else
			try_to_eat_odd(ph);
	}
	return (NULL);
}