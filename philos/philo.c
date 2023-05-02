/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:30:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/02 14:53:20 by hmaciel-         ###   ########.fr       */
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

void	print_event(t_root *root)
{
	int i = 0;
	while (i < root->input.number_of_philosophers)
	{
		printf("%lld - philo: %d - ", root->curr_time, root->philo[i].philo_id);
		if (root->philo[i].action == 0)
			printf("is thinking\n");
		if (root->philo[i].action == 1)
			printf("is eating\n");
		if (root->philo[i].action == 2)
			printf("is sleeping\n");
		if (root->philo[i].action == 3)
			printf("sofrendo por amor:\n");
		i++;
	}
}

int	can_eat(t_philo *philo, t_root *root)
{
	if (root->philo->philo_id == root->input.number_of_philosophers)
	{
		if (pthread_mutex_lock(&root->fork[root->philo->philo_id - 1]) == 0 && pthread_mutex_lock(&root->fork[0]) == 0)
		{
			philo->action = 1;
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&root->fork[root->philo->philo_id - 1]) == 0 && pthread_mutex_lock(&root->fork[root->philo->philo_id]) == 0)
		{
			philo->action = 1;
			return (1);
		}
	}
	return (0);
}

void *myThreadFun(void *vargp)
{
	t_root *root;
	root = (t_root *)vargp;

	if (can_eat(root->philo, root))
	{
		if (is_event_end(root->input.time_to_eat))
		{
			pthread_mutex_unlock(&root->fork[root->philo->philo_id - 1]);
			pthread_mutex_unlock(&root->fork[root->philo->philo_id]);
			root->philo->action = 2;
		}
	}
    return NULL;
}

int main(int argc, char **argv)
{
	t_root	root;
	
	init_input(argc, argv, &root);
	init_philo(&root);
	int i = 0;
	while (i < root.input.number_of_philosophers)
	{
		pthread_mutex_init(&root.fork[i], NULL);
		i++;
	}

	i = 0;
	
	long long start_time;
	
	start_time = time_in_milliseconds();
	while (i < root.input.number_of_philosophers)
	{
		root.curr_time = time_in_milliseconds() - start_time;
		pthread_create(&root.philo[i].thread, NULL, myThreadFun, &root);
		pthread_join(root.philo[i].thread, NULL);
		print_event(&root);
		i++;
	}
	printf("morreu!");
}
