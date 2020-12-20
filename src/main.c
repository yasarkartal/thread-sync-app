#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define msleep(x)  usleep(x*1000)

/*shared resource*/
int counter = 0;

void* threadA(const char * threadName)
{
    while(1)
    {
        printf("%s start\n", threadName);
        counter++;
        printf("%s counter: %d\n", threadName, counter);
        printf("%s finish\n", threadName);

        msleep(160);
    }
}

int main()
{
    pthread_t thread_A;
    pthread_t thread_B;
    pthread_t thread_C;

    printf("tread-sync-app: start\n");

    /*Create thread: threadA, threadB and threadC*/
    pthread_create(&thread_A, NULL, &threadA, "threadA");
    pthread_create(&thread_B, NULL, &threadA, "threadB");
    pthread_create(&thread_C, NULL, &threadA, "threadC");

    /*Join thread: wait theads termination*/
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);

    printf("main counter: %d\n",counter);

    printf("tread-sync-app: finish\n");

	return 0;
}
