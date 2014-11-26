#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_PAROLE 100
#define  MAX_CHAR 80 + 1
#define  FILE_COD "codificato.txt"
#define  FILE_DIZ "dizionario.txt"
#define  FILE_DEC "decodificato.txt"

int main(int argc, char *argv[])
{
    //Variabili
    char dizionario[MAX_PAROLE][MAX_CHAR];  //Dizionario
    char parola[MAX_CHAR];                  //Per leggere dizionario
    int indice;                             //Per leggere dizionario
    FILE *fp1, *fp2;                        //Puntatori a file
    char c;                                 //Per leggere ogni carattere del file codificato.txt

    //Carico dizionario
    if((fp1 = fopen(FILE_DIZ,"r")) == NULL){
        fprintf(stderr, "Impossibile aprire il file %s\n", FILE_DIZ);
        return -1;
    }
    while(fscanf(fp1,"%d %s", &indice, parola) != EOF)
        strcpy(dizionario[indice],parola);
    fclose(fp1);

    //Leggo file codificato e scrivo il file decodificato
    if((fp1 = fopen(FILE_COD,"r")) == NULL){
        fprintf(stderr, "Impossibile aprire il file %s\n", FILE_COD);
        return -2;
    }
    if((fp2 = fopen(FILE_DEC,"w")) == NULL){
        fprintf(stderr, "Impossibile aprire il file %s\n", FILE_DEC);
        return -3;
    }
    //Per ogni carattere del testo
    while( (c = fgetc(fp1)) != EOF )
    {
        //Se non e' il carattere $ lo stampo
        if(c != '$')
            fputc(c,fp2);
        //Altrimenti leggo indice e stampo parola opportuna
        else
        {
            fscanf(fp1,"%d",&indice);
            fprintf(fp2, "%s", dizionario[indice]);
        }
    }
    //Chiudo i file
    fclose(fp1);
    fclose(fp2);
    return 0;
}
