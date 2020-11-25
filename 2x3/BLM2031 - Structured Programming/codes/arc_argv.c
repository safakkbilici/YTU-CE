#include<stdio.h>



int main (int argc, char* argv[]) { // macro.c      ./macro topla 4 6
	
	int sayi1,sayi2;
	if(argc!=4) {
		printf("yanlis");
		return 0;
	}
	
	sayi1=atoi(argv[1]);
	sayi2=atoi(argv[3]);
	
	if(!strcpy("toplam",argv[1])) {
		printf("%d",sayi1+sayi2);
	}
	else{
		printf("%d",sayi1-sayi2);
	}
	
	
	return 0;
}
