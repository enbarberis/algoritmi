#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_RIGA 100 + 1
#define MAX_POS 10

typedef struct t_parole{
    int occorrenze;             //Numero di occorrenze
    int posizioni[MAX_POS];     //Elenco delle poiszioni
} t_parole;

int main(int argc, char *argv[])
{
    //Struttura dati
    char riga[MAX_RIGA];        //Variabile per leggere una riga dal file di input, variabile per parola temporanea letta
    char parola[MAX_RIGA];      //Variabile per memorizzare una parola
    t_parole parole[MAX_RIGA];  //Di sicuro una parola non sara' mai piu' lunga di 100 caratteri perche' una riga al massimo contiene 100 caratteri
    FILE *fp;                   //Puntatore a file
    int i,l,offset;             //Var. per cicli, per memorizzare strlen, per capire di quanto andare avanti nella sscanf

    //Inizializzazione dati
    for(i=0; i<MAX_RIGA; i++)
        parole[i].occorrenze = 0;

    //Controllo argomenti
    if(argc < 2){
        fprintf(stderr, "Errore nei parametri!\nUso: 1.exe <nomefile>\n");
        return -1;
    }

    //Apro il file
    if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr, "Impossibile aprire il file %s!\n", argv[1]);
        return -2;
    }

    //Per ogni riga del file
    while( fgets(riga, MAX_RIGA, fp) != NULL )
    {
        //Puliso stringa dai caratteri non alfabetici
        l = strlen(riga);
        for(i=0; i<l; i++)
            if(!isalpha(riga[i]))
                riga[i] = ' ';

        //Per ogni parola della riga
        while(sscanf(riga,"%s%n", parola, &offset) > 0)
        {
            printf("%s\n", parola);
            riga += offset;
        }
    }

    fclose(fp);
    return 0;
}
