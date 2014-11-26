#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESTO 0
#define NUM1  1
#define NUM2  2
#define SOMMA 3

void stampa(char **m, int n);	//per stampare la matrice della somma in colonna
int sposta(int *r, int *c);	//mi sposto alla prossima della da riempire
int ultimo(char **m, int c);	//mi dice se devo decidere solo piu` un numero in quella colonna
int aggiungi(char **m, int r, int c, int n, int *preso);

int main(int argc, char **argv)
{
	int n;			//cifre mancanti
	int i;			//variabile ausiliaria
	char **m;		//matrice di caratteri che contiene la somma in colonna
	int preso[10] = {1,0,0,0,0,0,0,0,0,0};

	if(argc < 4)
	{
		fprintf(stderr, "Parameteres error!\nUsage: ./3 <n> <num1> <num2> </sum>\n");
		return -1;
	}

	n = atoi(argv[1]);
	m = (char **) malloc(4*sizeof(char *));	//4 righe per contenere resto, num1, num2 e somma
	for(i=0; i<4; i++)
		m[i] = malloc(n*sizeof(char));
	for(i=0; i<n; i++)
		m[0][i] = '0';
	strcpy(m[NUM1],argv[2]);
	strcpy(m[NUM2],argv[3]);
	strcpy(m[SOMMA],argv[4]);

	printf("========P R O B L E M A========\n");
	stampa(m,n);

	if(aggiungi(m,NUM1,n-1,n,preso) == 1)
	{
		printf("=======S O L U Z I O N E=======\n");
		stampa(m,n);
	}
	else
		printf("Il problema non ha soluzione\n");
	return 0;
}

void stampa(char **m, int n)
{
	int i,j;
	for(i = 0; i<4; i++)
	{
		if(i==0)printf("RESTO\t");
		if(i==1)printf("NUM1 \t");
		if(i==2)printf("NUM2 \t");
		if(i==3)printf("SOMMA\t");
		for(j=0; j<n; j++)
		{
			printf(" %c",m[i][j]);
		}
		printf("\n\n");
	}
}

int sposta(int *r, int *c)
{
	*r = *r + 1;
	if(*r > 3)
	{
		*r = 1;
		*c = *c - 1;
	}
}

int ultimo(char **m, int c)
{
	int s = 0;
	if(m[NUM1][c]  != '_') s++;
	if(m[NUM2][c]  != '_') s++;
	if(m[SOMMA][c] != '_') s++;
	if(s == 2)
		return 1;
	return 0;
}

int verifica_somma(char **m, int n)
{
	int i,j,sum;
	char **tmp;
	tmp = (char **) malloc(4*sizeof(char *));	//4 righe per contenere resto, num1, num2 e somma
	for(i=0; i<4; i++)
		tmp[i] = malloc(n*sizeof(char));
	for(i=0; i<n; i++)
		tmp[RESTO][i] = '0';
	for(i=1; i<4; i++)
		for(j=0; j<n; j++)
			tmp[i][j] = m[i][j];

	for(i=n-1; i>=0; i--)
	{
		sum = tmp[RESTO][i] + tmp[NUM1][i] + tmp[NUM2][i] - 3*'0';
		if(sum%10 != tmp[SOMMA][i] - '0')
			return 0;

		if(sum > 9)
		{
			if(i == 0)
				return 0;
			tmp[RESTO][i-1] = '1';
		}
	}

	for(i=0; i<4; i++)
		free(tmp[i]);
	free(tmp);

	return 1;
}

int aggiungi(char **m, int r, int c, int n, int *preso)
{
	while(c>=0 && m[r][c] != '_')	//mi sposto alla prima cella da riempire
		sposta(&r, &c);
	if(c < 0)			//Se ho messo tutte le cifre ho trovato una soluzione!!!
	{	
		if(verifica_somma(m, n))
			return 1;
		return 0;
	}
	if(ultimo(m, c))		//se e` l'ultimo elemento della colonna da definire
	{
		int i,x;
		for(i=0; i<2; i++)	//per i due numeri "forzati" possibili (1 + 2 = 3) oppure (4 + 8  = (1)2)
		{
			if(r == NUM1  && i==0) x = m[SOMMA][c] - m[RESTO][c] - m[NUM2][c] + '0';
			if(r == NUM1  && i==1) x = 10 + m[SOMMA][c] - m[RESTO][c] - m[NUM2][c] + '0';
			if(r == NUM2  && i==0) x = m[SOMMA][c] - m[RESTO][c] - m[NUM1][c] + '0';
			if(r == NUM2  && i==1) x = 10 + m[SOMMA][c] - m[RESTO][c] - m[NUM1][c] + '0';
			if(r == SOMMA && i==0) x = m[RESTO][c] + m[NUM1][c] + m[NUM2][c] - 3*'0';
			if(r == SOMMA && i==1) x = (m[RESTO][c] + m[NUM1][c] + m[NUM2][c] - 3*'0')%10;

			if(x>0 && x<10 && !preso[x])	//se la soluzione e` valida e la cifra corrispondente non e` presa
			{

				if(i==1 && c==0)	//controllo di non eccedere a colonna = -1
					return 0;
				preso[x] = 1;
				m[r][c] = '0' + x;	//la 'prendo' e aggiorno la matrice
				if(i==1 && c>0)
					m[RESTO][c-1] = '1';	//se e` il caso metto il resto
				if(aggiungi(m,r,c,n,preso) == 1)
					return 1;
				else			//se il numero non va bene torno alle origini
				{	
					preso[x] = 0;
					m[r][c] = '_';
					if(i==1)
						m[RESTO][c-1] = '0';
				}
			}
		}
		return 0;
	}
	else	//se non e' l'ultimo numero da inserire
	{
		int i;
		for(i = 1; i<10; i++)	//per tutte le cifre che posso usare non prese
		{
			if(!preso[i])
			{
				preso[i] = 1;		//se non preso provo ad aggiungerlo e vedo se va bene
				m[r][c] = '0' + i;
				if(aggiungi(m,r,c,n,preso) == 1)
					return 1;
				else			//se non va bene torno alle origini
				{
					preso[i] = 0;
					m[r][c] = '_';
				}
			}
		}
		return 0;
	}
}
