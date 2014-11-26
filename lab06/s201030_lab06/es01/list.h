#ifndef LIST_H_DEFINED
#define LIST_H_DEFINED

typedef struct list *List;

List list_init();
int list_empty(List l);
int list_size(List l);
void list_push_head(List l, Item i);
void list_push_tail(List l, Item i);
int  list_extract(List l, Item i, int (*compare)(Item a, Item b));
void list_print_search(List l, Item i, int (*compare)(Item a, Item b));
void list_print(List l);
void list_destroy(List l);
#endif
