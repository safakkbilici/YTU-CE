#include<stdio.h>
#include<stdlib.h>



typedef struct {
	
		char std_name[15], std_surname[20];
		
		short std_year;
		
		float std_mark;
		
	}std;
	
	
	
int main() {
	
	
	std *students;
	
	int n;
	
	scanf("%d",&n);
	
	students=(int*)calloc(n,sizeof(int));
	
	students[0].std_year=19; // students->std_year=19;  or  (*students).std_year=19;
	
	printf("%d",students->std_year);
	
	free(students);
	
	
	
	
	
	
	return 0; 
	
}


