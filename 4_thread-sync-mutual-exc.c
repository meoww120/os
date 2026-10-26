#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;
pthread_mutex_t mutex;

void *function(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&semaphore);  // Acquire counting semaphore
    pthread_mutex_lock(&mutex);  // Lock mutex

    printf("Thread %d is executing.\n", id);
    sleep(1);
    printf("Thread %d finished.\n", id);

    pthread_mutex_unlock(&mutex);  // Unlock mutex
    sem_post(&semaphore);  // Release semaphore

    return NULL;
}

int main()
{
    pthread_t threads[5];
    int id[5];

    sem_init(&semaphore, 0, 2);  // Allow 2 threads at a time
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; i++)
    {
        id[i] = i + 1;
        pthread_create(&threads[i], NULL, function, &id[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    pthread_mutex_destroy(&mutex);

    return 0;
}