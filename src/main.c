#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "main.h"

/*shared resource*/
static int counter = 0;

void* threadWrite(void *threadParameter)
{
    struct ThreadParameter *parameter = (struct ThreadParameter*) threadParameter;

    while(1)
    {
        pthread_mutex_lock(parameter->threadLock);
        printf("%s start\n", parameter->threadName);
        counter++;
        printf("%s counter: %d\n", parameter->threadName, counter);
        printf("%s finish\n", parameter->threadName);
        pthread_mutex_unlock(parameter->threadLock);

        msleep(THREAD_PERIOD);
    }
}

void* threadRead(void *threadParameter)
{
    struct ThreadParameter *parameter = (struct ThreadParameter*) threadParameter;

    while(1)
    {
        pthread_mutex_lock(parameter->threadLock);
        printf("%s start\n", parameter->threadName);
        printf("%s counter: %d\n", parameter->threadName, counter);
        printf("%s finish\n", parameter->threadName);
        pthread_mutex_unlock(parameter->threadLock);

        msleep(THREAD_PERIOD);
    }
}

int main()
{
    pthread_t thread_write[3];
    pthread_t thread_read[1];
    pthread_mutex_t lock;
    struct ThreadParameter *threadParameter[THREAD_NR];

    printf("tread-sync-app v%s: start\n", VERSION);

    /*Init mutex*/
    if(pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("thread-sync-app: mutex init failed\n");
    }

    /*Initialize thread parameters*/
    for(int i = 0; i<THREAD_NR; i++)
    {
        threadParameter[i] = malloc(sizeof(struct ThreadParameter));
        sprintf(threadParameter[i]->threadName,"thread_id_%d",i);
        threadParameter[i]->threadLock = &lock;
    }

    /*Create threads*/
    pthread_create(&thread_write[0], NULL, threadWrite, threadParameter[0]);
    pthread_create(&thread_write[1], NULL, threadWrite, threadParameter[1]);
    pthread_create(&thread_write[2], NULL, threadWrite, threadParameter[2]);
    pthread_create(&thread_read[0], NULL, threadRead, threadParameter[3]);

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
