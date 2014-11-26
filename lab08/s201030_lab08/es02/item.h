typedef struct person *Item;

Item new_item(char *id, char *name, char *surname, int day, int month, int year);
int compare_item(Item a, Item b);
void print_item(Item i);
Item scan_item();
void free_item(Item i);
