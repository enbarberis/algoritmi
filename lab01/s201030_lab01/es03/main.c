#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 20 + 1

//Ritorna quante volte si ripetono i primi l caratteri di s
//(si suppone pero` che l stia esattamente nella lunghezza di s)
int ripetizioni(char *s, int l);

int main(int argc, char *argv[])
{
    char s[NMAX];   //Stringa di input
    int i, s_len;   //Var. per cicli e per memorizzare la lunghezza di s
    int p = 0;      //Periodo minimo

    printf("Stringa? ");
    scanf("%s", s);
    while(strcmp(s,"stop") != 0)
    {
        p = 0;                          //Suppongo perido = 0
        s_len = strlen(s);              //Mi calcolo una volta sola la strlen(s) per velocizzare for
        for(i=1; i<s_len && p==0; i++)  //Per tutti i divisori e finche` non trovo un periodo
        {
            if(s_len % i == 0)          //Se i e` un divisore
            {
                if(ripetizioni(s,i) > 0)//e se i primi 'i' caratteri si ripetono per tutta la stringa s
                    p = i;              //Allora il periodo minimo e' i (quindi esce dal ciclo for)
            }
        }
        if(p > 0)
            printf("La stringa %s e` periodica (periodo %d).\n", s, p);
        else
            printf("La stringa %s non e` periodica.\n", s);

        printf("Stringa? ");
        scanf("%s", s);
    }
    printf("Programma terminato.\n");
    return 0;
}

int ripetizioni(char *s, int l)
{
    int i;                      //Var. per ciclo for
    int s_len = strlen(s);      //Calcolo strlen solo una volta
    for(i=l; i<s_len; i++)      //Per tutti i caratteri successivi all' l-esimo
    {
        if(s[i] != s[i%l])      //Se il carattere attuale non coincide con il carattere (i%l)-esimo (il carattere (i%l)-esimo coincide proprio con la posizione del carattere della parola da controllare se si ripete)
            return 0;           //Allora la stringa non si ripete
    }
    return s_len/l;             //Se arrivo qui vuol dire che i primi l caratterei si ripetono per tutto il vettore, e dato che l e` un divisore di strlen(s) allora se ritorno strlen(s)/l ritorno il numero di ripetizioni
}
