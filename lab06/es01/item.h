#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define MAX_STR 36
typedef struct t_student *Item;

int compare_name(Item a, Item b);
int compare_surname(Item a, Item b);
int compare_id(Item a, Item b);
int compare_average(Item a, Item b);
Item item_scan();
Item item_new(char *n, char *s, char *i, float a, int c);
void item_print(Item i);
void item_free(Item i);

#endif
