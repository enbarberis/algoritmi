#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	if(argc < 4)
	{
		fprintf(stderr, "Errore nei parametri!\nUtilizzo: %s <n_compiti> <n_risorse> <intervallo>\n", argv[0]);
		return -1;
	}
	
	int n_compiti = atoi(argv[1]);
	int n_risorse = atoi(argv[2]);
	int intervallo = atoi(argv[3]);
	FILE *fp;
	int i;

	srand(time(NULL));

	fp = fopen("compiti_rand.txt","w");
	for(i=0; i<n_compiti; i++)
	{
		fprintf(fp,"Job%d\t\t%d\n", i, rand()%intervallo);
	}
	fclose(fp);

	fp = fopen("risorse_rand.txt","w");
	for(i=0; i<n_risorse; i++)
		fprintf(fp,"Risorsa%d\n",i);
	fclose(fp);
	
	return 0;
}
