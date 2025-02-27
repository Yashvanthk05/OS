#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t mutex;
sem_t chopsticks[N];
int state[N];

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d thinking...\n", id + 1);
        sleep(rand() % 3);

        printf("Philosopher %d hungry...\n", id + 1);

        sem_wait(&mutex);
        state[id] = 1; // Hungry

	//picking chopstick
        if (state[(id + 4) % N] != 0 && state[(id + 1) % N] != 0) {
            state[id] = 0; // Eating
            sem_wait(&chopsticks[id]);
            sem_wait(&chopsticks[(id + 1) % N]);
            printf("Philosopher %d takes fork %d and %d...\n", id + 1, id + 1, (id + 1) % N + 1);
            printf("Philosopher %d eating...\n", id + 1);
        }

        sem_post(&mutex);
        sleep(2);

	//dropping chopstick
        sem_wait(&mutex);
        state[id] = 2; // Thinking
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % N]);
        printf("Philosopher %d putting fork %d and %d down\n", id + 1, id + 1, (id + 1) % N + 1);
        printf("Philosopher %d is thinking.\n", id + 1);
        sem_post(&mutex);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
        ids[i] = i;
    }
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
        printf("Philosopher %d thinking...\n", i + 1);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}
