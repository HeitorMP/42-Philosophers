/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/17 22:45:02 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"
#include <stdio.h>

/*
void	destroy(t_args *args, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&args->monitoring_mutex);
	if (forks)
	{
		i = 0;
		while (i < args->nbr_of_philo)
		{
			pthread_mutex_destroy(&philos[i].can_die);
			pthread_mutex_destroy(&forks[i]);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
			i += 1;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}*/

int	free_all(t_philo *ph, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->number_of_philosophers)
	{
		pthread_mutex_destroy(&ph[i].dead_mutex);
		pthread_mutex_destroy(&ph[i].dead_mutex);
		i++;
	}
	pthread_mutex_destroy(&input->print_mutex);
	if (ph)
		free(ph);
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_input	input;

	if (init_input(argc, argv, &input) == FALSE)
	{
		write(2, "Error: ", 7);
		exit(1);
	}
	ph = init_philo(&input);
	if (!ph)
	{
		write(2, "Philo error", 11);
		exit(1);
	}
 	if (init_threads(ph, &input) == FALSE)
	{
		write(2, "Threads error", 13);
		exit(1);
	}
	free_all(ph, &input);
}
