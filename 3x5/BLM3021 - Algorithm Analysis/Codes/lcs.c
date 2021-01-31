#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void LCS(char*, char*, int**);
void printLCS(char*,char*,int**);

int main(){


  char str1[100];
  strcpy(str1,"BACDB");
  char str2[100];
  strcpy(str2,"BDCB");
  int i,j;


  int** C = (int**)calloc(strlen(str1)+1, sizeof(int*));
  for(i=0; i<strlen(str1)+1; i++){
    C[i] = (int*)calloc(strlen(str2)+1, sizeof(int));
  }

  LCS(str1, str2, C);
  for(i=0; i<strlen(str1)+1; i++){
    for(j=0; j<strlen(str2)+1; j++){
      printf("%d ",C[i][j]);
    }
    printf("\n");
  }
  printLCS(str1,str2,C);
  return 0;
}

void LCS(char* str1, char* str2, int** C){
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int i,j;
  for(i=0; i<len1+1; i++){
    for(j=0; j<len2+1; j++){
      if(i==0){
        C[i][j] = 0;
      }
      else if(i==0){
        C[i][j] = 0;
      }
      else{
        if(str1[i-1] == str2[j-1]){
          C[i][j] = C[i-1][j-1] +1;
        }
        else{
          if(C[i-1][j] > C[i][j-1]){
            C[i][j] = C[i-1][j];
          }
          else{
            C[i][j] = C[i][j-1];
          }
        }
      }
    }
  }
}

void printLCS(char* str1, char* str2, int** C){

  int index = C[strlen(str1)][strlen(str2)];
  char* B = (char*)calloc(index+1, sizeof(char));
  int i=strlen(str1), j=strlen(str2);

  while(i>0 && j>0){
    if(str1[i-1] == str2[j-1]){
      B[index-1] = str1[i-1];
      i--;
      j--;
      index--;
    }
    else if(C[i-1][j] > C[i][j-1]){
      i--;
    }
    else{
      j--;
    }
  }
  printf("\nLCS for %s and %s is %s",str1,str2,B);
}
