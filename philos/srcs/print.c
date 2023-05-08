/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:09:39 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/08 23:29:48 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	print_action(t_philo *ph, char *action)
{
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("Time %lld: Philo-%d, %s\n", convert_time(ph), ph->id, action);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
}
