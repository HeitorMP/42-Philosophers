/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_root->input->c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:41:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/26 16:26:56 by hmaciel-         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static int	is_valid_params(int argc, char **argv)
{
	int i;

	i = 1;
	while(i < argc)
	{
		if(ft_str_is_numeric(argv[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_input_errors(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Missing/More params!\n");
		return (FALSE);
	}
	if (is_valid_params(argc, argv) == FALSE)
	{
		printf("Non numeric params!\n");
		return (FALSE);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Invalid number of philos!\n");
		return (FALSE);
	}
	return (TRUE);
}

void	init_input(int argc, char **argv, t_root *root)
{
	root->input.number_of_philosophers = ft_atoi(argv[1]);
	root->input.time_to_die = ft_atoi(argv[2]);
	root->input.time_to_eat = ft_atoi(argv[3]);
	root->input.time_to_sleep = ft_atoi(argv[4]);
	root->input.times_each_philo_must_eat = 0;
	if (argc == 6)
		root->input.times_each_philo_must_eat = ft_atoi(argv[5]);
}
