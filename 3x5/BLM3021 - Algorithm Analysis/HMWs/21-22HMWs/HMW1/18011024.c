#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<conio.h>


int get_total_sample_number();          //txt dosyasýnda bulunan toplam nokta adedini döndüren fonksiyon.
int** matrix_allocation(int);			//nokta sayýsý kadar Nx2 boyutunda matrix allocate eden fonksiyon
void read_from_txt(int**,int);			//txt dosyasýnda bulunan noktlarý okuyup oluþturulan matrixe kaydeden fonksiyon
float find_closest_pair(int**,int,int);	//Divide&Conquer algoritmasý ile en yakýn iki noktayý bulan fonksiyon
float brute_force(int**,int,int);		//eleman sayýsý üçten küçük olan anlarda en kýsa uzunluðu bulan fonksiyon
float find_min(float,float);			//verilen iki noktadan minimum olanýný bulan fonksiyon
float line_closest(int**,int,float);	//ikiye bölünen matrixin ortasýndan belli bir noktaya kadar tarayan ve minimum(mevcut ise)
										// uzaklýðý döndüren fonksiyon
float distance(int**,int,int);			//iki nokta arasýndaki uzaklýðý hesaplayan fonksiyon
void free_matrix(int**,int);			//allocate edilen matrix alanýný boþaltan fonksiyon
void InsertionSort_by_x(int**,int);		//verilen matrixi inseriton sort uygulayarak x deðerlerine göre sýralayan fonksiyon
void InsertionSort_by_y(int**,int);		//verilen matrixi inseriton sort uygulayarak y deðerlerine göre sýralayan fonksiyon

void MergeSort_by_x(int**,int, int);
void Merge(int**, int, int, int);

int main(){
	
	int n = get_total_sample_number();
	int** matrix = matrix_allocation(n);
	read_from_txt(matrix,n);

	InsertionSort_by_x(matrix,n);
	//MergeSort_by_x(matrix,0,n);
	printf("\nwith Divede & Counquer : %f", find_closest_pair(matrix,0,n));
	
	free_matrix(matrix, n);
	
	return 0;
}

int get_total_sample_number(){
	
	char ch;
	int count = 1;
	FILE *f_sample;
	f_sample = fopen("sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	while((ch=getc(f_sample)) != EOF)
		if(ch == '\n')
			count++;
	
	fclose(f_sample);
	return count;
}

int** matrix_allocation(int n){
	
	int i;
	
	int **matrix = (int**) calloc(n, sizeof(int*));
	if(matrix == NULL){
		perror("Could Not Allocate the Space for Matrix ");
		exit -1;
	}
	
	for(i=0;i<n;i++){
		matrix[i] = (int*) calloc(2, sizeof(int));
	}
	
	return matrix;
}

void read_from_txt(int** matrix, int n){
	
	int i;
	FILE *f_sample;
	f_sample = fopen("sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	for(i=0;i<n;i++){
		fscanf(f_sample, "%d %d", &matrix[i][0], &matrix[i][1]);
	}
	
	fclose(f_sample);	
}

float find_closest_pair(int** matrix, int l, int n){
	
	if( (n-l) <= 3 )
		return brute_force(matrix, l, n);
	
	int medyan = ((n-l)/2) + l;
	float dl = find_closest_pair(matrix, l, medyan);
	float dr = find_closest_pair(matrix, medyan, n);
	float d = find_min(dl, dr);
	
	int** line = matrix_allocation(n);
	int i,j=0;
	for(i=l;i<n;i++){
		if( abs(matrix[i][0] - matrix[medyan][0] < d) ){
			line[j][0] = matrix[i][0];
			line[j][1] = matrix[i][1];
			j++;
		}		
	}
	//printf("dl:%f dr:%f mid_line:%f l:%d m:%d n:%d\n",dl,dr,line_closest(line,j,d),l,medyan,n);

	d = find_min(d, line_closest(line, j, d));
	
	free_matrix(line, n);
	
	return d;
}

float brute_force(int** matrix, int l, int n){
	
	float min = FLT_MAX;
	int i, j;
	
	for(i=l;i<n;i++){
		for(j=i+1;j<n;j++){
			if(distance(matrix,i,j)<min)
				min = distance(matrix,i,j);
		}
	}
	
	return min;
}

float find_min(float a, float b){
	
	return (a<b)? a : b;
}

float line_closest(int** matrix, int n, float d){
	
	float min = d;
	int i,j;
	
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(distance(matrix,i,j)<min)
				min = distance(matrix,i,j);
		}
	}
	
	return min;
}

