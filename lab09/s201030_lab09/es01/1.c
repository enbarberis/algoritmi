#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_oggetto{
	char nome[21];
	float peso;
	int valore;
	int preso;
} t_oggetto;

void swap(t_oggetto *a, t_oggetto *b);
void zaino(t_oggetto *oggetto, int i, int n, float peso, int *soluzione, int *max_val);
void valigia(t_oggetto *oggetto, int pos, int n, float peso, int n_valigie, float cap_valigia, 
		int *disposizione, int *min_valigie, int *soluzione);

int main(int argc, char **argv)
{
	int n;			//Numero oggetti di input
	float max_bagaglio;	//Peso max del bagaglio
	float max_valigie;	//Peso max delle valigie
	t_oggetto *oggetto;	//Vettore degli oggetti
	int *soluzione;		//Soluzione del problema dello zaino (cosa prendere)
	int *disposizione;	//Vettore per generare tutte le disposizioni
	int max_val = -1;	//valore massimo per il bagaglio
	int min_val = 262144;	//valigie minime necessarie;
	int i;			//var per cicli for
	int presi=0;		//contatore di oggetti presi dopo la prima parte del problema
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
	disposizione = (int *) malloc(n * sizeof(int));
	for(i=0; i<n; i++)
		fscanf(fp,"%s %f %d", oggetto[i].nome, &oggetto[i].peso, &oggetto[i].valore);
	fclose(fp);

	zaino(oggetto, 0, n, max_bagaglio, soluzione, &max_val);

	fp = fopen(argv[4],"w");

	fprintf(fp, "Valore massimo trasportabile nel bagaglio: %d\nOggetti nel bagaglio:\n", max_val); 
	for(i=0; i<n; i++)
		if(oggetto[i].preso = soluzione[i])
		{
			fprintf(fp, "- %s\n", oggetto[i].nome);
			swap(&oggetto[i], &oggetto[presi]);
			presi++;
		}

	valigia(oggetto, presi, n, 0, 0, max_valigie, disposizione, &min_val, soluzione);

	fprintf(fp, "\nNumero di valigie minime: %d\n\nValigia:\n", min_val+1);
	
	float somma = 0;
	for(i=presi; i<n; i++)
	{	
		if(somma + oggetto[soluzione[i]].peso  > max_valigie)
		{
			fprintf(fp, "Peso totale valigia: %.3f\n\nValigia:\n", somma);
			somma = 0;
		}
		somma += oggetto[soluzione[i]].peso;
		fprintf(fp, "- %s\n", oggetto[soluzione[i]].nome);
	}	
	fprintf(fp, "Peso totale valigia: %.3f\n", somma);	
	
	fclose(fp);
	free(oggetto);
	free(soluzione);
	return 0;
}

void swap(t_oggetto *a, t_oggetto *b)
{
	t_oggetto tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
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

void valigia(t_oggetto *oggetto, int pos, int n, float peso, int n_valigie, float cap_valigia, 
		int *disposizione, int *min_valigie, int *soluzione)
{
	int i;

	if(n_valigie > *min_valigie)
		return;
	if(pos >= n)
	{
		*min_valigie = n_valigie;
		for(i=0; i<n; i++)
			soluzione[i] = disposizione[i];
	}
	else
	{
		for(i=0; i<n; i++)
		{
			if(!oggetto[i].preso)
			{
				oggetto[i].preso = 1;	//marcamento
				if(oggetto[i].peso + peso > cap_valigia)
				{
					n_valigie++;
					peso = 0;
				}
				disposizione[pos] = i;
				valigia(oggetto, pos+1, n, peso + oggetto[i].peso, n_valigie, cap_valigia, 
						disposizione, min_valigie, soluzione);
				oggetto[i].preso = 0;	//smarcamento
			}
		}
	}
}
