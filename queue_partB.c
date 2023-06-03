//
// Created by vboxuser on 6/3/23.
//

#include <pthread.h>
#include "queue_partB.h"
#include "stdio.h"
void q_init(Queue *queue){
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    queue->count = 0;
    queue->front = 0;
    queue->rear = -1;
}

void q_push(Queue *queue,void *element){
    pthread_mutex_lock(&queue->mutex);

    while (queue->count >= QSIZE) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->rear = (queue->rear + 1) % QSIZE;
    queue->data[queue->rear] = element;
    queue->count++;

    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

void *q_pop(Queue *queue){
    pthread_mutex_lock(&queue->mutex);

    while (queue->count <= 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    void *element = queue->data[queue->front];
    queue->front = (queue->front + 1) % QSIZE;
    queue->count--;

    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);

    return element;
}