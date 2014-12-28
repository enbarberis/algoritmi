#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define	MAX_STR 11
#define BASE	127
typedef struct item *Item;

Item	item_new(char *city, char *region);
Item	item_scan(FILE *fp);
int	item_compare(char *key_a, char *key_b);
int	item_hash(char *key, int m);
char*	item_get_key(Item item);
char*	item_get_region(Item item);
void	item_destroy(Item item);

#endif
