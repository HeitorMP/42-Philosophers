/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:15:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/26 16:50:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	init_philo(t_root *root)
{
	int	i;

	root->philo = malloc(sizeof(t_philo) * root->input.number_of_philosophers);
	i = 0;
	while(i < root->input.number_of_philosophers)
	{
		root->philo[i].philo_id = i + 1;
		root->philo[i].is_alive = TRUE;
		root->philo[i].action = 0;
		root->philo[i].has_left_fork = 0;
		root->philo[i].has_right_fork = 0;
		i++;
	}
	root->input.fork = malloc(sizeof(pthread_mutex_t) * root->input.number_of_philosophers);
	i = 0;
	while (i < root->input.number_of_philosophers)
	{
		pthread_mutex_init(&root->input.fork[i], NULL);
		i++;
	}
}
