/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:02:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 12:48:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	try_to_eat_even(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->left_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->dead_mutex);
	ph->last_meal = current_time();
	ph->number_of_eats++;
	pthread_mutex_unlock(&ph->philo_input->dead_mutex);
	usleep(ph->philo_input->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleep_and_think(ph);
}

void	try_to_eat_odd(t_philo *ph)
{		
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->dead_mutex);
	ph->last_meal = current_time();
	ph->number_of_eats++;
	pthread_mutex_unlock(&ph->philo_input->dead_mutex);
	usleep(ph->philo_input->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleep_and_think(ph);
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&ph->philo_input->dead_mutex);
		if (ph->philo_input->stop == 1)
			break ;
		pthread_mutex_unlock(&ph->philo_input->dead_mutex);
		if (ph->id % 2 == 0)
			try_to_eat_even(ph);
		else
			try_to_eat_odd(ph);
	}
	pthread_mutex_unlock(&ph->philo_input->dead_mutex);
	return (NULL);
}

static int	inner_check_death(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_input->number_of_philosophers)
	{
		pthread_mutex_lock(&ph->philo_input->dead_mutex);
		if (is_dead(&ph[i]))
		{
			printf(" Philo %d, is dead!", ph[i].id);
			ph->philo_input->stop = 1;
			pthread_mutex_unlock(&ph->philo_input->dead_mutex);
			return (TRUE);
		}
		pthread_mutex_unlock(&ph->philo_input->dead_mutex);
		i++;
	}
	return (FALSE);
}

void	*monitoring_dead(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (inner_check_death(ph))
			return (NULL);
		pthread_mutex_lock(&ph->philo_input->dead_mutex);
		if (ph->philo_input->times_each_philo_must_eat != -1 && \
			all_philo_ate(ph))
		{
			ph->philo_input->stop = 1;
			pthread_mutex_unlock(&ph->philo_input->dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->philo_input->dead_mutex);
	}
}
