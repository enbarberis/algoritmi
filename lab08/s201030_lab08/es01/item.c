#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct person{
	char *id;
	char *name;
	char *surname;
	int day;
	int month;
	int year;
};

Item new_item(char *id, char *name, char *surname, int day, int month, int year)
{
	Item i = malloc(sizeof(*i));
	
	i->id = (char *) malloc((strlen(id)+1)*sizeof(char));
	strcpy(i->id, id);
	
	i->name = (char *) malloc((strlen(name)+1)*sizeof(char));
	strcpy(i->name, name);
	
	i->surname = (char *) malloc((strlen(surname)+1)*sizeof(char));
	strcpy(i->surname, surname);

	i->day = day;
	i->month = month;
	i->year = year;

	return i;
}

int compare_item(Item a, Item b)
{
	return strcmp(a->id, b->id);
}

void print_item(Item i)
{
	printf("\nID:            %s\n"
		 "NAME:          %s\n"
		 "SURNAME:       %s\n"
		 "DATE OF BIRTH: %.2d/%.2d/%4d\n",
		  	i->id,
		  	i->name,
			i->surname,
			i->day, i->month, i->year);
}

void free_item(Item i)
{
	free(i->id);
	free(i->name);
	free(i->surname);
	free(i);
}
