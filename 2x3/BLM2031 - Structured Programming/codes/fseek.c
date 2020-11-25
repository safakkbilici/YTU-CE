#include<stdio.h>
#include<stdlib.h>
#define LINESIZE 100
typedef struct {
	
	char name[20];
	char surname[20];
	int age;
}SAFAK;

void __init__(SAFAK*);

int main() {
	
	char line[LINESIZE];
	
	SAFAK* person;
	FILE* fp=fopen("abc.txt","r");;
	
	/*
	fp=fopen("abc.txt","w+");
	person=(SAFAK*)calloc(5,sizeof(SAFAK));
	__init__(person);
	
	
	for(int i=0; i<5; i++) {
		
		fprintf(fp,"NAME: %s \t SURNAME: %s \t AGE: %d\n",person[i].name,person[i].surname,person[i].age);
		
	}
	*/
	
	int offset=1*sizeof(SAFAK);
	
	fseek(fp,offset,SEEK_SET);
	
	while(!feof(fp)) {
		
	}
	
	fgets(line,LINESIZE,fp);
	
	printf("%s",line);
	
	
	
	
	
	
	return 0;
}

void __init__(SAFAK* person){
	
	for(int i=0; i<5; i++) {
		
		printf("Name: ");
		scanf("%s",person[i].name);
		printf("Surname: ");
		scanf("%s",person[i].surname);
		printf("Age: ");
		scanf("%d",&person[i].age); 
	}

}


