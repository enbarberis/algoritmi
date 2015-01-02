#include <stdio.h>
#include "item.h"
#include "heap.h"

int main(int argc, char **argv)
{
	Heap h = heap_init();
	FILE *fp;
	char id[MAX_STR];
	int priority, scelta;
	Item item;

	if(argc > 1 )
	{
		if((fp = fopen(argv[1], "r")) == NULL)
		{
			fprintf(stderr, "Impossibile aprire il file\n");
			return -1;
		}
		while(fscanf(fp, "%s %d", id, &priority) == 2)
			heap_insert(h, item_new(id, priority));
		fclose(fp);
	}

	printf( "===== H E A P =====\n"
		"1 - Inserisci cliente in coda\n"
		"2 - Estrai cliente dalla coda\n"
		"3 - Esci dal programma\n");
	do
	{
		printf("\nScelta: ");
		scanf("%d", &scelta);

		switch(scelta)
		{
			case 1:
				printf("Id: ");
				scanf("%s", id);
				printf("Priorita`: ");
				scanf("%d", &priority);
				heap_insert(h, item_new(id, priority));
			break;

			case 2:
				item = heap_extract(h);
				if(item != NULL)
				{
					item_print(item, stdout);
					item_destroy(item);
				}
				else
					printf("Coda vuota!\n");
			break;
		}
	
	}while(scelta != 3);

	heap_destroy(h);

	return 0;
}
