#ifndef ITEM_H
#define ITEM_H

typedef struct item *Item;

Item item_scan();
Item item_new(char *s, int n);
void item_print(Item i, FILE *fp);
void item_free(Item i);

#endif
