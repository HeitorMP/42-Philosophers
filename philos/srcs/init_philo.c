/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:15:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/02 11:42:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	init_philo(t_root *root)
{
	int	i;

	root->philo = malloc(sizeof(t_philo) * root->input.number_of_philosophers);
	if (!root->philo)
		return (FALSE);
	i = 0;
	while(i < root->input.number_of_philosophers)
	{
		root->philo[i].id = i + 1;
		root->philo[i].ms_eat = root->input.start_time;
		root->philo[i].nb_eat = 0;
		root->philo[i].finish = 0;
		root->philo[i].right_fork = NULL;
		pthread_mutex_init(&root->philo[i].left_fork, NULL);
		if (root->input.number_of_philosophers == 1)
			return (TRUE);
		if (i == root->input.number_of_philosophers - 1)
			root->philo[i].right_fork = &root->philo[0].left_fork;
		else
			root->philo[i].right_fork = &root->philo[i + 1].left_fork;
		i++;
	}
	return (TRUE);
}