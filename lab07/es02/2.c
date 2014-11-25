#include <stdio.h>
#include <stdlib.h>

const char vowels[] = "aeiou";
const char consonants[] = "bcdfghlmnpqrstvz"; 
const int n_vowels = 5;
const int n_consonants = 16;

void add(char *v, int pos, int max, FILE *fp);

int main(int argc, char *argv[])
{
	FILE *fp;
	int n;
	char *v;

	if(argc < 3){
		fprintf(stderr, "Parameters error!\nUsage: ./2 <n> <output_file>\n");
		return -1;
	}
	
	if((fp = fopen(argv[2],"w")) == NULL){
		fprintf(stderr, "Can't open file %s\n",argv[2]);
		return -2;
	}

	n = atoi(argv[1]);

	v = (char *) malloc((n+1)*sizeof(char));
	add(v, 0, n, fp);

	free(v);
	fclose(fp);

	return 0;
}


void add(char *v, int pos, int max, FILE *fp)
{
	if(pos == max)
	{
		v[pos] = '\0';
		fprintf(fp,"%s\n",v);
		return;
	}
	
	int i;

	if(pos%2 == 0)
	{
		for(i=0; i<n_consonants; i++)
		{
			v[pos] = consonants[i];
			add(v, pos+1, max, fp);
		}
	}
	else
	{
		for(i=0; i<n_vowels; i++)
		{
			v[pos] = vowels[i];
			add(v, pos+1, max, fp);
		}
	}
}
