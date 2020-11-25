#include<stdio.h>
#include<stdlib.h>


struct	ogr {
	
	char ogr_isim[15], ogr_soyisim[20];
	
	short ogr_yas;
	
	float ogr_puan;
	
};


int main() {
	
	int i, max=0, maxLoc;
	struct ogr *ogrenci,ogrenciler[3];
	struct ogr *maxLocStr;
	
	for(i=0; i<3; i++) {
		
		scanf("%s %s %d %f",ogrenciler[i].ogr_isim,ogrenciler[i].ogr_soyisim,
							&ogrenciler[i].ogr_yas,&ogrenciler[i].ogr_puan);
	    
	    if(ogrenciler[i].ogr_puan>max)  {
			
			max=ogrenciler[i].ogr_puan;
			maxLoc=i;
			
		}
	}
	
	/*
	 
	 //scanf ile ogrrenciler[i].ogr_isim şeklinde alındı bilgiler
	 * 
	 ogrenci=ogrenciler;
	 max=0;
	 for(i=0; i<3; i++) {
		
		if(ogrenci->ogr_puan>max) {
			
			max=ogrenci->ogr_puan;
			maxLocStr=ogrenci;
		}
		ogrenci++;
	}
	
	printf("%s",maxLocStr->ogr_soyisim);
	 */
	
	printf("%s %d",ogrenciler[maxLoc].ogr_isim,max);
	
	printf("\n");
	
	ogrenci=&ogrenciler[maxLoc];
	
	max=0;
	
	printf("%s",ogrenci->ogr_soyisim); // printf("%s",(*ogrenci).ogr_soyisim); // calling member from struct with pointer
	
	
	
		
	
	
	
	
	return 0;
	
} 
