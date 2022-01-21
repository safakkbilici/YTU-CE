#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct oda{
	int id;
	float yukseklik,genislik,uzunluk;
};


void GetInfo(struct oda *dizi, int n);
void ScanRooms(struct oda *dizi, int n);
void sortbyVolume(struct oda *dizi, int n);
void printfInfo(struct oda *dizi, int n);

int main(){
	
	int n;
	printf("Oda sayisini giriniz : "); scanf("%d", &n);
	
	struct oda *dizi;
	
	dizi = (struct oda*) malloc(n*sizeof(struct oda));
	if( dizi == NULL ) {
		printf("out of memory."); exit(1);
	}
	
	GetInfo(dizi,n);
	
	ScanRooms(dizi,n);
	printfInfo(dizi,n);
	
	
	printf("\n\n");
	
	
	sortbyVolume(dizi,n);
	printfInfo(dizi,n);
	
	free(dizi);
	
	return 0;
}


void GetInfo(struct oda *dizi, int n ){
	int i;
	for(i=0;i<n;i++){
		printf("%d. Odanin bilgilerini giriniz;\n",i+1);
		printf("ID : "); scanf("%d",&(dizi+i)->id);
		printf("Yukseklik : "); scanf("%f",&(dizi+i)->yukseklik);
		printf("Genislik : "); scanf("%f",&(dizi+i)->genislik);
		printf("Uzunluk : "); scanf("%f",&(dizi+i)->uzunluk);
	}
}

void ScanRooms(struct oda *dizi, int n){
	float sagHacim,solHacim,Hacim;
	int i;
	
	for(i=1;i<n-1;i++){
		sagHacim = ((dizi+i+1)->yukseklik) * ((dizi+i+1)->genislik) * ((dizi+i+1)->uzunluk);
		solHacim = ((dizi+i-1)->yukseklik) * ((dizi+i-1)->genislik) * ((dizi+i-1)->uzunluk);
		Hacim = ((dizi+i)->yukseklik)*((dizi+i)->genislik)*((dizi+i)->uzunluk);
		printf("\nScanned Rooms\n");
		if(Hacim>solHacim && Hacim>sagHacim){
			printf("%d\n",(dizi+i)->id);
		}
	}
}

void sortbyVolume(struct oda *dizi, int n){
	int i, j;
	float min; 
	struct oda temp;
	
	for(i = 0; i < n-1; i++){
		
		min = ((dizi+i)->yukseklik) * ((dizi+i)->genislik) * ((dizi+i)->uzunluk);
		for(j = i+1; j < n; j++){
			
			if((((dizi+j)->yukseklik) * ((dizi+j)->genislik) * ((dizi+j)->uzunluk)) < min){
				
				temp = *(dizi+i);
				*(dizi+i)= *(dizi+j);
				*(dizi+j)= temp;
				min = ((dizi+j)->yukseklik) * ((dizi+j)->genislik) * ((dizi+j)->uzunluk);
			}
		}
	} 
}

void printfInfo(struct oda *dizi, int n){
	int i;
	float hacim;
	for(i=0;i<n;i++){
		hacim = ((dizi+i)->yukseklik) * ((dizi+i)->genislik) * ((dizi+i)->uzunluk);
		printf("\nOda %d\nID : %d \nYukseklik   : %f \nGenislik  : %f \nUzunluk  : %f\nHacim : %f\n ",i+1,(dizi+i)->id,(dizi+i)->yukseklik,(dizi+i)->genislik,(dizi+i)->uzunluk,hacim); 
	}
}




