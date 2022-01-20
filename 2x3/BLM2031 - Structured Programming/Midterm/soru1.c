#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define size 100
#define SIZE_OF_ARRAY(x) (sizeof(x)/sizeof((x)[0]))

int enbuyuk_bul(int **matrix,int n);
void liste_yazdir(int **matrix,int n);

int main(){
	
	
	int n,i,j;
	printf(" Matrisin satir sayisini giriniz : "); scanf("%d", &n);
	
	int **matrix = (int**) malloc(n * sizeof(int*));
	if(matrix == NULL) {
		printf("%s:%d>Can not allocate memory for the array...\n",__FILE__, __LINE__);
		exit(0);
	}
	
	for(i=0;i<n;i++){
		matrix[i] = (int*) malloc(2 * sizeof(int));
	}
	
	printf("Matris elemanlarini giriniz\n");
	for(i=0;i<n;i++){
		for(j=0;j<2;j++){
			printf("Matrix 1 (%d)(%d) = ",i+1,+1+j);
			scanf(" %d",&matrix[i][j]);
		}
	}
	
	int row= enbuyuk_bul(matrix,n);
	
	printf("\nen buyuk karenin olduðu satýr : %d\n\n",row);
	
	liste_yazdir(matrix,n);
	

	
	
	for (i = 0; i < n; i++)
    {
        free (matrix [i]);
    }
    free (matrix);
	return 0;
}

int enbuyuk_bul(int **matrix,int n){
	
	int i,j;
	int clm=0,max=0;
	for(i=0;i<n;i++){
		if( ((matrix[i][0]*matrix[i][0])+(matrix[i][1]*matrix[i][1]))>max ){
			max=((matrix[i][0]*matrix[i][0])+(matrix[i][1]*matrix[i][1]));
			clm= i;
		}	
	}

	return clm+1;
}


void liste_yazdir(int **matrix,int n){
	
	int i;
	
	for(i=0;i<n;i++){
		if(matrix[i][1]>=0){
			printf("%d+%di\n",matrix[i][0],matrix[i][1]);
		}
		else{
			printf("%d%di\n",matrix[i][0],matrix[i][1]);
		}
	}
	
}
