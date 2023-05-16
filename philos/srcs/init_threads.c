/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:37:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/16 23:12:53 by hmaciel-         ###   ########.fr       */
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
		if (pthread_create(&ph[i].thread_id, NULL, \
			simulation, (void *)&ph[i]) != 0)
			return (FALSE);
		i++;
	}
	i = 0;
	pthread_create(&thread_dead, NULL, monitoring_dead, (void *)ph);
  	while (i < input->number_of_philosophers)
	{
		pthread_join(ph[i].thread_id, NULL);
		i++;
	}
	pthread_join(thread_dead, NULL);
	return (TRUE);
}
