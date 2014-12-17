#ifndef ST_HASH_H_DEFINED
#define ST_HASH_H_DEFINED

typedef struct st_hash *St_hash;

/*Function that initialize the symbol table
 *M = cells number of the table 
 *compare = function to compare 2 items
 *hash = function that calculate the hash of the key within (0) and (M-1)
 *get_key = function to retrive the key field of an item
 */
St_hash st_hash_init(int M, int(*compare)(void *key_a, void *key_b), int(*hash)(void *key, int M), void*(*get_key)(void *item));

/*Function to add an item to the symbol table*/
void st_hash_insert(St_hash st, void *item);

/*search function, it return a pointer to the item so it can be edited*/
void *st_hash_search(St_hash st, void *key);

void  st_hash_start_iteration(St_hash st);
void *st_hash_get_next_item(St_hash st);

/*destroy function*/
void st_hash_destroy(St_hash st);

#endif
