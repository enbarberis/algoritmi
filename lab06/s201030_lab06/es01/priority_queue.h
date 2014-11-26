#ifndef PRIORITY_QUEUE_H_DEFINED
#define PRIORITY_QUEUE_H_DEFINED

typedef struct priority_queue *Priority_queue;

Priority_queue priority_queue_init();
int priority_queue_empty(Priority_queue q);
int priority_queue_size(Priority_queue q);
void priority_queue_push(Priority_queue q, Item i, int (*compare)(Item a, Item b));
Item priority_queue_pop(Priority_queue q);
void priority_queue_print(Priority_queue q);
void priority_queue_destroy(Priority_queue q);

#endif
