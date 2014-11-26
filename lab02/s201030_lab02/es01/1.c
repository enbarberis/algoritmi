#include <string.h>
#include <stdio.h>

#define MAX_RIGA 100 + 2 // \n + \0
#define MAX_POS 10

typedef struct t_parole{
    int occorrenze;             //Numero di occorrenze
    int posizioni[MAX_POS];     //Elenco delle poiszioni
} t_parole;

int main(int argc, char *argv[])
{
    //Struttura dati
    char riga[MAX_RIGA];        //Variabile per leggere una riga dal file di input
    char parola[MAX_RIGA];      //Variabile per memorizzare una parola
    t_parole parole[MAX_RIGA];  //Vettore statistiche. Di sicuro una parola non sara' mai piu' lunga di 100 caratteri perche' una riga al massimo contiene 100 caratteri
    FILE *fp;                   //Puntatore a file
    int i,l,offset;             //Var. per cicli, per memorizzare strlen, per capire di quanto andare avanti nella sscanf
    char *r;                    //Puntatore per scorrere riga
    int c = 0;                  //Contatore dell'ordine delle parole
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
        //Puliso stringa dai caratteri non alfanumerici
        l = strlen(riga);
        for(i=0; i<l; i++)
            if(!isalnum(riga[i]))
                riga[i] = ' ';

        r = riga;                   //Punto alla riga attuale (mi serve per spostarmi con la sscanf)

        //Per ogni parola della riga
        while(sscanf(r,"%s%n", parola, &offset) > 0)
        {
            r+=offset;		   	      //scorro stringa dei byte letti
            c++;                    //Aumento contatore parole
            //Se ci sta aggiungo la posizione della parola corrente
            if(parole[strlen(parola)].occorrenze < MAX_POS )
                parole[strlen(parola)].posizioni[parole[strlen(parola)].occorrenze++] = c;
        }
    }
    fclose(fp);

    //Stampo il risultato
    for(i=0; i<MAX_RIGA; i++)
    {
        if(parole[i].occorrenze > 0)
        {
            printf("%d - %d - ", i, parole[i].occorrenze);
            for(l=0; l<parole[i].occorrenze; l++)
                printf("%d ", parole[i].posizioni[l]);
            printf("\n");
        }
    }

    return 0;
}
