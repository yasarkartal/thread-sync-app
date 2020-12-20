//
// Created by yasar on 12/20/20.
//

#ifndef THREAD_SYNC_APP_MAIN_H
#define THREAD_SYNC_APP_MAIN_H

#define msleep(x)  usleep(x*1000)
#define THREAD_PERIOD   160 //MS
#define VERSION         "0.1.0"

void* threadWrite(void *threadName);
void* threadRead(void *threadName);

#endif //THREAD_SYNC_APP_MAIN_H
