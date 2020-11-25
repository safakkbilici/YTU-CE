#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LINESIZE 200
typedef struct{
	
	char name[100];
	char surname[100];
	char gender[7];
	char job[20];
	int age;
	
}employees;

void get_member(employees*,int);
void employee_file(FILE*,int,employees*);


int main() {
	
	employees* person;
	int number_of_employee;
	FILE* fp;
	
	printf("Enter the number of employee: ");
	scanf("%d",&number_of_employee);
	
	person=(employees*)calloc(number_of_employee,sizeof(employees));
	
	get_member(person,number_of_employee);
	
	employee_file(fp,number_of_employee,person);
	
	return 0;
	
}

void get_member(employees* person,int number_of_employee) {
	
	
	for(int i=0; i<number_of_employee; i++) {
		
		printf("Name of Employee %d: ",i+1);
		scanf("%s",person[i].name);
		printf("Surname of Employee %d: ",i+1);
		scanf("%s",person[i].surname);
		printf("Gender of Employee %d: ",i+1);
		scanf("%s",person[i].gender);
		printf("Job of Employee %d: ",i+1);
		scanf("%s",person[i].job);
		printf("Age of Employee %d: ",i+1);
		scanf("%d",&person[i].age);
		
		printf("\n");
		
	}

}

void employee_file(FILE* fp,int number_of_employee, employees* person) {
	
	int i;
	char file_name[100];
	char* strconcat;
	
	for(i=0; i<number_of_employee; i++) {
		
		strconcat= strcat(person[i].name,person[i].surname);
		
		fp=fopen(strconcat,"w");
	
		fprintf(fp,"Name:v%s\nSurname: %s\nGender: %s\nJob: %s\nAge: %d",person[i].name,person[i].surname,person[i].gender,person[i].job,person[i].age);
		fclose(fp);
		
	}
	
}
