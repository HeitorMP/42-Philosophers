/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/18 13:07:55 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static int	is_valid_params(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_str_is_numeric(argv[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	has_rrors(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Missing/More params!\n");
		return (TRUE);
	}
	if (is_valid_params(argc, argv) == FALSE)
	{
		printf("Non numeric params!\n");
		return (TRUE);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Invalid number of philos!\n");
		return (TRUE);
	}
	return (FALSE);
}

int	init_input(int argc, char **argv, t_input *input)
{
	if (has_rrors(argc, argv) == TRUE)
		return (FALSE);
	input->number_of_philosophers = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	input->times_each_philo_must_eat = -1;
	if (argc == 6)
		input->times_each_philo_must_eat = ft_atoi(argv[5]);
	if (input->times_each_philo_must_eat == 0)
		return (FALSE);
	pthread_mutex_init(&input->print_mutex, NULL);
	pthread_mutex_init(&input->dead_mutex, NULL);
	input->stop = 0;
	return (TRUE);
}
