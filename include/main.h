//
// Created by yasar on 12/20/20.
//

#ifndef THREAD_SYNC_APP_MAIN_H
#define THREAD_SYNC_APP_MAIN_H

#define msleep(x)  usleep(x*1000)
#define THREAD_PERIOD       160 //MS
#define THREAD_NR           4
#define LENGTH_THREAD_NAME  1024

#define VERSION         "0.1.0"

struct ThreadParameter
{
    char threadName[LENGTH_THREAD_NAME];
    pthread_mutex_t *threadLock;
};

void* threadWrite(void *threadName);
void* threadRead(void *threadName);

#endif //THREAD_SYNC_APP_MAIN_H
