
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *thread1(void *arg)
{
    printf("Thread 1 waiting for Lock 1...\n");

    pthread_mutex_lock(&lock1);

    printf("Thread 1 acquired Lock 1\n");

    sleep(1);

    printf("Thread 1 waiting for Lock 2...\n");

    pthread_mutex_lock(&lock2);

    printf("Thread 1 acquired Lock 2\n");

    printf("Thread 1 is working...\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    printf("Thread 1 finished.\n\n");

    return NULL;
}

void *thread2(void *arg)
{
    printf("Thread 2 waiting for Lock 1...\n");

    pthread_mutex_lock(&lock1);

    printf("Thread 2 acquired Lock 1\n");

    sleep(1);

    printf("Thread 2 waiting for Lock 2...\n");

    pthread_mutex_lock(&lock2);

    printf("Thread 2 acquired Lock 2\n");

    printf("Thread 2 is working...\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    printf("Thread 2 finished.\n");

    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("\nDeadlock avoided by acquiring locks in the same order.\n");

    return 0;
}
