#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hash{
  struct node* head;
  int count;
};

struct node{
  int key;
  char name[40];
  struct node* next;
};

typedef struct hash HASH;
typedef struct node NODE;

void insert(HASH**,int,int,char*);
NODE* createNode(int,char*);
int search(HASH**,int,int);
void delete(HASH**,int,int);
void printHash(HASH**,int);
int main(){
  int m = 7;
  HASH* hashTable = NULL;
  hashTable = (HASH*)calloc(m,sizeof(HASH));
  int key;
  char name[40];

  if(hashTable == NULL){
    fprintf(stderr,"Memory could not be allocated.\n");
  }
  key = 9;
  strcpy(name,"Hello");
  insert(&hashTable,key,m,name);
  insert(&hashTable,16,m,name);
  insert(&hashTable,23,m,name);
  insert(&hashTable,30,m,name);
  insert(&hashTable,17,m,name);
  //int s = search(&hashTable,31,m);
  printHash(&hashTable,m);
  delete(&hashTable,9,m);
  delete(&hashTable,16,m);
  delete(&hashTable,23,m);
  printf("\n");
  printHash(&hashTable,m);
  return 0;
}

void insert(HASH** hashTable, int key, int m, char* name){
  int hashIndex = key % m;
  NODE* newNode = createNode(key,name);
  if(!(*hashTable)[hashIndex].head){
    (*hashTable)[hashIndex].head = newNode;
    (*hashTable)[hashIndex].count = 1;
  }
  else{
    newNode->next = ((*hashTable)[hashIndex].head);
    (*hashTable)[hashIndex].head = newNode;
    (*hashTable)[hashIndex].count += 1;
  }

}

NODE* createNode(int key, char* name){
  NODE* newNode = (NODE*)malloc(sizeof(NODE));
  newNode->key = key;
  strcpy(newNode->name,name);
  newNode->next = NULL;
  return newNode;
}


int search(HASH** hashTable, int searchkey, int m){
  int hashIndex = searchkey % m;
  if((*hashTable)[hashIndex].head == NULL){
    return -1;
  }
  else{
    if(((*hashTable)[hashIndex].head)->key == searchkey){
      return 1;
    }
    else if(((*hashTable)[hashIndex]).count > 1){
      NODE* current = (*hashTable)[hashIndex].head;
      while(current->next != NULL && current->key!=searchkey){
        current = current->next;
      }
      if(current->key == searchkey){
        return 0;
      }
      else{
        return -1;
      }
    }
  }
}

void delete(HASH** hashTable, int delkey, int m){
  int hashIndex = delkey % m;
  if((*hashTable)[hashIndex].head == NULL){
    return;
  }
  else{
    if(((*hashTable)[hashIndex].head)->key == delkey){
      NODE* temp = (*hashTable)[hashIndex].head;
      (*hashTable)[hashIndex].head = ((*hashTable)[hashIndex].head)->next;
      free(temp);
    }
    else if(((*hashTable)[hashIndex]).count > 1){
      NODE* current = (*hashTable)[hashIndex].head;
      NODE* before = current;
      while(current->next != NULL && current->key!=delkey){
        before = current;
        current = current->next;
      }
      if(current->key == delkey){
        if(current->next == NULL){
          free(current);
          before->next = NULL;
        }
        else{
          before->next = current->next;
          free(current);
        }
      }
    }
  }
}

void printHash(HASH** hashTable, int m){
  int i;
  for(i=0; i<m; i++){
    if((*hashTable)[i].head == NULL){
      printf("[%d]: Empty\n",i);
    }
    else if((*hashTable)[i].count == 1){
      printf("[%d]: %d\n",i,((*hashTable)[i].head)->key);
    }
    else if((*hashTable)[i].count > 1){
      printf("[%d]: ",i);
      NODE* current = (*hashTable)[i].head;
      while(current->next != NULL){
        printf("%d -> ",current->key);
        current = current->next;
      }
      printf("%d\n",current->key);
    }
  }
}
