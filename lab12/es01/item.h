#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define	MAX_STR 11
#define BASE	127
typedef struct item *Item;

int		item_compare(void *key_a, void *key_b);
int		item_hash(void *key, int m);
Item		item_new(char *city, char *region);
Item		item_scan(FILE *fp);
void		item_add_adjacent_node(Item i, int node, int weight);
void		item_destroy(Item i);

#endif
