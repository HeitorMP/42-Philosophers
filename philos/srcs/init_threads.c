/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:37:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 23:54:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	init_threads(t_root *rt)
{
	int			i;
	pthread_t	thread_dead;

	i = 0;
	pthread_create(&thread_dead, NULL, monitoring_dead, &rt->ph[i]);
	while (i < rt->input.number_of_philosophers)
	{
		rt->input.start_time = current_time();
		rt->ph[i].last_meal = rt->input.start_time;
		rt->ph[i].philo_input = &rt->input;
		if (pthread_create(&rt->ph[i].thread_id, NULL, \
			simulation, &rt->ph[i]) != 0)
			return (FALSE);
		i++;
	}
	i = 0;
	pthread_join(thread_dead, NULL);
	while (i < rt->input.number_of_philosophers)
	{
		pthread_join(rt->ph[i].thread_id, NULL);
		i++;
	}
	return (TRUE);
}
