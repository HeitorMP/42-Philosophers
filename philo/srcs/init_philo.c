/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:11:45 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 12:14:55 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

t_philo	*init_philo(t_input *input)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo) * input->number_of_philosophers);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		ph[i].id = i + 1;
		ph[i].last_meal = 0;
		ph[i].number_of_eats = 0;
		ph[i].start_time = 0;
		pthread_mutex_init(&ph[i].left_fork, NULL);
		ph[i].right_fork = NULL;
		if (input->number_of_philosophers == 1)
			ph[0].right_fork = &ph[0].left_fork;
		if (i == input->number_of_philosophers - 1)
			ph[i].right_fork = &ph[0].left_fork;
		else
			ph[i].right_fork = &ph[i + 1].left_fork;
		i++;
	}
	return (ph);
}
