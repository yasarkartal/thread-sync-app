#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "main.h"

/*shared resource*/
static int counter = 0;

static pthread_mutex_t lock;

void* threadWrite(void *threadName)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        printf("%s start\n", threadName);
        counter++;
        printf("%s counter: %d\n", threadName, counter);
        printf("%s finish\n", threadName);
        pthread_mutex_unlock(&lock);

        msleep(THREAD_PERIOD);
    }
}

void* threadRead(void *threadName)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        printf("%s start\n", threadName);
        printf("%s counter: %d\n", threadName, counter);
        printf("%s finish\n", threadName);
        pthread_mutex_unlock(&lock);

        msleep(THREAD_PERIOD);
    }
}

int main()
{
    pthread_t thread_write[3];
    pthread_t thread_read[1];

    printf("tread-sync-app v%s: start\n", VERSION);


    /*Init mutex*/
    if(pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("thread-sync-app: mutex init failed\n");
    }

    /*Create threads*/
    pthread_create(&thread_write[0], NULL, threadWrite, "thread_write_A");
    pthread_create(&thread_write[1], NULL, threadWrite, "thread_write_B");
    pthread_create(&thread_write[2], NULL, threadWrite, "thread_write_C");
    pthread_create(&thread_read[0], NULL, threadRead, "thread_read_A");

    /*Join thread: wait theads termination*/
    pthread_join(thread_write[0], NULL);
    pthread_join(thread_write[1], NULL);
    pthread_join(thread_write[2], NULL);
    pthread_join(thread_read[0], NULL);

    /*destroy mutex*/
    pthread_mutex_destroy(&lock);

    printf("main counter: %d\n",counter);

    printf("tread-sync-app: finish\n");

    return 0;
}
