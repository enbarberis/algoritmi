#ifndef ITEM_CLIENTE_H_DEFINED
#define ITEM_CLIENTE_H_DEFINED

#define MAX_STR 26
#define BASE	127
typedef struct item_customer *Item_customer;

int   		item_customer_compare(void *key_a, void *key_b);
int   		item_customer_hash(void *key, int M);
void* 		item_customer_get_key(void *item);
char* 		item_customer_get_category(Item_customer item);
void		item_customer_add_kb(Item_customer item, int kb);
void 		item_customer_add_time(Item_customer item, int time);
void 		item_customer_add_access(Item_customer item);
Item_customer 	item_customer_scan(FILE *fp);
void 		item_customer_print(Item_customer item, FILE *fp);
void 		item_customer_free(Item_customer item);

#endif
