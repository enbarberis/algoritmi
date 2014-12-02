#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_oggetto{
	char nome[21];
	float peso;
	int valore;
	int preso;
} t_oggetto;

void zaino(t_oggetto *oggetto, int i, int n, float peso, int *soluzione, int *max_val);

int main(int argc, char **argv)
{
	int n;			//Numero oggetti di input
	float max_bagaglio;	//Peso max del bagaglio
	float max_valigie;	//Peso max delle valigie
	t_oggetto *oggetto;	//Vettore degli oggetti
	int *soluzione;		//Soluzione del problema dello zaino (cosa prendere)
	int max_val = -1;	//valore massimo per il bagaglio
	int i;			//Var. per cicilo for
	FILE *fp;		//Per lettura e scrittura file

	if(argc < 5){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo: %s <peso massimo bagaglio> <peso massimo valigie> "
				"<input file> <output file> \n", argv[0]);
		return -1;
	}

	max_bagaglio = atof(argv[1]);
	max_valigie  = atof(argv[2]);
	
	if((fp=fopen(argv[3],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[3]);
		return -2;
	}

	fscanf(fp,"%d", &n);
	oggetto = (t_oggetto *) malloc(n * sizeof(t_oggetto));
	soluzione = (int *) malloc(n * sizeof(int));

	for(i=0; i<n; i++)
		fscanf(fp,"%s %f %d", oggetto[i].nome, &oggetto[i].peso, &oggetto[i].valore);

	zaino(oggetto, 0, n, max_bagaglio, soluzione, &max_val);

	printf("\nValore massimo trasportabile nel bagaglio: %d\nOggetti nel bagaglio:\n", max_val); 
	for(i=0; i<n; i++)
		if(oggetto[i].preso = soluzione[i])
			printf("- %s\n", oggetto[i].nome);

	free(oggetto);
	free(soluzione);

	return 0;
}

void zaino(t_oggetto *oggetto, int i, int n, float peso, int *soluzione, int *max_val)
{
	if(i >= n)	//se non ci sono piu` oggetti da considerare
	{
		int j, somma = 0;
		
		for(j=0; j<n; j++)
			if(oggetto[j].preso)
				somma += oggetto[j].valore;

		if(somma > *max_val)
		{
			*max_val = somma;
			for(j=0; j<n; j++)
				soluzione[j] = oggetto[j].preso;
		}
	}
	else
	{
		oggetto[i].preso = 0;
		zaino(oggetto, i+1, n, peso, soluzione, max_val);
		if(peso - oggetto[i].peso >= 0)	//se ci sta ancora
		{
			oggetto[i].preso = 1;
			zaino(oggetto, i+1, n, peso - oggetto[i].peso, soluzione, max_val);
		}
	}
}
