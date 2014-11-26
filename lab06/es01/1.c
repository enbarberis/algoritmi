#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "item.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"


int main(int argc, char *argv[])
{
	List l;
	Stack s;
	Queue q;
	Priority_queue pq;
	Item item, key;
	int scelta, chiave;
	char str[36];

	if(argc < 2){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo:"
				" ./1 -<modalita`>\n\n"
				"Modalita` disponibili:\n"
				"-l : lista non ordinata\n"
				"-s : pila\n"
				"-q : coda\n"
				"-p : coda con priorita`\n");
		return -1;
	}

	switch(argv[1][1])
	{
		//===============================================LIST===============================================//
		case 'l':
			l = list_init();

			scelta = 0;
			printf( "=== L I S T A ===\n\n"
				"1 - Cardinalita` della lista\n"
				"2 - Inserimento in testa\n"
				"3 - Inserimento al fondo\n"
				"4 - Ricerca di elementi\n"
				"5 - Estrazione di elementi\n"
				"6 - Visualizzazione lista\n"
				"7 - Distruzione lista\n"
				"8 - Esci\n\n");
			while(scelta != 8)
			{
				printf("\nScelta: ");
				scanf("%d", &scelta);
				switch(scelta)
				{
					case 1:
						printf("Cardinalita` lista = %d\n", list_size(l));
					break;
					case 2:
						item = item_scan();
						list_push_head(l,item);
					break;
					case 3:
						item = item_scan();
						list_push_tail(l,item);
					break;
					case 4:
						printf("Per quale chiave di ricerca?\n(1 nome; 2 cognome; 3 matricola)\n");
						scanf("%d", &chiave);
						printf("Introduci la chiave di ricerca: ");
						scanf("%35s",str);
						key = item_new(str,str,str,0,0);
						if(chiave == 1)
							list_print_search(l,key,compare_name);
						if(chiave == 2) 
							list_print_search(l,key,compare_surname);
						if(chiave == 3)
							list_print_search(l,key,compare_id);
						item_free(key);
					break;
					case 5:						
						printf("Per quale chiave di ricerca?\n(1 nome; 2 cognome; 3 matricola)\n");
						scanf("%d", &chiave);
						printf("Introduci la chiave di ricerca degli elementi da eliminare: ");
						scanf("%35s",str);
						key = item_new(str,str,str,0,0);
						if(chiave == 1)
							while(list_extract(l,key,compare_name) == 1);
						if(chiave == 2)
							while(list_extract(l,key,compare_surname) == 1);
						if(chiave == 3)
							while(list_extract(l,key,compare_id) == 1);
						printf("Elementi lista dopo eliminazione:\n");
						list_print(l);
					break;
					case 6:
						list_print(l);
					break;
					case 7:
						list_destroy(l);
					break;
				}
			}
			list_destroy(l);
		break;
		
		//===============================================PILA===============================================//
		case 's':
			s = stack_init();

			scelta = 0;
			printf( "=== P I L A ===\n\n"
				"1 - Cardinalita` della pila\n"
				"2 - Inserimento in testa\n"
				"3 - Estrazione dalla testa\n"
				"4 - Visualizzazione pila\n"
				"5 - Distruzione lista\n"
				"6 - Esci\n\n");
			while(scelta != 6)
			{
				printf("\nScelta: ");
				scanf("%d", &scelta);
				switch(scelta)
				{
					case 1:
						printf("\nCardinalita` della pila = %d\n",stack_size(s));	
					break;
					case 2:
						item = item_scan();
						stack_push(s,item);
					break;
					case 3:
						if(!stack_empty(s))
						{
							printf("\nElemento estratto:\n");
							item_print(stack_pop(s));
						}
					break;
					case 4:
						stack_print(s);
					break;
					case 5:	
						stack_destroy(s);
					break;
				}
			}
			stack_destroy(s);
		break;
		
		//===============================================CODA===============================================//
		case 'q':
			q = queue_init();

			scelta = 0;
			printf( "=== C O D A ===\n\n"
				"1 - Cardinalita` della coda\n"
				"2 - Inserimento in fondo\n"
				"3 - Estrazione dalla testa\n"
				"4 - Visualizzazione coda\n"
				"5 - Distruzione coda\n"
				"6 - Esci\n\n");
			while(scelta != 6)
			{
				printf("\nScelta: ");
				scanf("%d", &scelta);
				switch(scelta)
				{
					case 1:
						printf("\nCardinalita` della coda = %d\n",queue_size(q));	
					break;
					case 2:
						item = item_scan();
						queue_push(q,item);
					break;
					case 3:
						if(!queue_empty(q))
						{
							printf("\nElemento estratto:\n");
							item_print(queue_pop(q));
						}
					break;
					case 4:
						queue_print(q);
					break;
					case 5:	
						queue_destroy(q);
					break;
				}
			}
			queue_destroy(q);
		break;
		
		//======================================CODA CON PRIORITA======================================//
		case 'p':
			pq = priority_queue_init();

			scelta = 0;
			printf( "=== C O D A   C O N   P R I O R I T A`===\n\n"
				"1 - Cardinalita` della coda\n"
				"2 - Inserimento nella coda\n"
				"3 - Estrazione dalla testa\n"
				"4 - Visualizzazione coda\n"
				"5 - Distruzione coda\n"
				"6 - Esci\n\n");
			while(scelta != 6)
			{
				printf("\nScelta: ");
				scanf("%d", &scelta);
				switch(scelta)
				{
					case 1:
						printf("\nCardinalita` della coda = %d\n",priority_queue_size(pq));	
					break;
					case 2:
						item = item_scan();
						priority_queue_push(pq,item,compare_average);
					break;
					case 3:
						if(!priority_queue_empty(pq))
						{
							printf("\nElemento estratto:\n");
							item_print(priority_queue_pop(pq));
						}
					break;
					case 4:
						priority_queue_print(pq);
					break;
					case 5:	
						priority_queue_destroy(pq);
					break;
				}
			}
			priority_queue_destroy(pq);
		break;
	}

	return 0;
}
