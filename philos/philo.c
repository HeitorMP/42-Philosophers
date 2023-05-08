/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/08 23:57:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philos.h"
#include <stdio.h>

int	init_threads(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->input.number_of_philosophers)
	{
		root->philo[i].philo_input = &root->input;
		if (pthread_create(&root->philo[i].thread_id, NULL, \
			simulation, &root->philo[i]) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_root	root;
	int		i;

	if (init_input(argc, argv, &root) == FALSE)
	{
		write(2, "Error: ", 7);
		exit(1);
	}
	if (init_philo(&root) == FALSE)
	{
		write(2, "Philo error", 11);
		exit(1);
	}
	if (init_threads(&root) == FALSE)
	{
		write(2, "threads error", 13);
		exit(1);
	}
	i = 0;
	while (i < root.input.number_of_philosophers)
	{
		pthread_join(root.philo[i].thread_id, NULL);
		i++;
	}
	free(root.philo);
}
