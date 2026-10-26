#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room, forks[5];

void *philosopher(void *arg)
{
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i);

    sem_wait(&room);

    sem_wait(&forks[i]);
    sem_wait(&forks[(i + 1) % 5]);

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&forks[i]);
    sem_post(&forks[(i + 1) % 5]);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int id[5];

    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&room);

    for (int i = 0; i < 5; i++)
        sem_destroy(&forks[i]);

    return 0;
}