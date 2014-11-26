#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#define OUTPUT_FILE "output.txt"
#define INIT_SIZE 10

typedef struct t_punto{
	int x;
	int y;
} t_punto;

float dist(t_punto p1, t_punto p2);	//Distanza tra due punti
void  sort(t_punto *v, int n);		//Ordina il vettore dei punti lungo n
void  swap(t_punto *p1, t_punto *p2);	//Scambia le due variabili

int main(int argc, char *argv[])
{
	int d;				//Lunghezza massima dei segmenti (dato di input tramite argomenti)
	int n_d = 0;			//Numero di punti che sono distanti tra di loro meno di d
	int x,y;			//Variabili per leggere le coordinate
	int n = 0;			//Numero di coordinate
	int i,j;			//Variabili per cicli
	unsigned int size = INIT_SIZE;	//Byte allocati per il vattore punto[]
	t_punto *punto;			//Vettore contenete tutte le coordinate
	FILE *fp;			//Puntatore a file
	float d_min;			//Distanza minima tra due punti
	t_punto p1_min, p2_min;		//La coppia di punti piu` vicini
	float d_max;			//Distanza massima tra due punti
	t_punto p1_max, p2_max;		//La coppia di punti piu` lontani
	
	//Controllo argomenti
	if(argc < 3){
		fprintf(stderr, "Errore nei parametri!\nUtilizzo: 1.exe <d> <file input>\n");
		return -1;
	}
	
	d = atoi(argv[1]);		//Mi ricavo l'input d
	
	//Apro file
	if((fp = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "Impossibile aprire il file %s\n", argv[2]);
		return -2;
	}
	
	punto = (t_punto *) malloc(size * sizeof(t_punto));
	
	//Leggo input
	while(fscanf(fp,"%d %d", &x, &y) == 2)
	{
		punto[n].x = x;
		punto[n].y = y;
		n++;
		if(n >= size - 1){
			size *= 2;	//Raddoppio lo spazio allocato
			punto = (t_punto *) realloc(punto, size * sizeof(t_punto));
		}	
	}
	fclose(fp);
	
	//Inizializzo max e min
	d_max = d_min = dist(punto[0], punto[1]);
	p1_min = punto[0]; p2_min = punto[1];
	p1_max = punto[0]; p2_max = punto[1];				 
	
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)	//Non parto da j=0 ma da j=i+1 per evitare di controllare due volte le stesse coppie
		{
			if(j != i)
			{
				//Per tutte le combinazioni di punti
				//Se trovo una coppia piu` vicina...
				if(dist(punto[i], punto[j]) < d_min){
					d_min = dist(punto[i], punto[j]);
					p1_min = punto[i];
					p2_min = punto[j];
				}
				//Se trovo una coppia piu` lontana...
				if(dist(punto[i], punto[j]) > d_max){
					d_max = dist(punto[i], punto[j]);
					p1_max = punto[i];
					p2_max = punto[j];
				}
				//Se trovo una coppia distante meno di d
				if(dist(punto[i], punto[j]) < d)
					n_d++;
			}
		}
	}
	
	//Stampo risultato
	printf("Coppia di punti piu` vicini:  (%d, %d) e (%d, %d)\n", p1_min.x, p1_min.y, p2_min.x, p2_min.y);
	printf("Coppia di punti piu` lontani: (%d, %d) e (%d, %d)\n", p1_max.x, p1_max.y, p2_max.x, p2_max.y);
	printf("Numero di punti distanti meno di %d: %d\n", d, n_d);
	
	sort(punto, n);		//Ordino i punti
	
	//Li stampo
	if((fp = fopen(OUTPUT_FILE,"w")) == NULL){
		fprintf(stderr, "Impossibile creare il file %s\n", OUTPUT_FILE);
		return -3;
	}
	
	for(i=0; i<n; i++)
		fprintf(fp, "%d %d\n", punto[i].x, punto[i].y);
	fclose(fp);
	
	return 0;
}

float dist(t_punto p1, t_punto p2)
{
	return sqrt( pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) );	
}

void  sort(t_punto *v, int n)
{
	int i,j;
	float min;
	int indice;
	t_punto origine; origine.x = 0; origine.y = 0;
	for(i=1; i<n-1; i++)
	{
		//Cerco il minimo
		min = dist(v[i], origine);
		indice = i;
		
		for(j=i+1; j<n; j++)
			if(dist(v[j],origine) < min)
			{
				indice = j;
				min = dist(v[j],origine);
			}
		swap(&v[i], &v[indice]);
	}
}

void  swap(t_punto *p1, t_punto *p2)
{
	t_punto tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}


	
