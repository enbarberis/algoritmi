typedef struct symbol_table *Symbol_table;

Symbol_table symbol_table_init_from_file(FILE *fp);
Item symbol_table_search(Symbol_table st, Item i);
void symbol_table_free(Symbol_table st);
