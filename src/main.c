#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "main.h"

/*shared resource*/
int counter = 0;

void* threadWrite(void *threadName)
{
    while(1)
    {
        printf("%s start\n", threadName);
        counter++;
        printf("%s counter: %d\n", threadName, counter);
        printf("%s finish\n", threadName);

        msleep(THREAD_PERIOD);
    }
}

void* threadRead(void *threadName)
{
    while(1)
    {
        printf("%s start\n", threadName);
        printf("%s counter: %d\n", threadName, counter);
        printf("%s finish\n", threadName);

        msleep(THREAD_PERIOD);
    }
}

int main()
{
    pthread_t thread_write[3];
    pthread_t thread_read[1];

    printf("tread-sync-app v%s: start\n", VERSION);

    /*Create thread: threadA, threadB and threadC*/
    pthread_create(&thread_write[0], NULL, threadWrite, "thread_write_A");
    pthread_create(&thread_write[1], NULL, threadWrite, "thread_write_B");
    pthread_create(&thread_write[2], NULL, threadWrite, "thread_write_C");
    pthread_create(&thread_read[0], NULL, threadRead, "thread_read_A");

    /*Join thread: wait theads termination*/
    pthread_join(thread_write[0], NULL);
    pthread_join(thread_write[1], NULL);
    pthread_join(thread_write[2], NULL);
    pthread_join(thread_read[0], NULL);

    printf("main counter: %d\n",counter);

    printf("tread-sync-app: finish\n");

    return 0;
}
