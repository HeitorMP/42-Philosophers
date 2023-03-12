/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/12 16:18:51 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

/*
	int gettimeofday ( struct timeval *tp ,  struct timezone *tz )
	time val struct:

	struct    timeval  {
  			time_t        tv_sec ;   //used for seconds
  			suseconds_t       tv_usec ;   //used for microseconds
	}

	struct timezone *tz : NULL because struct timezone is obsolete. This argument is for backwards compatibility only.

*/

/*
	pthread_create - create thread, pthread type, atrib, func, args)
	pthread_detach - make a pthread not joinable

*/

/*1.2 What is a Data Race?

The Thread Analyzer detects data-races that occur during the execution of a multi-threaded process. A data race occurs when:
    - two or more threads in a single process access the same memory location concurrently, and
    - at least one of the accesses is for writing, and
    - the threads are not using any exclusive locks to control their accesses to that memory.
*/

/* TEMPORARY STRUCTS*/

#include "./includes/philos.h"

static void	print_philo(t_root *root)
{
	int i = 0;

	while(i < root->input.number_of_philosophers)
	{
		printf("Philo %d\n", i+1);
		printf("Philo id: %d\n", root->philos[i].philo_id);
		printf("Is alive: %d\n", root->philos[i].is_alive);
		printf("Doing: %d\n", root->philos[i].action);
		printf("Time to die: %d\n", root->philos[i].time_to_die);
		printf("Has left fork: %d\n", root->philos[i].has_left_fork);
		printf("Has right fork: %d\n", root->philos[i].has_right_fork);
		printf("------------------------------------------\n");
		i++;
	}
}

void *action(void *arg)
{
	t_root *root;

	root = (t_root *)arg;


    return NULL;
}

int	main(int argc, char **argv)
{
	t_root	root;
	pthread_t thread1;
	pthread_t thread2;

    pthread_create(&thread1, NULL, action, &root);
	pthread_create(&thread2, NULL, action, &root);

	if (init_input(argc, argv, &root) == FALSE)
		return(1);
	if (init_philo(&root) == FALSE)
		return (1);
	print_philo(&root);
	free_philos(&root);
	return (0);
}
