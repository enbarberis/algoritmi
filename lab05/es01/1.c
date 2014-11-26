#include <stdio.h>
#include <stdlib.h>

void convert(int n, int base);

int main(int argc, char *argv[])
{
	int n, base;

	printf("Convert ");
	scanf("%d",&n);
	printf("to base ");
	scanf("%d",&base);
	
	convert(n,base);
	printf("\n");
	
	return 0;
}

void convert(int n, int base)
{
	if(n!=0)
	{
		convert(n/base, base);
		printf("%d",n%base);
	}
}

