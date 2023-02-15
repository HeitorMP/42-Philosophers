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

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()


int test = 0;
pthread_mutex_t mutex;

void *myThreadFun(void *arg)
{
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		test++;
    	printf("Printing from Thread %d\n", i);
		pthread_mutex_unlock(&mutex);
	}
    return NULL;
}

int	main()
{

	int	number_of_philosophers, number_of_times_each_philosopher_must_eat, number_of_forks;
	time_t time_to_die, time_to_eat ,time_to_sleep;
	struct timeval current_time;

	number_of_philosophers = 5;
	number_of_forks = number_of_philosophers;

	gettimeofday(&current_time, NULL);
	printf("%ld\n", current_time.tv_usec);
	printf("%ld\n", current_time.tv_sec);

	pthread_t thread_id;
	pthread_t thread_id_2;


    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, &mutex);
	pthread_create(&thread_id_2, NULL, myThreadFun, &mutex);
    pthread_join(thread_id, NULL);
	pthread_join(thread_id_2, NULL);
    printf("After Thread %d\n", test);

	return 0;
}
