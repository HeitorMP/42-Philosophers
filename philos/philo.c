/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 23:34:39 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philos.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_root	rt;
	int		i;

	if (init_input(argc, argv, &rt) == FALSE)
	{
		write(2, "Error: ", 7);
		exit(1);
	}
	rt.ph = malloc(sizeof(t_philo) * rt.input.number_of_philosophers);
	if (!init_philo(&rt))
	{
		write(2, "Philo error", 11);
		exit(1);
	}
 	if (init_threads(&rt) == FALSE)
	{
		write(2, "threads error", 13);
		exit(1);
	}
}
