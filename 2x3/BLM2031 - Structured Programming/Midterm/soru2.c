#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Student{
	
	char name[20];
	int id,age;
	float gpa;
	
};

void nota_gore_sirala(struct Student *dizi,int n ){
	
	int i, j;
	float min;
	struct Student temp;
	
	for(i = 0; i < n-1; i++){
		
		min = (dizi+i)->gpa;
		for(j = i+1; j < n; j++){
			
			if(((dizi+j)->gpa) < min){
				
				temp = *(dizi+i);
				*(dizi+i)= *(dizi+j);
				*(dizi+j)= temp;
				min = (dizi+j)->gpa;
			}
		}
	}
	
	
}

void ada_gore_sirala(struct Student *dizi,int n){
	
	int i, j=0;
	struct Student temp;
	
	for(i = 0; i < n; i++){
		
		while((dizi+i)->name[j] !='\0'){
			
			if(('a' <=((dizi+i)->name[j])) && (((dizi+i)->name[j]) <= 'z')){
				
				(dizi+i) -> name[j] = ((dizi+i) -> name[j]) - ('a' - 'A');
			}
			j++;
		}
		j=0;
	}
	
	for(i = 0; i < n-1; i++){
		
		for(j = i+1; j < n; j++){
			
			if(strcmp((dizi+i)->name,(dizi+j)->name)> 0){
				
				temp = *(dizi+i);
				*(dizi+i)= *(dizi+j);
				*(dizi+j)= temp;
			}
		}
	}
}

void liste_yaz(struct Student *dizi,int n){
	int i;
	for(i=0;i<n;i++){
		printf("\nSTUDENT %d\nName : %s \nID   : %d \nAge  : %d \nGPA  : %f\n ",i+1,(dizi+i)->name,(dizi+i)->id,(dizi+i)->age,(dizi+i)->gpa); 
	}
	
}
int main(){
	
	int n;
	printf("Ogrenci sayisini giriniz : "); scanf("%d", &n);
	
	struct Student  *ogr_dizi;
	
	ogr_dizi= (struct Student*) malloc(n*sizeof(struct Student));
	if( ogr_dizi == NULL ) {
		printf("out of memory."); exit(1);
	}
	
	int i;
	for(i=0;i<n;i++){
		printf("For student %d\n",i+1);
		printf("Please enter the name of student : "); scanf("%s",(ogr_dizi+i)->name);
		printf("Please enter the id   of student : "); scanf("%d",&(ogr_dizi+i)->id);
		printf("Please enter the age  of student : "); scanf("%d",&(ogr_dizi+i)->age);
		printf("Please enter the gpa  of student : "); scanf("%f",&(ogr_dizi+i)->gpa);
	}
	
	printf("\nSorted by GPA\n");
	nota_gore_sirala(ogr_dizi,n);
	liste_yaz(ogr_dizi,n);
	
	printf("\nSorted by NAME\n");
	ada_gore_sirala(ogr_dizi,n);
	liste_yaz(ogr_dizi,n);
	
	free(ogr_dizi);
	return 0;
}
