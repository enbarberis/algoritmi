#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAROLE 100
#define MAX_STR	25+1
#define ESCI "quit"

void inserisci(char **p, int *n);		//Inserisce parola in ordine nella matrice p 
void elimina(char **p, int *n);			//Elimina parola dalla matrice p
void ricerca(char **p, int n);			//Ricerca una stringa
int cerca(char **p, int n, char *str);		//Ritorna la posizione dell'elemento cercato


int main(int argc, char *argv[])
{
	char *parola[MAX_PAROLE];		//Matrice che contiene tutte le parole
	int scelta;				//Scelta del menu`
	int n = 0;				//Numero di parole
	int esci = 0;				//Flag per uscire dal menu
	
	printf(	"======== M E N U ========\n"
	    	"1 - Inserisci una stringa\n"
	    	"2 - Elimina una stringa\n"
	    	"3 - Cerca una stringa\n"
	    	"4 - Esci dal programma\n\n");
	while(!esci)
	{
		printf("> ");
		scanf("%d", &scelta);
		switch(scelta)
		{
			case 1:
				inserisci(parola, &n);
				break;
			case 2:
				elimina(parola, &n);
				break;
			case 3:
				ricerca(parola, n);
				break;
			case 4:
				esci = 1;
				break;
		}
	}
	
	return 0;
}

void inserisci(char **p, int *n)
{
	char inp[MAX_STR];			
	int i,j;
	
	printf("Parola da inserire: ");
	scanf("%s", inp);
	
	for(i=0; i<*n && strcmp(inp,p[i]) > 0; i++);			//Cerco posizione in cui inserire
	
	for(j=*n; j>i; j--)
		p[j] = p[j-1];						//Sposto le parole successive
	p[i] = (char *) malloc((strlen(inp) + 1) * sizeof(char));	//Alloco spazio per le stringhe
	strcpy(p[i],inp);						//Copio la stringa nella posizione esatta
	
	*n = *n + 1;							//Numero parole ++
	
	for(i=0; i<*n; i++)						//Stampo l'elenco delle parole
		printf("[%d] %s\n",i,p[i]);
	printf("\n");
}

void ricerca(char **p, int n)
{
	char inp[MAX_STR];
	
	printf("Parola da ricercare: ");
	scanf("%s", inp);
	if(cerca(p,n,inp) == -1)					//Se non trovo la parola da ricercare...
		printf("Parola non trovata\n\n");
	else
		printf("Parola trovata in poszione %d\n\n", cerca(p,n,inp));		
}

void elimina(char **p, int *n)
{
	char inp[MAX_STR];
	int i;
	
	printf("Parola da eliminare: ");
	scanf("%s", inp);
	
	if(cerca(p,*n,inp) == -1)					//Se non trovo la parola da eliminare...
		printf("Parola inesistente, impossibile cancellarla\n\n");
	else
	{
		for(i=cerca(p,*n,inp); i<*n-1; i++)			//Cancello spostando le successive indietro di 1
			p[i] = p[i+1];	
		*n = *n - 1;						//Diminuisco mumero di parole
		
		printf("Parola cancellata\n");	
		for(i=0; i<*n; i++)					//Stampo l'elenco delle parole
			printf("[%d] %s\n",i,p[i]);
		printf("\n");
	}	
}

int cerca(char **p, int n, char *str)
{
	int sx = 0, dx = n-1, c;
	while(sx <= dx)
	{
		c =  sx + (dx - sx)/2;
		if(strcmp(str,p[c]) == 0)
			return c;
		if(strcmp(p[c],str) > 0)
			dx = c -1;
		else
			sx = c + 1;
	}
	return -1;
}


