#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_oggetto{
	char nome[21];
	float peso;
	int valore;
	int preso;
} t_oggetto;

int max_valore(t_oggetto *oggetto, int i, float max_peso);

int main(int argc, char **argv)
{
	int n;			//Numero oggetti di input
	float max_bagaglio;	//Peso max del bagaglio
	float max_valigie;	//Peso max delle valigie
	t_oggetto *oggetto;	//Vettore degli oggetti
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
	for(i=0; i<n; i++)
	{
		fscanf(fp,"%s %f %d", oggetto[i].nome, &oggetto[i].peso, &oggetto[i].valore);
		oggetto[i].preso = 0;
	}
	
	printf("\nValore massimo trasportabile nel bagaglio: %d\nOggetti nel bagaglio:\n", max_valore(oggetto, n-1, max_bagaglio));
	for(i=0; i<n; i++)
		if(oggetto[i].preso)
			printf("- %s\n", oggetto[i].nome);
	
	free(oggetto);
	return 0;
}

int max_valore(t_oggetto *oggetto, int i, float max_peso)
{
	if(i < 0)
		return 0;
	if(max_peso == 0)
		return 0;
	if(oggetto[i].peso > max_peso)
		return max_valore(oggetto, i-1, max_peso);
	
	int ris1 = max_valore(oggetto, i-1, max_peso);
	int ris2 = max_valore(oggetto, i-1, max_peso - oggetto[i].peso) + oggetto[i].valore;
	
	if(ris1 > ris2)
	{
		oggetto[i].preso = 0;
		return ris1;
	}
	else
	{
		oggetto[i].preso = 1;
		return ris2;
	}
}
