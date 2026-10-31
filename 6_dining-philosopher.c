#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room, fork[5];

void *philosopher(void *arg)
{
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i);

    sem_wait(&room);

    sem_wait(&fork[i]);
    sem_wait(&fork[(i + 1) % 5]);

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&fork[i]);
    sem_post(&fork[(i + 1) % 5]);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t thread[5];
    int id[5];

    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++)
    {
        sem_init(&fork[i], 0, 1);
    }    

    for (int i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&thread[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(thread[i], NULL);

    sem_destroy(&room);

    for (int i = 0; i < 5; i++)
        sem_destroy(&fork[i]);

    return 0;
}
