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
#include <stdio.h>

long long	convert_time(t_philo *ph)
{
	return (current_time() - ph->philo_input->start_time);
}

int	is_dead(t_philo *ph)
{
	printf("\n eat %lld\n", (long)ph->ms_eat);
	if ((current_time() - ph->ms_eat) >= (long)ph->philo_input->time_to_die)
		return (TRUE);
	return (FALSE);
}

long long	wait_time(long long time)
{
	long long cur_time;
	long long start_time;

	start_time = current_time();
	cur_time = 0;
	while (1)
	{
		cur_time = current_time() - start_time;
		if (cur_time >= time)
			return (1);
	}
	return (0);
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, is sleeping\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	wait_time(ph->philo_input->time_to_sleep);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, is thinking\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
}

void	try_to_eat_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, has taken a fork\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, has taken a fork\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, is eating\n", convert_time(ph), ph->id);
	ph->ms_eat = current_time();
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	wait_time(ph->philo_input->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_think(ph);
}

void	try_to_eat_odd(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, has taken a fork\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, has taken a fork\n", convert_time(ph), ph->id);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	pthread_mutex_lock(&ph->philo_input->print_mutex);
	printf("%lld - %d, is eating\n", convert_time(ph), ph->id);
	ph->ms_eat = current_time();
	pthread_mutex_lock(&ph->philo_input->eat_mutex);
	pthread_mutex_unlock(&ph->philo_input->eat_mutex);
	pthread_mutex_unlock(&ph->philo_input->print_mutex);
	wait_time(ph->philo_input->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_think(ph);
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;

	while (1)
	{
		if (ph->id % 2 == 0)
			try_to_eat_even(ph);
		else
			try_to_eat_odd(ph);

		if (is_dead(ph))
		{
			printf("morreu");
			exit (0);
		}
	}
	return (NULL);

}

int	init_threads(t_root *root)
{
	int	i;

	i = 0;
	//while (i < root->input.number_of_philosophers)
	while (i < root->input.number_of_philosophers)
	{
		root->philo[i].philo_input = &root->input;
		if (pthread_create(&root->philo[i].thread_id, NULL, simulation, &root->philo[i]) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}


int main(int argc, char **argv)
{
	t_root	root;
	
	if (init_input(argc, argv, &root) == FALSE)
	{
		write(2, "Error: ", 7);
		exit(1);
	}
	if (init_philo(&root) == FALSE)
	{
		write(2, "Philo error", 11);
		exit(1);
	}
	if (init_threads(&root) == FALSE)
	{
		write(2, "threads error", 13);
		exit(1);
	}
	int	i = 0;
	while(i < root.input.number_of_philosophers)
	{
		pthread_join(root.philo[i].thread_id, NULL);
		i++;
	}
}