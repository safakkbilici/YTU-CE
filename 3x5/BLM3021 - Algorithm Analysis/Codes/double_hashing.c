#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void insert(int**,int,int);
int search(int**,int,int);

int main(){
  int m = 7;
  int key = 9;
  int* hashTable = (int*)calloc(m,sizeof(int));
  for(int i=0; i<m; i++){
    hashTable[i] = -2;
  }
  insert(&hashTable,key,m);
  insert(&hashTable,16,m);
  insert(&hashTable,23,m);
  for(int i=0; i<m; i++){
    if(hashTable[i] != -2){
      printf("%d: %d\n",i,hashTable[i]);
    }
  }

  int s = search(&hashTable,9,m);
  printf("%d\n",s);

  return 0;
}

void insert(int** hashTable, int key, int m){
  int i = 0;
  int h1 = key % m;
  int h2 = 1 + (key % 4);
  int hashIndex = (h1 + i * h2) % m;
  if((*hashTable)[hashIndex] == -2){
    (*hashTable)[hashIndex] = key;
  }
  else{
    while((*hashTable)[hashIndex] != -2 && i < m){
      i++;
      hashIndex = (h1 + i * h2) % m;
    }
    if(i < m){
      (*hashTable)[hashIndex] = key;
    }
    else{
      printf("Table is almost full! Cannot inserted. \n");
    }
  }
}

int search(int** hashTable, int key, int m){
  int i = 0;
  int h1 = key % m;
  int h2 = 1 + (key % 4);
  int hashIndex = (h1 + i * h2) % m;
  if((*hashTable)[hashIndex] == -2){
    return -1;
  }
  else{
    if((*hashTable)[hashIndex] != key){
      while((*hashTable)[hashIndex] != -2 && (*hashTable)[hashIndex] != key  && i < m){
        i++;
        hashIndex = (h1 + i * h2) % m;
      }
      if((*hashTable)[hashIndex] == key){
        return 0;
      }
      else{
        return -1;
      }
    }
    else{
      return 1;
    }
  }
}
