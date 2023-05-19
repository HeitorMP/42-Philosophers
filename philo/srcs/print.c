/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:09:39 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 15:03:31 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	print_action(t_philo *ph, char *action)
{
	pthread_mutex_lock(&ph->philo_input->dead_mutex);
	if (ph->philo_input->stop)
	{
		pthread_mutex_unlock(&ph->philo_input->dead_mutex);
		return ;
	}
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%ldms: Philo-%d, %s\n", convert_time(ph), ph->id, action);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	pthread_mutex_unlock(&ph->philo_input->dead_mutex);
}

int	all_philo_ate(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_input->number_of_philosophers)
	{
		if (ph[i].number_of_eats < ph->philo_input->times_each_philo_must_eat)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_dead(t_philo *ph)
{
	return ((current_time() - ph->last_meal) >= \
	(long)ph->philo_input->time_to_die);
}

void	sleep_and_think(t_philo *ph)
{
	print_action(ph, "is sleeping");
	usleep(ph->philo_input->time_to_sleep * 1000);
	print_action(ph, "is thinking");
	usleep(500);
}
