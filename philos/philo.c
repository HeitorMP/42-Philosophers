/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/26 17:23:59 by hmaciel-         ###   ########.fr       */
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

long long	is_event_end(long long event)
{
	long long cur_time;
	long long start_time;

	start_time = time_in_milliseconds();
	cur_time = 0;
	while (1)
	{
		cur_time = time_in_milliseconds() - start_time;
		if (cur_time >= event)
			return (1);
	}
	return (0);
}

int	do_event(t_philo *philo, t_root *root, int event)
{
		printf("%lld - philo: %d - ", root->curr_time, philo->philo_id);
		if (event == 1)
			printf("comendo:\n");
		if (event == 2)
			printf("pensando:\n");
		if (event == 3)
			printf("sofrendo por amor:\n");
		if(is_event_end(root->input.time_to_eat))
			philo->action++;
		if (philo->action == 4)
			philo->action = 1;
}

int main(int argc, char **argv)
{
	t_root	root;
	
	init_input(argc, argv, &root);
	init_philo(&root);
	
	long long start_time;
	root.philo->action = 1;
	start_time = time_in_milliseconds();
	int i = 0;
	while (1)
	{
		root.curr_time = time_in_milliseconds() - start_time;
		do_event(&root.philo[i] ,&root, root.philo[i].action);
		i++;
		if (i == 2)
			i = 0;
	}
	printf("morreu!");
}
