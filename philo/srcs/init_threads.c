/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:37:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/17 20:20:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	init_threads(t_philo *ph, t_input *input)
{
	int			i;
	pthread_t	thread_dead;
	long int	start;

 	i = 0;
	start = current_time();
	while (i < input->number_of_philosophers)
	{
		ph[i].start_time = start;
		ph[i].last_meal = start;
		ph[i].philo_input = input;
		i++;
	}
	i = 0;
	while (i < input->number_of_philosophers)
	{
		if (pthread_create(&ph[i].thread_id, NULL, \
			simulation, (void *)&ph[i]) != 0)
			return (FALSE);
		i++;
	}
	pthread_create(&thread_dead, NULL, monitoring_dead, ph);
	i = 0;
  	while (i < input->number_of_philosophers)
	{
		pthread_join(ph[i].thread_id, NULL);
		i++;
	}
	pthread_join(thread_dead, NULL);
	return (TRUE);
}
