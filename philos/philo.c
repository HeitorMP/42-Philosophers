/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/16 23:09:29 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philos.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_input	input;

	int		i;

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
	free(ph);
}
