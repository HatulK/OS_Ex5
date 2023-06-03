//
// Created by vboxuser on 6/3/23.
//

#ifndef OS_EX5_QUEUE_PARTB_H
#define OS_EX5_QUEUE_PARTB_H
#define QSIZE 10
#include "bits/pthreadtypes.h"
typedef struct {
    void *data[QSIZE];
    int front;
    int rear;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

void q_init(Queue *queue);

void q_push(Queue *queue,void *element);

void *q_pop(Queue *queue);
#endif //OS_EX5_QUEUE_PARTB_H
