#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GIRL_FILE "ragazze.txt"
#define BOY_FILE "ragazzi.txt"
#define MAX_STR  35 + 1

typedef struct t_student{
	char *name;				//name of the student
	char *surname;				//surname of the student
	int  day, month, year;			//date of birth
	char sex;				//student sex (M/F)
} t_student;

void sort(t_student *v, int n);			//sorting function
void swap(t_student *s1, t_student *s2);	//swap function
int  date(t_student s);				//date converter

int main(int argc, char *argv[])
{
	//data structure
	int n,i;				//number of students and iteration variable	
	t_student *student;			//vector of students
	FILE *fp, *fp2;				//file pointer
	char str[MAX_STR];			//temporary variables for reading names, surnames
	
	//arguments test
	if(argc < 2){
		fprintf(stderr, "Parameters error!\nUsage: ./2 <input file>\n");
		return -1;
	}	
	//file opening
	if((fp = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Can't open %s\n", argv[1]);
		return -2;
	}
	//file reading
	fscanf(fp, "%d", &n);
	student = (t_student *) malloc(n*sizeof(t_student));
	for(i=0; i<n; i++)
	{
		fscanf(fp,"%s",str);								//name
		student[i].name = malloc((strlen(str)+1)*sizeof(char));
		strcpy(student[i].name, str);
		fscanf(fp,"%s",str);								//surname
		student[i].surname = malloc((strlen(str)+1)*sizeof(char));
		strcpy(student[i].surname, str);
		fscanf(fp,"%d%*c%d%*c%d",&student[i].day,&student[i].month,&student[i].year);	//date
		student[i].sex = 0;								//sex
		while(student[i].sex != 'M' && student[i].sex != 'F') 
			fscanf(fp,"%c", &student[i].sex);
	}
	fclose(fp);
	
	//sorting vector
	sort(student, n);
	
	//print sorted vector
	if((fp = fopen(BOY_FILE,"w")) == NULL){
		fprintf(stderr, "Can't open %s\n", BOY_FILE);
		return -3;
	}
	if((fp2 = fopen(GIRL_FILE,"w")) == NULL){
		fprintf(stderr, "Can't open %s\n", GIRL_FILE);
		return -4;
	}
	for(i=0; i<n; i++)
		fprintf(student[i].sex == 'M' ? fp:fp2,"%s %s %d/%d/%d %c\n", 
			student[i].name, student[i].surname,  student[i].day,  
			student[i].month,  student[i].year,  student[i].sex);
	
	//clean memory
	for(i=0; i<n; i++){
		free(student[i].name);
		free(student[i].surname);
	}
	free(student);
	return 0;
}

void sort(t_student *s, int n)		//insertion sort
{
	int i,j;
	int lowest, lowest_index;
	
	for(i=0; i<n-1; i++)
	{
		lowest = date(s[i]);
		lowest_index = i;
		
		for(j=i+1; j<n; j++)
			if(date(s[j]) < lowest)
			{
				lowest_index = j;
				lowest = date(s[j]);
			}
		swap(&s[i], &s[lowest_index]);
	}	
}

int  date(t_student s)
{
	return s.year*16384 + s.month*128 + s.day;
	//return s.year*10000 + s.month*100 + s.day;
}

void  swap(t_student *s1, t_student *s2)
{
	t_student tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
