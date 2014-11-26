#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTR 50 + 1

void mergesort(void *v, int l, int r, size_t size, int (*compare)(void *a, void *b));
void merge(void *v, int l, int q, int r, size_t size, int (*compare)(void *a, void *b));
int compare_int(void *a, void *b);
int compare_str(void *a, void *b);

int main(int argc, char *argv[])
{
	FILE *fp;
	int i;
	int n;
	int *v;
	char **s;
	char riga[MAXSTR];
	
	if(argc < 3){
		fprintf(stderr, "Parameters error.\nUsage: ./3 -<s/i> <file>\n-s : sort strings\n-i : sort integers\n");
		return -1;
	}

	if((fp = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}
	fscanf(fp,"%d", &n);

	if(argv[1][1] == 's'){
		s = (char **) malloc(n*sizeof(char *));
		for(i=0; i<n; i++){
			fscanf(fp,"%s",riga);
			s[i] = (char *) malloc(strlen(riga)*sizeof(char));
			strcpy(s[i],riga);
		}
		
		mergesort(s,0,n-1,sizeof(char *),compare_str);
		
		printf("Sorted:\n\n");
		for(i=0; i<n; i++)
			printf("%s\n", s[i]);
		
		for(i=0; i<n; i++)
			free(s[i]);
		free(s);
	}
	else if(argv[1][1] == 'i')
	{
		v = (int *) malloc(n*sizeof(int));
		for(i=0; i<n; i++)
			fscanf(fp,"%d",&v[i]);
		
		mergesort(v,0,n-1,sizeof(int),compare_int);
		
		printf("Sorted:\n\n");
		for(i=0; i<n; i++)
			printf("%d\n",v[i]);
		
		free(v);
	}
	fclose(fp);

	return 0;
}

void merge(void *v, int l, int q, int r, size_t size, int (*compare)(void *a, void *b))
{
	int i, j, k;
	void *b;

	b = (void *) malloc((r - l + 1) * size);
	i = l;
	j = q+1;
	for(k=0; k<=r-l; k++)
	{
		if(i > q){		//if left elements are finished
			memcpy(b+k*size, v+j*size, size);
			j++;
		}
		else if(j > r){		//if right elements are finished
			memcpy(b+k*size, v+i*size, size);
			i++;
		}
		else if(compare(v+i*size, v+j*size) < 0 || compare(v+i*size, v+j*size) == 0){
			memcpy(b+k*size, v+i*size, size);
			i++;
		}
		else{	
			memcpy(b+k*size, v+j*size, size);
			j++;
		}
	}
	for(k=l; k<=r; k++)
		memcpy(v+k*size,b+(k-l)*size, size);
	free(b);
}

void mergesort(void *v, int l, int r, size_t size, int (*compare)(void *a, void *b))
{
	int q = (l + r)/2;
	if(r <= l)
		return;
	mergesort(v, l, q, size, compare);
	mergesort(v, q+1, r, size, compare);
	merge(v, l, q, r, size, compare);
}

int compare_int(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}

int compare_str(void *a, void *b)
{
	return strcmp(*((char **)a), *((char **)b));
}
