#ifndef ITEM_CATEGORIA_H_DEFINED
#define ITEM_CATEGORIA_H_DEFINED

#define MAX_STR 26
#define BASE	127
typedef struct item_category *Item_category;

int 		item_category_compare(void *key_a, void *key_b);
int		item_category_hash(void *key, int M);
void*		item_category_get_key(void *item);
Item_category	item_category_new(char *id);
void		item_category_add_kb(Item_category item, int kb);
void		item_category_add_customer(Item_category item, char *customer_id);
void		item_category_print_customers(Item_category item, FILE *fp);
void		item_category_print_kb(Item_category item, FILE *fp);
void		item_category_free(Item_category item);

#endif
