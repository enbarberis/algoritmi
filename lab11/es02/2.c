#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item_customer.h"
#include "item_category.h"
#include "st_hash.h"

int main(int argc, char **argv)
{
	St_hash st_customer, st_category;
	FILE *fp;
	Item_customer customer;
	Item_category category;
	int i, n_customers = 0;
	int kb, time;
	char str[MAX_STR];

	if(argc < 6){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo %s <file_clienti> <file_traffico> <out1> <out2> <out3>\n", argv[0]);
		return -1;
	}

	//carico i clienti
	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
		return -2;
	}
	
	//conto le righe del file
	while(fscanf(fp, "%s %s %s %s",str,str,str,str) == 4)
		n_customers++;
	rewind(fp);
	st_customer = st_hash_init(n_customers, item_customer_compare, item_customer_hash, item_customer_get_key);
	st_category = st_hash_init(n_customers, item_category_compare, item_category_hash, item_category_get_key);
	for(i=0; i<n_customers; i++)
	{
		customer = item_customer_scan(fp);
		st_hash_insert(st_customer, customer);
		category = st_hash_search(st_category, item_customer_get_category(customer));
		if(category == NULL)
		{
			category = item_category_new(item_customer_get_category(customer));
			st_hash_insert(st_category, category);
		}
		item_category_add_customer(category, item_customer_get_key(customer));
	}
	fclose(fp);

	//carico traffico
	if((fp = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
		return -3;
	}
	while(fscanf(fp, "%s %d %d", str, &kb, &time) == 3)
	{
		customer = st_hash_search(st_customer, str);
		category = st_hash_search(st_category, item_customer_get_category(customer));
		item_customer_add_kb(customer, kb);
		item_customer_add_time(customer, time);
		item_customer_add_access(customer);
		item_category_add_kb(category, kb);
	}

	fp = fopen(argv[3], "w");
	st_hash_start_iteration(st_category);
	while((category = st_hash_get_next_item(st_category)) != NULL)
		item_category_print_kb(category, fp);
	fclose(fp);

	fp = fopen(argv[4], "w");
	st_hash_start_iteration(st_category);
	while((category = st_hash_get_next_item(st_category)) != NULL)
		item_category_print_customers(category, fp);
	fclose(fp);

	fp = fopen(argv[5], "w");
	st_hash_start_iteration(st_customer);
	while((customer = st_hash_get_next_item(st_customer)) != NULL)
		item_customer_print(customer, fp);
	fclose(fp);

	//free memory
	st_hash_start_iteration(st_category);
	while((category = st_hash_get_next_item(st_category)) != NULL)
		item_category_free(category);
	st_hash_destroy(st_customer);
	return 0;
}
