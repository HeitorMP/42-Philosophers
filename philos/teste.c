#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  

typedef struct teste{
	int i;
	pthread_mutex_t lock;
} t_teste;

void *myThreadFun(void *vargp)
{
    t_teste *root;
	root = (t_teste *)vargp;
	//pthread_mutex_lock(&root->lock);
	root->i++;
	//pthread_mutex_unlock(&root->lock);
	//sleep(1);
    
    return NULL;
}
   
int main()
{
	t_teste root;
    pthread_t thread_id;
	pthread_t thread_id2;
	//pthread_mutex_init(&root.lock, NULL);
	int i = 0;
	root.i = 0;
	while(i < 1000)
	{
    	pthread_create(&thread_id, NULL, myThreadFun, &root);
		pthread_create(&thread_id2, NULL, myThreadFun, &root);
    	pthread_join(thread_id, NULL);
		pthread_join(thread_id2, NULL);
		i++;
	}
	printf("%i", root.i);
	//pthread_mutex_destroy(&root.lock);
    exit(0);
}