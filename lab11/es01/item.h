#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define MAX_STR 26
typedef struct t_item *Item;

int item_compare(Item a, Item b);
Item item_scan(FILE *fp);
Item item_new(int key, char *str);
void item_print(Item a, FILE *fp);
void item_free(Item a);

#endif
