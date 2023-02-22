/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:15:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/02/22 18:22:35 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	init_philo(t_root *root)
{
	int	i;

	root->philos = malloc(sizeof(t_philo) * root->input.number_of_philosophers);
	if(!root->philos)
		return(FALSE);
	i = 0;
	while(i < root->input.number_of_philosophers)
	{
		root->philos[i].philo_id = i + 1;
		root->philos[i].is_alive = TRUE;
		root->philos[i].action = IDLE;
		root->philos[i].time_to_die = root->input.time_to_die;
		root->philos[i].has_left_fork = FALSE;
		root->philos[i].has_right_fork = FALSE;
		i++;
	}
	return (TRUE);
}
