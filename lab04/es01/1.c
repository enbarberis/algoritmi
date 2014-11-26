#include <stdio.h>
#include <stdlib.h>

typedef struct t_cell{			 //struct of a single cell of the sparse matrix
	int column;			 //column cell
	float value;			 //value of the cell
} t_cell;

typedef struct t_sparse{		 //struct of the sparse matrix
	int size;			 //max number of columns
	int n;				 //number of columns
	t_cell *element;		 //vector of cells
} t_sparse;

float get(t_sparse *m, int i, int j);	 //return the value of the matrix at row i and column j (inp[i][j] == get(m,i,j))
int symmetric(t_sparse *m, int r, int c);//return 1 if matrix m is symmetric
					

int main(int argc, char *argv[])
{
	//data structure
	int r,c;			//rows and columns of input matrix 
	int i,j;			//iterations variables
	float **inp;			//input matrix
	t_sparse *m;			//sparse matrix
	FILE *fp;			//file pointer
	
	//test on arguments
	if(argc < 2){
		fprintf(stderr, "Parameters error!\nUsage: ./1 <input file>\n");
		return -1;
	}
	//test if file is readable
	if( (fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Can't open file %s!\n", argv[1]);
		return -2;
	}
	//file reading and memory allocation for inp
	fscanf(fp, "%d %d", &r, &c);
	inp = (float **) malloc(r * sizeof(float *));
	for(i=0; i<c; i++)
		inp[i] = (float *) malloc(c * sizeof(float));
	for(i=0; i<r; i++)
		for(j=0; j<c; j++)
			fscanf(fp,"%f",&inp[i][j]);
	fclose(fp);
	
	//memory allocation and initialization
	m = (t_sparse *) malloc(r * sizeof(t_sparse));
	for(i=0; i<r; i++){
		m[i].size = 1;
		m[i].n = 0;
		m[i].element = (t_cell *) malloc(1 * sizeof(t_cell));
	}

	//matrix conversion
	for(i=0; i<r; i++)
		for(j=0; j<c; j++)
			if(inp[i][j] != 0)	//for each element not equal to 0...
			{
				//if the element array hasn't enough space
				if(m[i].n >= m[i].size)
				{
					m[i].size *= 2;
					m[i].element = (t_cell *) realloc(m[i].element, m[i].size * sizeof(t_cell));
				}
				m[i].element[m[i].n].column = j;
				m[i].element[m[i].n].value = inp[i][j];
				m[i].n = m[i].n + 1;
			}
	
	printf("Matrix %s symmetric\n", symmetric(m,r,c) ? "is":"is not");
	
	//memory cleaning
	for(i=0; i<r; i++) free(m[i].element);
	free(m);
	return 0;
}

//search if at row i there is an element with column equals to j, if there isn't return 0
float get(t_sparse *m, int i, int j)	
{
	int left = 0, right = m[i].n - 1, center;			//variables for binary search
	while(left <= right)
	{
		center = (left + right)/2;
		if(m[i].element[center].column == j)
			return m[i].element[center].value;
		if(m[i].element[center].column > j)
			right = center - 1;
		else
			left = center + 1;
	}
	return 0;
}

int symmetric(t_sparse *m, int r, int c)
{
	if(r != c) return 0;
	int i,j;
	for(i=1; i<r; i++)
		//for each element above the diagonal ands not equal to 0
		for(j=0; j<m[i].n && m[i].element[j].column<i; j++)
			if(m[i].element[j].value != get(m,m[i].element[j].column,i))
				return 0;
	return 1;
}

/*
int symmetric(t_sparse *m, int r, int c)
{
	if(r != c) return 0;
	int i,j;
	for(i=1; i<r; i++)
		for(j=0; j<i; j++)
			if(get(m,i,j) != get(m,j,i))			//if(inp[i][j] != inp[j][i])
				return 0;
	return 1;
}
*/
