#include <stdio.h>
#include <stdlib.h>

void add(char *v, char *digits, int n_digits, int position, int max);

int main(int argc, char *argv[])
{
	char *v;
	int max = 3;
	if(argc > 1)
		max = atoi(argv[1]);
	v = (char *) malloc((max+1)*sizeof(char));

	add(v,"5678",4,0,max);

	return 0;
}


void add(char *v, char *digits, int n_digits, int position, int max)
{
	if(position == max)
	{
		v[position] = '\0';
		if(atoi(v) % 7 == 0)
			printf("%s\n",v);
	}
	else
	{
		int i;
		for(i=0; i<n_digits; i++)
		{
			v[position] = digits[i];
			add(v, digits, n_digits, position+1, max);
		}
	}
}
