#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "bst.h"

void carica_file(BST bst, char *file);

int main(int argc, char **argv)
{
	Item i;
	BST bst = bst_init();
	int scelta, chiave;
	char file[256];
	FILE *fp;

	//se passo un parametro allora carico subito il bst da file
	if(argc >= 2)
		carica_file(bst, argv[1]);
	
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
			case 2:
				printf("Introduci nuvo elemento:\n");
				i = item_scan(stdin);
				bst_insert_root(bst, i);
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
			case 4:
				bst_print_min_max(bst);
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
			case 6:
				printf("Altezza albero = %d\n", bst_tree_height(bst));
			break;
			case 7:
				printf("Numero di nodi totale = %d\n", bst_root_size(bst));
			break;
			case 8:
				printf("Numero di foglie totali = %d\n", bst_number_of_leafs(bst));
			break;
			case 9:
				printf("Output file: ");
				scanf("%s", file);
				if((fp=fopen(file,"w")) == NULL){
					fprintf(stderr, "Impossibile creare il file %s\n", file);
					return -2;
				}		
				bst_print_in_order(bst, fp);
				fclose(fp);
			break;
			case 10:	
				printf("File da caricare: ");
				scanf("%s", file);
				carica_file(bst, file);
			break;
		}
	}while(scelta != 0);
	
	bst_destroy(bst);

	return 0;
}

void carica_file(BST bst, char *file)
{
	FILE *fp;
	int chiave;
	char str[MAX_STR];
	Item i;

	if((fp = fopen(file,"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", file);
		exit(-1);
	}
	while(fscanf(fp, "%d %s", &chiave, str) != EOF)
	{	
		i = item_new(chiave, str);
		bst_insert_leaf(bst,i);
	}
	fclose(fp);
}
