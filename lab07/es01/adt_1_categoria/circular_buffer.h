#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

typedef struct circular_buffer *Circular_buffer;

Circular_buffer circular_buffer_init(int size);
int circular_buffer_size(Circular_buffer cb);
void circular_buffer_enqueue(Circular_buffer cb, Item i);
Item circular_buffer_dequeue(Circular_buffer cb);
void circular_buffer_print(Circular_buffer cb, FILE *fp);
void circular_buffer_destroy(Circular_buffer cb);

#endif
