#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "bst.h"

int main(int argc, char **argv)
{
	Item i;
	BST bst = bst_init();
	int scelta, chiave;
	char str[26];
	FILE *fp;

	//se passo un parametro allora carico subito il bst da file
	if(argc >= 2)
	{
		if((fp = fopen(argv[1],"r")) == NULL){
			fprintf(stderr, "Can't open file %s\n", argv[1]);
			return -1;
		}
		while(fscanf(fp, "%d %s", &chiave, str) != EOF)
		{	
			i = item_new(chiave, str);
			bst_insert_leaf(bst,i);
		}
		fclose(fp);
	}
	
	printf( "============B S T============\n"
		"0 -  Esci dal programma\n"
		"1 -  Inserimento in foglia\n"
		"2 -  Inserimento in radice\n"
		"3 -  Ricerca di un elemento\n"
		"4 -  Stampa minimo e massimo\n"
		"5 -  Stampa a video\n"
		"6 -  Altezza albero\n"
		"7 -  Numero nodi totale\n"
		"8 -  Numero nodi foglia\n"
		"9 -  Salva BST su file\n"
		"10 - Carica BST da file\n");
	do
	{
		printf("\nScelta: ");
		scanf("%d", &scelta);
		switch(scelta)
		{
			case 1:
				printf("Introduci nuvo elemento:\n");
				i = item_scan(stdin);
				bst_insert_leaf(bst, i);
			break;
			case 3:
				printf("Introduci chiave da cercare: ");
				scanf("%d", &chiave);
				i = item_new(chiave," ");
				i = bst_search(bst, i);
				if(i != NULL)
					item_print(i, stdout);
				else
					printf("Elemento non trovato\n");
			break;
			case 5:
				printf("Sampa in\n\t1 - pre ordine\n\t2 - in ordine\n\t3 - post ordine\nScelta: ");
				scanf("%d", &chiave);
				if(chiave == 1)
					bst_print_pre_order(bst, stdout);
				if(chiave == 2)
					bst_print_in_order(bst, stdout);
				if(chiave == 3)
					bst_print_post_order(bst, stdout);
			break;
		}
	}while(scelta != 0);
	
	bst_destroy(bst);

	return 0;
}
