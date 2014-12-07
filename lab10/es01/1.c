#define RICORSIVA 0
#define GREEDY	  1
#define SOLUZIONE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct t_compito{
	char *nome;
	int  difficolta;
	int  risorsa;
} t_compito;

void ric_partition(int pos, t_compito *compito, int n, int k, int *scarto_min, int *soluzione);
void gre_partition(t_compito *compito, int n, int k, int *scarto_min, int *soluzione);

int main(int argc, char **argv)
{
	int k = 0;			//numero risorse
	int n = 0;			//numero compiti
	t_compito *compito;		//vettore dei compiti
	char **risorsa;			//vettore delle risorse
	FILE *fp;			//puntatore a file
	char str[21];			//per leggere stringhe da file
	int ch;				//per leggere righe del file
	int i,j;			//var. per ciclo for
	int scarto_min = INT_MAX;	//lo scarto minimo tra la risorsa piu` usata e quella meno usata
	int *soluzione;			//soluzione[i] = risorsa del compito i a cui conviene assegnare tale compito

	if(argc < 3){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo: %s <file_compiti> <file_risorse>\n", argv[0]);
		return -1;
	}

	//=====Lettura file compiti=====
	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Impossibile leggere il file %s\n", argv[1]);
		return -2;
	}
	while((ch = fgetc(fp)) != EOF)		//conto righe del file
		if(ch == '\n')
			n++;
	
	compito = (t_compito *) malloc(n * sizeof(t_compito));
	soluzione = (int *) malloc(n * sizeof(int));
	rewind(fp);
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%s %d", str, &ch);
		compito[i].nome = (char *) malloc((strlen(str)+1)*sizeof(char));
		strcpy(compito[i].nome, str);
		compito[i].difficolta = ch;
	}
	fclose(fp);

	//=====Lettura file risorse=====
	if((fp = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "Impossibile leggere il file %s\n", argv[2]);
		return -3;
	}
	while((ch = fgetc(fp)) != EOF)		//conto righe del file
		if(ch == '\n')
			k++;
	
	risorsa = (char **) malloc(k*sizeof(char *));
	rewind(fp);
	for(i=0; i<k; i++)
	{
		fscanf(fp, "%s", str);
		risorsa[i] = (char *) malloc((strlen(str)+1)*sizeof(char));
		strcpy(risorsa[i], str);
	}
	fclose(fp);

	#if SOLUZIONE==RICORSIVA
	ric_partition(0, compito, n, k, &scarto_min, soluzione);
	#endif
	#if SOLUZIONE==GREEDY
	gre_partition(compito, n, k, &scarto_min, soluzione);
	#endif

	//stampa del risultato
	printf("Scarto: %d\n", scarto_min);
	for(i=0; i<k; i++)
	{
		printf("%s\n", risorsa[i]);
		for(j=0; j<n; j++)
			if(soluzione[j] == i)
				printf("\t%s\n", compito[j].nome);
	}

	//liberazione memoria
	for(i=0; i<n; i++)
		free(compito[i].nome);
	free(compito);
	for(i=0; i<k; i++)
		free(risorsa[i]);
	free(risorsa);
	free(soluzione);

	return 0;	
}

void ric_partition(int pos, t_compito *compito, int n, int k, int *scarto_min, int *soluzione)
{
	if(pos >= n)
	{
		int ris_meno_usata = INT_MAX, ris_piu_usata = -1;
		int i, j, somma;
		
		for(i=0; i<k; i++)		//per tutte le risorse
		{
			somma = 0;
			for(j=0; j<n; j++)	//per tutti i compiti
			{
				if(compito[j].risorsa == i)
					somma += compito[j].difficolta;
			}
			if(somma > ris_piu_usata)
				ris_piu_usata = somma;
			if(somma < ris_meno_usata)
				ris_meno_usata = somma;
		}
		if(abs(ris_piu_usata - ris_meno_usata) < *scarto_min)	//se trovo una soluzione migliore la salvo
		{
			*scarto_min = abs(ris_piu_usata - ris_meno_usata);
			for(i=0; i<n; i++)
				soluzione[i] = compito[i].risorsa;
		}
	}
	else
	{
		int i;
		for(i = 0; i<k; i++)
		{
			compito[pos].risorsa = i;
			ric_partition(pos+1, compito, n, k, scarto_min, soluzione);
		}
	}
}

void gre_partition(t_compito *compito, int n, int k, int *scarto_min, int *soluzione)
{
	int parte = 0;
	int diff_ris[k];
	int i,j;
	int min, min_index, max;

	for(i=0; i<k; i++)
		diff_ris[i] = 0;

	for(i=0; i<n; i++)
		parte += compito[i].difficolta;
	parte = parte / k;

	j=0;
	for(i=0; i<n; i++)
	{
		if(diff_ris[j] + compito[i].difficolta > parte)
		{	
			j++;
			if(j >= k)
				break;
		}

		diff_ris[j] += compito[i].difficolta;
		soluzione[i] = j;
	}
	
	for(; i<n; i++)	//per gli elementi rimanenti
	{
		min = INT_MAX;
		for(j=0; j<k; j++)	//cerco risorsa meno sfruttata
		{
			if(diff_ris[j] < min)
			{
				min = diff_ris[j];
				min_index = j;
			}
		}
		diff_ris[min_index] += compito[i].difficolta;
		soluzione[i] = min_index;
	}

	//calcolo scarto tra risorsa piu usata e meno usata
	min = INT_MAX;
	max = -1;
	for(j=0; j<k; j++)
	{
		if(diff_ris[j] > max)
			max = diff_ris[j];
		if(diff_ris[j] < min)
			min = diff_ris[j];
	}
	*scarto_min = max - min;
}
