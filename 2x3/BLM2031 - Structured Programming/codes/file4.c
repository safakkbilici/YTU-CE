#include <stdio.h>
#include <stdlib.h>
#define LEN 20


typedef struct vitalstat
{ 
 	char name[LEN]; 
	char surname[LEN]; 
	int day;
	int month;
	int year;
} STUDENT; 

void printf_file(char*);
void list_file(FILE*);

int main() {
	
	
	char file_name[20];
	FILE* std_file;
	STUDENT std;
	
	int k=0,stat=0;
	long offset=0;
	
	printf("File name: ");
	scanf("%s",file_name);
	
	printf_file(file_name);
	
	std_file=fopen(file_name,"r+b");
	
	list_file(std_file);
	
	
	printf("\nwhich person you want to reach: ");
	scanf("%d",&k);
	
	offset=k*sizeof(STUDENT);
	stat=fseek(std_file,offset,SEEK_SET);
	fread(&std,sizeof(STUDENT),1,std_file);
	
	printf("kth person data: ");
	printf("%s %s %d %d %d\n",std.name,std.surname,std.day,std.month,std.year);
	
	printf("New Name: ");
	scanf("%s",std.name);
	
	stat=fseek(std_file,offset,SEEK_SET);
	fwrite(&std,sizeof(STUDENT),1,std_file);
	list_file(std_file);
	
	
	
	
	
	
	
	
	return 0;
}

void printf_file(char filename[]) {
	
	int nb;
	
	STUDENT std;
	
	FILE* fs=fopen(filename,"wb");
	
	printf("How many person: ");
	scanf("%d",&nb);
	
	for(int i=0; i<nb; i++) {
		
		scanf("%s %s %d %d %d",std.name,std.surname,&std.day,&std.month,&std.year);
		fwrite(&std,sizeof(STUDENT),1,fs);
	}
	fclose(fs);
}

void list_file(FILE* fp) {
	
	STUDENT std;
	
	printf("list:\n");
	fseek(fp,0,SEEK_SET);
	fread(&std,sizeof(STUDENT),1,fp);
	while(!feof(fp)) {
		printf("%s %s %d %d %d\n",std.name,std.surname,std.day,std.month,std.year);
		fread(&std,sizeof(STUDENT),1,fp);
	}
	
}
