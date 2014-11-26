#ifndef QUEUE_H_DEFINED
#define QUEUE_H_DEFINED

typedef struct queue *Queue;

Queue queue_init();
int queue_empty(Queue q);
int queue_size(Queue q);
void queue_push(Queue q, Item i);
Item queue_pop(Queue q);
int queue_delete(Queue q, Item i);
int queue_edit(Queue q, Item i);
void queue_print(Queue q);
void queue_destroy(Queue q);

#endif
