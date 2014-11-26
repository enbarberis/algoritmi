#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float x,y,z;                //Cooridnate di input
    float bx = 0,by = 0,bz =0;  //Cooridnate baricentro
    int c=0;                    //Contantore delle coordinate
    FILE *fp;

    if(argc < 2)
    {
        fprintf(stderr,"Utilizzo programma: lab01_1.exe <file>\n");
        return -1;
    }

    if((fp = fopen(argv[1],"r")) == NULL)
    {
        fprintf(stderr,"Impossibile aprire il file %s\n",argv[1]);
        return -2;
    }

    while(fscanf(fp,"%f %f %f", &x, &y, &z) != EOF)
    {
        c++;
        bx+=x;
        by+=y;
        bz+=z;
    }

    bx=bx/(float)c;
    by=by/(float)c;
    bz=bz/(float)c;

    printf("Baricentro: %.1f %.1f %.1f\n", bx, by, bz);

    return 0;
}
