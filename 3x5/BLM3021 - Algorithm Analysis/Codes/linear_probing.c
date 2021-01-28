#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void insert(int**,int,int);
int search(int**,int,int);

int main(){
  int m = 17;
  int* hashTable = (int*)calloc(m,sizeof(int));
  for(int i=0; i<m; i++){
    hashTable[i] = -2;
  }

  int arr1[15];
  int arr2[20];
  int i;
  for(i=0; i<15; i++){
    printf("Enter %d element of arr1: ",i);
    scanf("%d",&arr1[i]);
    printf("\n");
  }
  for(i=0; i<20; i++){
    printf("Enter %d element of arr1: ",i);
    scanf("%d",&arr2[i]);
    printf("\n");
  }

  for(i=0; i<15; i++){
    insert(&hashTable,arr1[i],m);
  }
  int intersec;
  printf("Intersection: ");
  for(i=0; i<20; i++){
    intersec = search(&hashTable,arr2[i],m);
    if(intersec != -1){
      printf("%d - ",intersec);
    }
  }
  printf("\n");

  return 0;
}

void insert(int** hashTable, int key, int m){
  int i = 0;
  int hashIndex = key % m;
  if((*hashTable)[hashIndex] == -2){
    (*hashTable)[hashIndex] = key;
  }
  else{
    while((*hashTable)[hashIndex] != -2 && i < m){
      i++;
      hashIndex = (key + i) % m;
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
  int hashIndex = key % m;
  int i = 0;
  if((*hashTable)[hashIndex] == -2){
    return -1;
  }
  else{
    if((*hashTable)[hashIndex] != key){
      while((*hashTable)[hashIndex] != -2 && (*hashTable)[hashIndex] != key  && i < m){
        i++;
        hashIndex = (key + i) % m;
      }
      if((*hashTable)[hashIndex] == key){
        return (*hashTable)[hashIndex];
      }
      else{
        return -1;
      }
    }
    else{
      return (*hashTable)[hashIndex];
    }
  }
}
