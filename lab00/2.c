#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int n;          //Numero di parole da leggere
    int i;          //Variabile per for
    char parola[21];//Parola P
    char riga[21];  //Parola generica della i-esima riga

    if(argc < 2)
    {
        fprintf(stderr, "Utilizzo programma: 2.exe <file>\n");
        return -1;
    }
    if((fp=fopen(argv[1],"r"))==NULL)
    {
        fprintf(stderr, "Impossibile aprire il file %s\n", argv[1]);
        return -2;
    }

    fscanf(fp,"%d %s", &n, parola);
    for(i=0; i<n; i++)
    {
        fscanf(fp,"%s",riga);
        if(strcmp(riga,parola) > 0 )    //Se riga > parola
            printf("%s\n",riga);
    }


    return 0;
}
