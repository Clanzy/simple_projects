#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <unistd.h>

/** The maximum length of pipeline/buffer.
 *  Original problem used infinite buffer, but here I use functions that insert/take value in O(n) as an alternative
 */
#define LENGTH 5
/* Typedef just to distinguish The Resource™ from other ints */
typedef int Resource;

Resource pipeline[LENGTH];

sem_t free_pipeline_cells;
sem_t used_pipeline_cells;

pthread_mutex_t pipeline_manipulations;

Resource generate_resource()
{
	Resource stored = rand() % 3 + 1;
	sleep(stored);
	return stored;
}

void put_in_pipeline(Resource r)
{
	for (int i = 0; i < LENGTH; ++i) {
		if (pipeline[i] == 0) {
			pipeline[i] = r;
			return;
		}
	}
}

void *producer()
{
	for (;;) {
        /* First, out producer thread generates the resource */
		Resource r = generate_resource();
		printf("P: generated resource %d\n", r);
        /* Second, it asks if there a free storage in the pipeline. If there is no such, it waits on semaphore */
		sem_wait(&free_pipeline_cells);
        /* It puts it inside the pipeline (mutex-guarded) */
		pthread_mutex_lock(&pipeline_manipulations);
		put_in_pipeline(r);
		pthread_mutex_unlock(&pipeline_manipulations);
        /* Then notifies that there was a resource stored in one of the cells */
		sem_post(&used_pipeline_cells);
        /* Repeat */
	}
}

Resource take_from_pipeline()
{
	for (int i = 0; i < LENGTH; ++i) {
		if (pipeline[i] != 0) {
			Resource stored = pipeline[i];
			pipeline[i] = 0;
			return stored;
		}
	}
	return -1;
}

void process_resource(Resource r)
{
	sleep(2);
	printf("C: processed_resource %d\n", r);
}

void *consumer()
{
	for (;;) {
        /* Consumer thread asks if there any resource to proceed. If there is none, it waits */
		sem_wait(&used_pipeline_cells);
        /* Then it takes it from the pipeline (mutex-guarded) */
		Resource r;
		pthread_mutex_lock(&pipeline_manipulations);
		r = take_from_pipeline();
		pthread_mutex_unlock(&pipeline_manipulations);
        /* Then notifies that there is now a one more free cell in the pipeline */
		sem_post(&free_pipeline_cells);
        /* And process it */
		process_resource(r);
        /* Repeat */
	}
}

int main()
{
	srand(time(NULL));

	pthread_t thread1, thread2;

	sem_init(&free_pipeline_cells, 0, LENGTH);
	sem_init(&used_pipeline_cells, 0, 0);
	pthread_mutex_init(&pipeline_manipulations, NULL);

	pthread_create(&thread1, NULL, producer, NULL);
	pthread_create(&thread2, NULL, consumer, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
    
    sem_close(&free_pipeline_cells);
    sem_close(&used_pipeline_cells);
    pthread_mutex_destroy(&pipeline_manipulations);

	return 0;
}
