#include <stdio.h>
#include "item.h"
#include "circular_buffer.h"
#include <stdlib.h>
#include <string.h>

int main()
{
	int size;
	int scelta;
	char file_name[257];
	FILE *fp;
	Circular_buffer cb;
	Item i;

	printf(	"\n===== B U F F E R   C I R C O L A R E=====\n"
		"0 - Crea una coda\n"
		"1 - Stampa cardinalita` della coda\n"
		"2 - Inserisci dato nella coda\n"
		"3 - Estrai dato dalla coda\n"
		"4 - Stampa a video delle coda\n"
		"5 - Stampa su file la coda\n"
		"6 - Carica da file la coda\n"
		"7 - Chiudi il programma\n");
	do
	{
		printf("\nScelta: ");
		scanf("%d", &scelta);
		switch(scelta)
		{
			case 0:
				printf("Dimensione massima: ");
				scanf("%d", &size);
				cb = circular_buffer_init(size);
			break;
			case 1:
				printf("Cardinalita` coda: %d\n", 
					circular_buffer_size(cb));
			break;
			case 2:
				i = item_scan();
				circular_buffer_enqueue(cb, i);
			break;
			case 3:
				i = circular_buffer_dequeue(cb);
				printf("Elemento estratto:\n");
				item_print(i, stdout);
			break;
			case 4:
				circular_buffer_print(cb, stdout);
			break;
			case 5:
				printf("File su cui salvare: ");
				scanf("%s", file_name);
				fp = fopen(file_name,"w");
				fprintf(fp,"%d %d\n",
						circular_buffer_size(cb),
						size);
				circular_buffer_print(cb,fp);
				fclose(fp);
			break;
			case 6:
				printf("File da cui caricare: ");
				scanf("%s", file_name);
				fp=fopen(file_name,"r");
				int j, n, x;
				char s[257], *p;
				fscanf(fp,"%d %d", &n, &size);
				cb = circular_buffer_init(size);
				for(j=0; j<n; j++)
				{
					fscanf(fp,"%s %d", s, &x);
					p = malloc((strlen(s)+1)*sizeof(char));
					strcpy(p,s);
					i = item_new(p,x);
					circular_buffer_enqueue(cb,i);
				}
				fclose(fp);
			break;
		}
	}while(scelta != 7);

	circular_buffer_destroy(cb);
	free(cb);
	
	return 0;
}
