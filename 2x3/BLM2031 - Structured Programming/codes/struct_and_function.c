#include<stdio.h>
#include<stdlib.h>
typedef struct {
		
		char name[30];
		short year;
		float mark;
		
		
	}STD;

void FindMax(STD*,int);
void UpdateMarks(STD*);
STD* AreaExpand(int);
	
int main() {
	
	STD stds[3],stds1,stds2,*stdsptr;
	
	int i,n=3;
	
	for(i=0; i<n; i++) {
		
		scanf("%s %d %d",stds[i].name,&stds[i].year,&stds[i].mark);
		
	}
	
	FindMax(stds,n);
	
	scanf("%s %d %d",stds2.name,&stds2.year,&stds2.mark);
	
	UpdateMarks(&stds2);
	
	stdsptr=AreaExpand(n);
	
	return 0; 
	
}

void FindMax(STD* stds, int n) {
	
	int i,max=0;
	
	for(i=0; i<n; i++) {
		
		if(stds[i].mark>max) {
			
			max=stds[i].mark;
		}
	}
	
	printf("%d",max);
}

void UpdateMarks(STD* stds) {
	
	if((*stds).year<18) {
		
		(stds->mark)++;
	}
}

STD* AreaExpand(int n) {
	
	return (STD*)calloc(n,sizeof(STD));
}
	
	
	
	
	
	
