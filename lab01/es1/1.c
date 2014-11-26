#include <stdio.h>
#include <stdlib.h>
#define NMAX 20

int main(int argc, char *argv[])
{
    float mat[NMAX][NMAX];  //Matrice di input
    float cod[NMAX][NMAX];  //Matrice codificata
    int r,c;                //Dimensione matrice (righe colonne)
    int i,j,k;              //Variabili per cicli
    float s;                //Memorizza somma celle adiacenti
    int n;                  //Numero di celle adiacenti
    FILE *fp;               //Puntatore a file per lettura
    const int dir[8][2] = { //Matrice dei vettori di direzione degli otto elementi adiacenti
                            {-1,-1},{-1,0},{-1,1},
                            { 0,-1},{ 0,1},
                            { 1,-1},{ 1,0},{ 1,1}
                          };
    //Controllo degli argomenti
    if(argc < 2){
        fprintf(stderr, "Utilizzo del programma: 1.exe <file>\n");
        return -1;
    }
    //Apertura del file di input
    if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
        return -2;
    }
    //Lettura file
    fscanf(fp,"%d %d", &r, &c);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fp,"%f", &mat[i][j]);
    //Codifico la matrice
    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {                       //Per ogni elementi della matrice
            s=0;                //Imposto somma a 0
            n=0;                //Imposto n. celle adiacenti a 0
            for(k=0; k<8; k++)  //Per tutte e 8 le celle adiacenti
            {                   //Se non sbordo fuori dalla matrice
                if(i+dir[k][0] >= 0 && i+dir[k][0] < r && j+dir[k][1] >= 0 && j+dir[k][1] < c)
                {
                    n++;                             //Celle adiacenti++
                    s+=mat[i+dir[k][0]][j+dir[k][1]];//Sommo cella adiacente
                }
            }
            cod[i][j]=s/(float)n;//Faccio la media
        }
    }
    //Stampo matrice codificata
    printf("%d %d\n",r,c);
    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            printf("%.1f\t",cod[i][j]);
        }
        printf("\n");
    }

    return 0;
}