float distance(int** matrix, int i, int j){
	
	return sqrt ( (matrix[i][0] - matrix[j][0]) * (matrix[i][0] - matrix[j][0]) +
				  (matrix[i][1] - matrix[j][1]) * (matrix[i][1] - matrix[j][1]) );
}

void free_matrix(int** matrix, int row){
	
	int i;
	for(i=0;i<row;i++){
		free(matrix[i]);
    }
    free(matrix);
}

void InsertionSort_by_x(int** matrix, int n){
	
	int i, j, key, key2;
	
	for(i=1;i<n;i++){
		
		key = matrix[i][0];
		key2 = matrix[i][1];
		j = i-1;
		
		while( j>=0 && key<matrix[j][0] ){
			
			matrix[j+1][0] = matrix[j][0];
			matrix[j+1][1] = matrix[j][1];
			j = j-1;	
		}
		matrix[j+1][0] = key;
		matrix[j+1][1] = key2;
	}
}

void InsertionSort_by_y(int** matrix, int n){
	
	int i, j, key, key2;
	
	for(i=1;i<n;i++){
		
		key = matrix[i][0];
		key2 = matrix[i][1];
		j = i-1;
		
		while( j>=0 && key2<matrix[j][1] ){
			
			matrix[j+1][0] = matrix[j][0];
			matrix[j+1][1] = matrix[j][1];
			j = j-1;	
		}
		matrix[j+1][0] = key;
		matrix[j+1][1] = key2;
	}
}

void MergeSort_by_x(int** matrix, int l, int r){
    int m;
     if( l < r) {
         m = (l+r) / 2;
         MergeSort_by_x(matrix, l, m);
         MergeSort_by_x(matrix, m, r);
         Merge(matrix, l, m, r);
    } 
} 

void Merge(int** matrix, int l, int m, int r) {

    int k, j, i;
    int n1 = m - l +1;
    int n2 = r - m;

    int** tmp1 = matrix_allocation(n1) ;
    int** tmp2 = matrix_allocation(n2) ;
    

    for (i = 0; i < n1; i++) {
        tmp1[i][0] = matrix[l+i][0] ;
        tmp1[i][1] = matrix[l+i][1];
    } 

   for (j = 0; j < n2; j++) {
        tmp2[j][0] = matrix[m+1+j][0] ;
        tmp2[j][1] = matrix[m+1+j][1];
    } 

    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 

    while (i < n1 && j < n2) { 

        if (tmp1[i][0] <= tmp2[j][0] ) { 

            matrix[k][0] = tmp1[i][0];
            matrix[k][1] = tmp1[i][1];
            i++; 

        } 

        else { 

            matrix[k][0] = tmp2[j][0];
            matrix[k][1] = tmp2[j][1]; 

            j++; 

        } 

        k++;
    } 
    while (i < n1) { 

        matrix[k][0] = tmp1[i][0];
        matrix[k][1] = tmp1[i][1];

        i++; 

        k++; 
    }
    

    while (j < n2) { 

        matrix[k][0] = tmp2[j][0];
        matrix[k][1] = tmp2[j][1];

        j++; 
        k++; 
    }

   free_matrix(tmp1,n1);
   free_matrix(tmp2,n2);
} 

