#include<stdio.h>


int i=15; // program scope
static int j=3;

/*
void printi(int i){
	
	printf("%d",i); 
	
}

*/

void FixDuration() {
	
	static int fix=2;
	int i; // block scope fix duration
	
	fix++; 
	
	printf("fix: %d\n",fix);
	
	for(i=0; i<3; i++) {
		
		j++;
		
		printf("%d",j);
		
		printf("\n");
	}
	
}

void funA() {
	
	int k=10,i; // block scope
	
	for(i=0; i<3; i++) {
		
		int a=4; // block scope
		
		printf("%d %d %d",k,a,i);
		printf("\n");
		
	}
}




int main() {
	
	/*
	
	int i=100; //block scope
	
	
	printf("%d",i); //100
	
	printi(i); //100
	
	
	*/
	
	
	int k=5,i; // block scope
	
	for(i=0; i<3; i++) {
		
		k++;
		
		goto PrintAgain;
		
	}
	
	PrintAgain:
	
	printf("%d %d %d",i,j,k); // 0 , 3 , 6
	
	printf("\n\n");
	
	
	FixDuration();
	printf("\n");
	funA();
	
	
	return 0;
	
	
}
	
	
	
	
