/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo->c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:15:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 23:38:05 by hmaciel-         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

t_philo	 *init_philo(t_input *input)
{
	int	i;
	t_philo *ph;

	ph = (t_philo *)malloc(sizeof(t_philo) * input->number_of_philosophers);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		ph[i].id = i + 1;
		ph[i].last_meal = 0;
		ph[i].number_of_eats = 0;
		ph[i].start_time = 0;
		pthread_mutex_init(&ph[i].left_fork, NULL);
		pthread_mutex_init(&ph[i].dead_mutex, NULL);
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
