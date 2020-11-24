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

int main(){
  int m = 97;
  HASH* hashTable = NULL;
  hashTable = (HASH*)calloc(m,sizeof(HASH));
  int key;
  char name[40];

  if(hashTable == NULL){
    fprintf(stderr,"Memory could not be allocated.\n");
  }
  key = 98;
  strcpy(name,"Hello");
  insert(&hashTable,key,m,name);
  int s = search(&hashTable,31,m);
  for(int i=0; i<m; i++){
    if(hashTable[i].head != NULL){
      printf("%d, %d, %s\n",i,(hashTable[i].head)->key, (hashTable[i].head)->name);
    }
  }
  printf("search: %d\n",s);

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
