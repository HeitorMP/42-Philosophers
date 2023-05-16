/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:02:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 23:52:12 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	all_philo_ate(t_philo *ph)
{
	int i;

	i = 0;
	while(i < ph->philo_input->number_of_philosophers)
	{
		if (ph[i].number_of_eats < ph->philo_input->times_each_philo_must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	is_dead(t_philo *ph)
{
	return ((current_time() - ph->last_meal) >= (long)ph->philo_input->time_to_die);
}

void	sleep_and_think(t_philo *ph)
{
	print_action(ph, "is sleeping");
	usleep(ph->philo_input->time_to_sleep * 1000);
	print_action(ph, "is thinking");
}

/* void	try_to_eat_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	print_action(ph, "has taken a fork");
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	ph->last_meal = current_time();
	ph->number_of_eats++;
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	usleep(ph->philo_input->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleep_and_think(ph);
} */

 void	try_to_eat_odd(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	pthread_mutex_lock(&ph->left_fork);
	print_action(ph, "has taken a fork");
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	ph->last_meal = current_time();
	ph->number_of_eats++;
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	usleep(ph->philo_input->time_to_eat * 1000);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_and_think(ph);
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	int i = 0;
  	while (ph->philo_input->stop != 1)
	{
 		if (ph->id % 2 == 0 && ph->philo_input->first_run)
		{
			usleep(300);
			ph->philo_input->first_run = 0;
		}
		else
		{
			try_to_eat_odd(ph);
		}
	}
	return (NULL);
}

void	*monitoring_dead(void *philo)
{
	t_philo	*ph;
	int	i;

	i = 0;
	int j = 0;
	ph = (t_philo *)philo;
 	while(ph->philo_input->stop != 1)
	{
		while (i < ph->philo_input->number_of_philosophers)
		{
			if (is_dead(&ph[i]))
			{
				pthread_mutex_lock(&ph->philo_input->dead_mutex);
				print_action(&ph[i], "is dead");
				while (j < ph->philo_input->number_of_philosophers)
				{
					ph[j].philo_input->stop = 1;
					j++;
				}
				pthread_mutex_unlock(&ph->philo_input->dead_mutex);
				break ;
			}
			i++;
		}
		i = 0;
		j = 0;
 		if (all_philo_ate(ph) && ph->philo_input->times_each_philo_must_eat != -1)
		{
			while (i < ph->philo_input->number_of_philosophers)
			{
				ph[i].philo_input->stop = 1;
				i++;
			}
			break ;
		}
	}
	return (NULL);
}
