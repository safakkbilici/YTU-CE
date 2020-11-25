#include<stdio.h>
#include<stdlib.h>

float** initmatrix(int row, int col) {
	
	float **mat;
	int i,j;
	
	mat=(float**)calloc(row,sizeof(float*));
	
	for(i=0; i<row; i++) {
		
		mat[i]=(float*)calloc(col,sizeof(float));
		
	}
	
	for(i=0; i<row; i++) {
		
		for(j=0; j<col; j++) {
			
			printf("enter the matrix[%d][%d]:  ",i,j);
			
			scanf("%f",&mat[i][j]);
			
			printf("\n");
			
		}
	}
	
	
	
	return mat;
	
}
	
	
	


int matrixaddition(int mat[][50], int dim1, int dim2) {
	
	int i,j,sum=0;
	
	sum=0;
	
	for(i=0; i<dim1; i++) {
		
		for(j=0; j<dim2; j++) {
			
			sum= sum + mat[i][j];
			
			
		}
	}
	
	return sum;
	
}
	
	
	
	

int arrayaddition(int* arr, int size) {
	
	int i,sum=0;
	
	for(i=0; i<size; i++) {
		
		sum=*(arr+i)+sum;
		
		
	}

	return sum;
}


int* initarray(int size) {  // int** initarray segmentation fault core dumped??????????????????
	
	
	int* arr;
	printf("\n");
	
	arr=(int*)calloc(size,sizeof(int));
	int i;
	
	for(i=0; i<size; i++) {
		
		printf("enter the %d. element: ",i+1);
		scanf("%d",&*(arr+i));
		printf("\n");
	}
	
	return arr;
}


int* initarrayrealloc(int* arr, int size, int newsize) {
	
	
	
	arr=realloc(arr,(newsize+size)*sizeof(int));
	
	
	return arr;
	
	
	
	
}
	


int main () {
	
	
	
	int arr[52],size,i,sum,*arr1,newsize,summ;
	
	
	
	int mat[50][50],rowm,colm,j;
	
	float **mat1;
	
	
	
	
	printf("enter the size of arr: ");
	scanf("%d",&size);
	printf("\n\n");
	
	for(i=0; i<size; i++) {
		
		
		printf("enter the %d. element of arr: ",i+1);
		scanf("%d",&arr[i]);
		
	}
	
	
	
	sum=arrayaddition(arr,size);
	
	printf("\n\n%d",sum);
	
	arr1=initarray(size);
	
	
	printf("\nnewsize for realloc: ");
	
	scanf("%d",&newsize);
	
	
	
	
	
	arr1=initarrayrealloc(arr1,size,newsize);
	
	
	printf("enter the row size and column size of the matrix: ");
	scanf("%d %d",&rowm,&colm);
	
	
	
	printf("\n");
	
	for(i=0; i<rowm; i++) {
		
		for(j=0; j<colm; j++) {
			
			printf("enter the matrix[%d][%d]:  ",i,j);
			
			scanf("%d",&*((*mat+i)+j));
			
			printf("\n");
			
		}
	}
			
	
	summ=matrixaddition(mat,rowm,colm);

	
	
	printf("\n%d",summ);
	
	
	mat1=initmatrix(rowm,colm);
	
	printf("\n\n");
	
	
	for(i=0; i<rowm; i++) {
		
		for(j=0; j<colm; j++) {
			
			printf("%f	",mat1[i][j]);
			
		}
		
		printf("\n");
		
	}
	
	
	
	
	
	return 0;
}
