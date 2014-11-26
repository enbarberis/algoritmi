#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SEQ 4 + 1
#define MAX_RIGA 100 + 1
#define MAX_POS 10
#define MAX_PRE 50

typedef struct t_sequenze{
	char sequenza[MAX_SEQ];		//stringa della sequenza
	int len;					        //lunghezza della sequenza (per evitare calcoli)
	int occorrenze;				    //numero di occorrenze della sequenza
	int posizioni[MAX_POS];		//vettore delle posizioni delle parole che iniziano con seq.
} t_sequenze;

int main(int argc, char *argv[])
{
	//Struttura dati
	t_sequenze sequenze[MAX_PRE];  //tabella delle statistiche		
	char riga[MAX_RIGA];		       //per salvare una riga del file	
	char parola[MAX_RIGA], *p;	   //per salvare una singola parola, puntatore per scorrerla
	int n;					               //numero di sequenze
	int i,j;
	int c = 0;					           //contatore parole
	int offset;					 
	FILE *fp;

	//Controllo argomenti
	if(argc < 3){
		fprintf(stderr, "Errore negli argomenti!\nUso: 2.exe <file_testo> <file_sequenze>\n");
		return -1;
	}

	//Apro file sequenze
	if((fp = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[2]);
		return -2;
	}

	//Leggo file sequenze
	fscanf(fp, "%d", &n);
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%s", sequenze[i].sequenza);
		sequenze[i].occorrenze = 0;
		sequenze[i].len = strlen(sequenze[i].sequenza);
	}	
	fclose(fp);

	//Apro testo
	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
		return -3;
	}

	//Per ogni riga
	while( fgets(riga, MAX_RIGA, fp) != NULL )
	{
		p = riga;
		//Per ogni parola
		while(sscanf(p,"%s%n", parola, &offset) > 0)
		{
			p += offset;       			//Mi sposto di quanti byte ho letto			
			c++;				            //Aumento contatore parole
			//Per tutte le sequenze
			for(i=0; i<n; i++)
			{
				//j++ finche` i caratteri di parola e sequenza[j] combaciano 
				for(j=0; sequenze[i].sequenza[j] == parola[j] && j<sequenze[i].len; j++);
				//Se j == lunghezza sequenza allora parola inizia con i-sequenza 	
				if(j == sequenze[i].len && sequenze[i].occorrenze < MAX_POS)
				{
					sequenze[i].posizioni[sequenze[i].occorrenze++] = c;		
				}	
			}
		}
	}
	fclose(fp);

	//Stampo il risultato
	for(i=0; i<n; i++)
	{
		if(sequenze[i].occorrenze > 0)
		{
			printf("%s - %d occorrenza/e - posizione/i: ", sequenze[i].sequenza, sequenze[i].occorrenze);
			for(j=0; j<sequenze[i].occorrenze; j++)
				printf("%d ", sequenze[i].posizioni[j]);
			printf("\n");
		}
		else
			printf("%s - %d occorrenza/e\n", sequenze[i].sequenza, sequenze[i].occorrenze);
	}

	return 0;
}