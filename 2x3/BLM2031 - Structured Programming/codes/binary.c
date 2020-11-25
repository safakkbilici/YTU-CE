#include<stdio.h>
#include<string.h>
typedef struct {
	
	int a,b,c;
	char klm[3];
}AX;

void write(FILE*);

int main() {
	
	
	FILE* fi,*fo;
	fi=fopen("bilici.BIN","wb");
	write(fi);
	return 0;	
	
}


void write(FILE* fi) {
	
	AX data;
	
	for(int i=0; i<5; i++) {
		
		scanf("%s %d %d %d",data.klm,&data.a,&data.b,&data.c);
		fwrite(&data,sizeof(AX),1,fi);
		
		
	}
}

void read(FILE* fp) {
	
	
	AX data; 
	
	fread(&data,sizeof(AX),1,fp);
	
	while(!feof(fp)) {
		
		printf("%s %d %d %d",data.klm,data.a,data.b,data.c);
		fread(&data,sizeof(AX),1,fp);
	}
	
}
	
	
	
	
	
	
