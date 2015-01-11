#ifndef QUEUE_H_DEFINED
#define QUEUE_H_DEFINED

typedef struct queue *Queue;

Queue queue_init();
int queue_empty(Queue q);
int queue_size(Queue q);
void queue_put(Queue q, int i);
int queue_get(Queue q);
void queue_destroy(Queue q);

#endif
