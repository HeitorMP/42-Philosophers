/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:28:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/08 23:29:35 by hmaciel-         ###   ########.fr       */
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

int	init_input(int argc, char **argv, t_root *root)
{
	if (has_input_errors(argc, argv) == TRUE)
		return (FALSE);
	root->input.number_of_philosophers = ft_atoi(argv[1]);
	root->input.time_to_die = ft_atoi(argv[2]);
	root->input.time_to_eat = ft_atoi(argv[3]);
	root->input.time_to_sleep = ft_atoi(argv[4]);
	root->input.times_each_philo_must_eat = 0;
	if (argc == 6)
		root->input.times_each_philo_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&root->input.print_mutex, NULL);
	pthread_mutex_init(&root->input.eat_mutex, NULL);
	pthread_mutex_init(&root->input.dead_mutex, NULL);
	pthread_mutex_init(&root->input.finish_mutex, NULL);
	root->input.start_time = current_time();
	root->input.nb_p_finish = 0;
	return (TRUE);
}
