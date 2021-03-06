#include "request_queue.h"

int request_queue_init(struct request_queue *q)
{
    q->front = 0;
    q->rear = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cv_notfull, NULL);
    pthread_cond_init(&q->cv_notempty, NULL);
    return 0;
}

int request_queue_destroy(struct request_queue *q)
{
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->cv_notfull);
    pthread_cond_destroy(&q->cv_notempty);
    return 0;
}

int request_queue_push(struct request_queue *q, struct request *req)
{
    pthread_mutex_lock(&q->mutex);
    int new_rear = (q->rear+1) % REQUEST_QUEUE_SIZE;
    while (new_rear == q->front) {
        // full
        pthread_cond_wait(&q->cv_notfull, &q->mutex);
        new_rear = (q->rear+1) % REQUEST_QUEUE_SIZE;
    }
    q->reqs[q->rear] = req;
    q->rear = new_rear;
    pthread_mutex_unlock(&q->mutex);
    pthread_cond_signal(&q->cv_notempty);
    return 0;
}

int request_queue_pop(struct request_queue *q, struct request **p_req)
{
    pthread_mutex_lock(&q->mutex);
    while (q->front == q->rear) {
        // empty
        pthread_cond_wait(&q->cv_notempty, &q->mutex);
    }
    *p_req = q->reqs[q->front];
    q->front = (q->front+1) % REQUEST_QUEUE_SIZE;
    pthread_mutex_unlock(&q->mutex);
    pthread_cond_signal(&q->cv_notfull);
    return 0;
}