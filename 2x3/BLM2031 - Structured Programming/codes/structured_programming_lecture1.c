#include<stdio.h>
#include<stdlib.h>






int main() {
	
	
	int *urun,size1;
	int **lower,**upper,bound;
	int loweri=0,upperi=0;
	int i;
	
	printf("enter  the bound: ");
	scanf("%d",&bound); 
	printf("\n");
	printf("enter the size of array urun");
	scanf("%d",&size1);
	printf("\n");
	
	
	urun=(int*)calloc(size1,sizeof(int));
	upper=(int**)calloc(size1,sizeof(int*));
	lower=(int**)calloc(size1,sizeof(int*));
	
	for(i=0; i<size1; i++){
		
		printf("%d. urunu gir: ",i+1);
		scanf("%d",&*(urun+i));
		
		
	}

	
	
	for(i=0; i<size1; i++) {
		
		if(urun[i]<bound) {
			*(*(lower)+loweri)=urun[i];
			loweri++;
			
		}
		
		else if(urun[i]>bound) {
			
				*(*(upper)+upperi)=urun[i];
				upperi++;
				
			}
	
	}			

	
	for(i=0; i<upperi; i++) {
		
		printf("%d	",*(*(upper)+i));
	}
	printf("\n\n");
	
	for(i=0; i<loweri; i++) {
		
		printf("%d	",*(*(lower)+i));
	}
	
	free(urun);
	free(*upper);
	free(*lower);
	
	
	return 0; 
	
}
