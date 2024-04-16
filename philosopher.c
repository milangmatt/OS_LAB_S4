/*Name : Milan George Mathew
Class : S4 DS
Roll No : 39
Experiment : 7 - Dining Philosopher's Problem
Date : 16 - 04 - 2024
*/


#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_number + N - 1) % N
#define RIGHT (philosopher_number + 1) % N

int state[N];
int philosophers[N] = {0, 1, 2, 3, 4};
sem_t mutex;
sem_t S[N];

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher_number] = EATING;
        sleep(2);
        printf("Philosopher %d takes chop_stick %d and %d and is eating\n", philosopher_number + 1, LEFT + 1, philosopher_number + 1);
        sem_post(&S[philosopher_number]);
    }
}

void take_chop_stick(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher_number + 1);
    test(philosopher_number);
    sem_post(&mutex);
    sem_wait(&S[philosopher_number]);
    sleep(1);
}

void put_chop_stick(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d putting chop_stick %d and %d down\n", philosopher_number + 1, LEFT + 1, philosopher_number + 1);
    printf("Philosopher %d is thinking\n", philosopher_number + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        take_chop_stick(*i);
        sleep(0);
        put_chop_stick(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}
