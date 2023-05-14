/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt->input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:28:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/14 22:23:44 by hmaciel-         ###   ########.fr       */
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

static int	has_input_errors(int argc, char **argv)
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

int	init_input(int argc, char **argv, t_root *rt)
{
	if (has_input_errors(argc, argv) == TRUE)
		return (FALSE);
	rt->input.number_of_philosophers = ft_atoi(argv[1]);
	rt->input.time_to_die = ft_atoi(argv[2]);
	rt->input.time_to_eat = ft_atoi(argv[3]);
	rt->input.time_to_sleep = ft_atoi(argv[4]);
	rt->input.times_each_philo_must_eat = 0;
	if (argc == 6)
		rt->input.times_each_philo_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&rt->input.print_mutex, NULL);
	pthread_mutex_init(&rt->input.eat_mutex, NULL);
	pthread_mutex_init(&rt->input.dead_mutex, NULL);
	pthread_mutex_init(&rt->input.finish_mutex, NULL);
	rt->input.start_time = 0;
	return (TRUE);
}
