#ifndef QUEUE_H_DEFINED
#define QUEUE_H_DEFINED

typedef struct queue *Queue;

Queue queue_init();
int queue_empty(Queue q);
int queue_size(Queue q);
void queue_push(Queue q, Item i);
Item queue_pop(Queue s);
Item queue_head(Queue q);
Item queue_tail(Queue q);
void queue_print(Queue q);
void queue_destroy(Queue q);

#endif
