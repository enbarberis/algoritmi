#include <stdio.h>
#include <stdlib.h>

int catalan(int n)
{
	int i, sum = 0;

	if(n == 0) 
		return 1;
		
	for(i=0; i<n; i++)
		sum += catalan(i)*catalan(n-1-i);
	return sum;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"Parameters error!\nUsage: ./1 <n>\n");
		return -1;
	}
	printf("Catalan(%d) = %d\n",atoi(argv[1]),catalan(atoi(argv[1])));
	return 0;
}
