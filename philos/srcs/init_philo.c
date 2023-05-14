/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:15:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 23:38:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	init_philo(t_root *rt)
{
	int	i;
	
	i = 0;
	while (i < rt->input.number_of_philosophers)
	{
		rt->ph[i].id = i + 1;
		rt->ph[i].last_meal = 0;
		rt->ph[i].number_of_eats = 0;
		rt->ph[i].finish = 0;
		rt->ph[i].dead = FALSE;
		rt->ph[i].right_fork = NULL;
		pthread_mutex_init(&rt->ph[i].left_fork, NULL);
		if (i == rt->input.number_of_philosophers - 1)
			rt->ph[i].right_fork = &rt->ph[0].left_fork;
		else
			rt->ph[i].right_fork = &rt->ph[i + 1].left_fork;
		i++;
	}
	return (TRUE);
}
