#include<stdio.h>
#include<stddef.h>
#define ERR_FLAG 1
#define EOF_FLAG 2
#define LINESIZE 100
#define FAIL 0
#define SUCCESS 1

FILE* file_open(char*,char*);
char check_file(FILE*);
int copy_line_by_line(char*,char*);
int copy_char_by_char(char*,char*);

int main() {
	
	char file_namei[100], file_nameo[100];
	int flag;
	
	printf("Enter the name of input file: ");
	scanf("%s",file_namei);
	printf("Enter the name of output file: ");
	scanf("%s",file_nameo);
	
	flag=copy_line_by_line(file_namei,file_nameo);
	printf("%d",flag);

}

FILE* file_open(char* file_name, char* mode) {
	
	FILE* fp;
	
	fp=fopen(file_name,mode);
	
	if(fp == NULL) {
		
		fprintf(stderr,"Error opening file!\n");
		return 0;
	}
	
	return fp;
}

char check_file(FILE* fp){  //sonda
	
	char stat=0;
	
	if(ferror(fp))
		stat|=ERR_FLAG;
	if(feof(fp)) 
		stat|=EOF_FLAG;
	clearerr(fp);
	return stat;
}
int copy_line_by_line(char* input_file, char* output_file) {
	
	FILE* fp1,*fp2;
	char line[LINESIZE];
	int lineNum=0;
	
	if((fp1= fopen(input_file,"r")) == NULL) return FAIL;
	if((fp2 = fopen(output_file,"w")) == NULL) {
		fclose(fp1);
		return FAIL;
	}
	
	while(fgets(line,LINESIZE-1,fp1) != NULL ) {
		
		fputs(line, fp2);
		lineNum++;
	}
	fprintf(fp2,"dosyada %d line var\n",lineNum);
	fclose(fp1);
	fclose(fp2);
	return SUCCESS;
}

int copy_char_by_char(char* input_file, char* output_file) {
	
	FILE* fp1, *fp2;
	char ch1, ch2;
	int charNum=0;
	
	if((fp1 = fopen(input_file,"r")) == NULL) return FAIL;
	if((fp2 = fopen(output_file,"w")) == NULL) {
		fclose(fp1);
		return FAIL;
	}
	
	fscanf(fp1,"%c",&ch2);
	ch1=getc(fp1);
	
	while(!feof(fp1)){
		
		putc(ch1,fp2);
		ch1=getc(fp1);
		charNum++;
	}
	
	fclose(fp1);
	fclose(fp2);
	return SUCCESS;
}
		
		
		
		
		
		
		
		
	
	
	
	

