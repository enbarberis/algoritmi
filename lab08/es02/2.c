#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "queue.h"

int main(int argc, char **argv)
{
	Queue q = queue_init();			//coda
	int scelta = 0;				//scelta del menu
	Item i;					//item per modifica e cancellazione
	char id[11], name[31], surname[31];	//var di lettura
	int day, month, year;			//var di lettura
	
	//carico dati dal file se passato come argomento
	if(argc > 1){
		FILE *fp;
		int j, n;

		if((fp = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Can't open file %s\n", argv[1]);
			return -1;
		}

		fscanf(fp, "%d", &n);
		for(j=0; j<n; j++)
		{
			fscanf(fp,"%s %s %s %d%*c%d%*c%d", id, name, surname, &day, &month, &year);
			i = new_item(id, name, surname, day, month, year);
			queue_push(q, i);
		}
		fclose(fp);
	}

	printf( "====S Y M B O L   T A B L E====\n"
		"1 - Insert new item\n"
		"2 - Edit an item\n"
		"3 - Delete an item\n"
		"4 - Print all\n"
		"5 - Close the program and destroy the symbol table\n");
	while(scelta != 5)
	{
		printf("\nChoice: ");
		scanf("%d", &scelta);
		switch(scelta)
		{
			case 1:
				i = scan_item();
				queue_push(q,i);
			break;
			case 2:
				printf("Item ID to edit: ");
				scanf("%s", id);
				i = new_item(id," ", " ", 0, 0, 0);
				if(queue_edit(q, i))
					printf("Item successfully changed\n");
				else
					printf("Can't find the item\n");
			break;
			case 3:	
				printf("Item ID to delete: ");
				scanf("%s", id);
				i = new_item(id," ", " ", 0, 0, 0);
				if(queue_delete(q, i))
					printf("Item successfully deleted\n");
				else
					printf("Can't find the item\n");
			break;
			case 4:
				queue_print(q);
			break;
		}
	}

	queue_destroy(q);
	return 0;
}

