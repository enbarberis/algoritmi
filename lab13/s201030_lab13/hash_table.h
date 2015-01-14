#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#define BASE 127

typedef struct hash_table *Hash_table;

Hash_table	hash_table_init(int n);
int		hash_table_insert(Hash_table ht, char *name);
int		hash_table_get(Hash_table ht, char *name);
char*		hash_table_get_name(Hash_table ht, int pos);
void		hash_table_destroy(Hash_table ht);

#endif
