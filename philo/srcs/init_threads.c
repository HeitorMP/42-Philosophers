/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:37:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 12:20:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static void	init_time(t_philo *ph, t_input *input)
{
	int			i;
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
}

int	init_threads(t_philo *ph, t_input *input)
{
	int			i;
	pthread_t	thread_dead;

	i = 0;
	init_time(ph, input);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		if (pthread_create(&ph[i].thread_id, NULL, \
			simulation, (void *)&ph[i]) != 0)
			return (FALSE);
		i++;
	}
	pthread_create(&thread_dead, NULL, monitoring_dead, ph);
	pthread_join(thread_dead, NULL);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		pthread_join(ph[i].thread_id, NULL);
		i++;
	}
	return (TRUE);
}
