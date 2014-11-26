#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "symbol_table.h"
#define QUIT "quit"

int main(int argc, char **argv)
{
	FILE *fp;
	Symbol_table st;
	Item i;
	char str[11] = " ";

	if(argc < 2){
		fprintf(stderr, "Parameters error!\nUsage: ./1 <input_file>\n");
		return -1;
	}

	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}

	st = symbol_table_init_from_file(fp);

	while(strcmp(str, QUIT) != 0)
	{
		printf("\nID to search ('quit' to exit) : ");
		scanf("%s", str);
		if(strcmp(str, QUIT) == 0)
			break;
		i = new_item(str,str,str,0,0,0);
		i = symbol_table_search(st, i);
		if(i != NULL)
			print_item(i);
		else
			printf("\nCan't find %s\n", str);
	}

	symbol_table_free(st);

	return 0;
}
