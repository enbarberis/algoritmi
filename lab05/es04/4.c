#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	char id[11];
	struct person *next;
};

int main(int argc, char *argv[])
{	
	//data structure
	struct person *first = NULL; 	//first person of the queue
	struct person *last  = NULL;	//last persone of the queue
	int choice;			//user menu choice
	char id[11];			//reading var for id
	struct person *p;
	struct person *new;
			
	;//display menu
	printf( "=== M E N U ===\n"
		"0 - push\n"
		"1 - pop\n"
		"2 - print the queue\n"
		"3 - exit\n\n");
	do
	{
		printf("Choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			//push
			case(0):
				printf("ID to push: ");
				scanf("%s", id);
				new = (struct person *) malloc(sizeof(struct person));
				strcpy(new->id,id);
				new->next = NULL;
				if(first != NULL)
				{
					last->next = new;
					last = new;
				}
				else
				{
					first = last = new;
				}
				break;

			case(1):
				if(first != NULL)
				{
					p = first;
					first = first->next;
					free(p);
				}
				break;
				
			//print
			case(2):
				for(p = first; p!=NULL; p=p->next)
					printf("%s\n",p->id);
				break;
		}
	}while(choice != 3);

	return 0;
}
