#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_WAITING_CHAIRS 3
#define TOTAL_STUDENTS 10

sem_t sem_stu;
sem_t sem_ta;
pthread_mutex_t mutex;
int waiting_students = 0;

void* ta_function(void* arg) {
    while (1) {
        sem_wait(&sem_stu);
        pthread_mutex_lock(&mutex);

        if (waiting_students > 0) {
            waiting_students--;
            printf("TA is helping a student. Waiting students: %d\n", waiting_students);
            sem_post(&sem_ta);
        } else {
            printf("No students waiting, TA goes to sleep.\n");
        }

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3 + 1);
    }
}

void* student_function(void* arg) {
    int id = *(int*)arg;
    sleep(rand() % 5);

    pthread_mutex_lock(&mutex);
    if (waiting_students < MAX_WAITING_CHAIRS) {
        waiting_students++;
        printf("Student %d is waiting. Waiting students: %d\n", id, waiting_students);
        sem_post(&sem_stu);
        pthread_mutex_unlock(&mutex);

        sem_wait(&sem_ta);
        printf("Student %d is getting help from the TA.\n", id);
    } else {
        printf("Student %d finds no seat and will return later.\n", id);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t ta;
    pthread_t students[TOTAL_STUDENTS];
    int student_ids[TOTAL_STUDENTS];

    sem_init(&sem_stu, 0, 0);
    sem_init(&sem_ta, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&ta, NULL, ta_function, NULL);

    for (int i = 0; i < TOTAL_STUDENTS; i++) {
        student_ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_function, &student_ids[i]);
    }

    for (int i = 0; i < TOTAL_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    return 0;
}
