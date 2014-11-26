#define NMAX 10
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void leggi(char *file, float **m, int *n);
void codifica(float **m, int n);
void stampa(float **m, int n);
int simmetrica(float **m, int n);

int main(int argc, char *argv[])
{
    int n;              //Dimensioni matrice
    float **m;          //Matrice letta
    float **c;          //Matrice codificata

    if(argc < 2)
    {
        fprintf(stderr, "Utilizzo del programma: 3.exe <file>\n");
        return -1;
    }

    leggi(argv[1], m, &n);
    stampa(m,n);

    return 0;
}

void stampa(float **m, int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%.2f\t",m[i][j]);
        printf("\n");
    }
}

void leggi(char *file, float **m, int *n)
{
    FILE *fp;
    int i, j;

    if((fp = fopen(file,"r")) == NULL)
    {
        fprintf(stderr, "Impossibile aprire il file %s\n", file);
        exit(-2);
    }

    fscanf(fp, "%d", n);

    //Alloco matrice
    m = (float **)malloc((*n)*sizeof(float *));
    for(i=0; i<*n; i++) m[i] = (float *)malloc((*n)*sizeof(float));

    //Leggo matrice
    for(i=0; i<*n; i++)
        for(j=0; j<*n; j++)
            fscanf(fp,"%f",&m[i][j]);

    fclose(fp);
}

/*
int main(int argc, char *argv[])
{
    FILE *fp;
    int n;              //Dimensioni matrice
    int i,j;            //Variabili ausiliarie
    float m[NMAX][NMAX];//Matrice di lettura
    float c[NMAX][NMAX];//Matrice codificata

    if(argc < 2)
    {
        fprintf(stderr, "Utilizzo del programma: 3.exe <file>\n");
        return -1;
    }

    if((fp = fopen(argv[1],"r")) == NULL)
    {
        fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
        return -2;
    }

    fscanf(fp,"%d",&n);     //Leggo dimensioni matrice
    for(i=0; i<n; i++)      //Leggo matrice
        for(j=0; j<n; j++)
            fscanf(fp,"%f", &m[i][j]);


    //Codifica
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(m[i][j] <= 0)
            {
                c[i][j] = 0;
            }
            else
            {
                c[i][j] = ceil(log10(m[i][j]));
            }
        }
    }


    return 0;
}
*/
