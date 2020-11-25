#include<stdio.h>
#include<string.h>
#define LINESIZE 100
#define SUCCESS 1

int line_by_line_copy(FILE*,FILE*);
int char_by_char_copy(FILE*,FILE*);

int main() {
	
	FILE* fp1,*fp2;
	char file_namei[100], file_nameo[100],copy_mode[10];
	int control_flag;
	
	printf("Enter the name of input file: ");
	scanf("%s",file_namei);
	printf("Enter the name of output file: ");
	scanf("%s",file_nameo);
	printf("How to copy: ");
	scanf("%s",copy_mode);
	
	fp1=fopen(file_namei,"r");
	fp2=fopen(file_nameo,"w");
	
	if(strcmp(copy_mode,"line") == 0) {
	control_flag=line_by_line_copy(fp1,fp2);
	printf("%d",control_flag);
	}
	else if(strcmp(copy_mode,"char")==0) {
		control_flag=char_by_char_copy(fp1,fp2);
		printf("%d",control_flag);
	}
	
	
	fclose(fp1);
	fclose(fp2);
	
	return 0;
}

int line_by_line_copy(FILE* fp1, FILE* fp2) {
	
	char line[LINESIZE];
	int lineNum=0;
	
	
	while(fgets(line,LINESIZE-1,fp1) != NULL ) {
		
		fputs(line,fp2);
		lineNum++;
	}
	fprintf(fp2,"%d line", lineNum);
	return SUCCESS;
}

int char_by_char_copy(FILE* fp1, FILE* fp2) {
	
	
	char ch1,ch2;
	int charNum=0;
	fscanf(fp1,"%c",&ch2);
	ch1=getc(fp1);
	
	while(!feof(fp1)) {
		
		putc(ch1,fp2);
		ch1=getc(fp1);
		charNum++;
	}
	fprintf(fp2,"%d char",charNum);
	fclose(fp1);
	fclose(fp2);
	return SUCCESS;
}
	
	
	
	
