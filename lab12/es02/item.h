#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED
#define MAX_STR 5+1

typedef struct item *Item;

int	item_compare(Item a, Item b);
Item	item_new(char *id, int priority);
void	item_print(Item i, FILE *fp);
void	item_destroy(Item i);

#endif
