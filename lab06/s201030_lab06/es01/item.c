#include "item.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct t_career{
	int credits;
	float average;
};

struct t_student{
	char *name;
	char *surname;
	char *id;
	struct t_career career;
};

int compare_name(Item a, Item b)
{
	return strcmp(a->name,b->name);
}

int compare_surname(Item a, Item b)
{

	return strcmp(a->surname,b->surname);
}

int compare_id(Item a, Item b)
{
	return strcmp(a->id, b->id);
}

int compare_average(Item a, Item b)
{
	return a->career.average -  b->career.average;
}

Item item_scan()
{
	Item i = malloc(sizeof (*i));
	char str[MAX_STR];
	
	printf("\nName: ");
	scanf("%35s", str);
	i->name = (char *)malloc((strlen(str)+1)*sizeof(char));
	strcpy(i->name, str);

	printf("Surname: ");
	scanf("%35s", str);
	i->surname = (char *)malloc((strlen(str)+1)*sizeof(char));
	strcpy(i->surname, str);

	printf("ID: ");
	scanf("%35s", str);
	i->id = (char *)malloc((strlen(str)+1)*sizeof(char));
	strcpy(i->id, str);

	printf("Average: ");
	scanf("%f", &i->career.average);

	printf("Credits: ");
	scanf("%d", &i->career.credits);

	return i;
}

Item item_new(char *n, char *s, char *i, float a, int c)
{
	Item x = malloc(sizeof(*x));
	
	x->name = (char *)malloc((strlen(n)+1)*sizeof(char));
	strcpy(x->name, n);
	
	x->surname = (char *)malloc((strlen(s)+1)*sizeof(char));
	strcpy(x->surname, s);
	
	x->id = (char *)malloc((strlen(i)+1)*sizeof(char));
	strcpy(x->id, i);	
	
	x->career.average = a;
	x->career.credits = c;
	return x;
}

void item_print(Item i)
{
	printf("\nName: %s\n", i->name);
	printf("Surname: %s\n", i->surname);
	printf("Id: %s\n", i->id);
	printf("Average: %.2f\n",i->career.average);
	printf("Credits: %d\n",i->career.credits);
}

void item_free(Item i)
{
	free(i->name);
	free(i->surname);
	free(i->id);
	free(i);
}
