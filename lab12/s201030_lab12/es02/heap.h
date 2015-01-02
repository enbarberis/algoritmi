#ifndef HEAP_H_DEFINED
#define HEAP_H_DEFINED
#define INIT_SIZE 2

typedef struct heap *Heap;

Heap	heap_init();
void	heap_insert(Heap h, Item i);
Item	heap_extract(Heap h);
void	heap_destroy(Heap h);

#endif
