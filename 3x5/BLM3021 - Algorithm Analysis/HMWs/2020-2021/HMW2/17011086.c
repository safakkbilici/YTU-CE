#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct hash{
  struct node* head;
  int count;
  int load_factor;
};

struct node{
  int key;
  char word_or_doc[100];
  struct node* next;
};

typedef struct hash HASH;
typedef struct node NODE;

void insertWord(HASH**,unsigned long long int,char*,char*,int,int); // function for inserting words into hash
void insertDoc(FILE*,HASH**,char*,int,int); // function for processes text inside a doc and iterates this doc with insertWord
void search(HASH**,char*,int,int); // search word inside the hash
NODE* createNode(char*); // creates single linked list node
unsigned long long int hornerKey(char*); // calculates key value from a given word with horner's formula
unsigned long long power(int,int); // calculates power
void printHash(HASH**,int); // prints hash
void saveHash(HASH**,int); // saves hash into hash.txt
void loadHash(FILE*, HASH**,int); // loads hash from hash.txt

int loaded = 0; // counter for "how many elements in this hash"
float load_factor = 0; // counter for 0-1 normalized load factor

int main(){

  int i;
  int m=997; //table size
  int mm=996; // hash2 function's mode
  char filename[20];
  FILE* fp;
  char word[200]; // variable for word searching
  int load=0; //full load flag

  HASH* hashTable = NULL;
  hashTable = (HASH*)calloc(m,sizeof(HASH)); // allocating hash table

  fp = fopen("17011086.txt","r");
  if(fp != NULL){
    loadHash(fp,&hashTable,m); // if there is hash.txt then load it
    if(load_factor == 1){
      load = 1;
    }
    printf("The hash is loaded from 17011086.txt...\n");
    fclose(fp);
  }
  printf("-------------------------------------------------------------------------------------\n");
  printf("--- You can enter your input documents in infinite loop\n");
  printf("--- Quit: 0, Add New Document: 1, Search For A Word: 2, Print Current Load Factor: 3\n");
  printf("-------------------------------------------------------------------------------------\n\n");
  int select=-1; // choice select: 0->quit, 1->load document, 2->search word, 3->print current load factor
  while(select !=0){
    printf("\nYour choice [0/1/2/3]: ");
    scanf("%d", &select);
    if(select == 0){
      printf("Goodbye...\n");
    }
    else if(select == 1){
      printf("Enter the document which you want to add it's word into the hash: ");
      scanf(" %s",filename);
      fp = fopen(filename,"r");
      if(fp==NULL){
        fprintf(stderr,"File Error!");
        exit(EXIT_FAILURE);
      }
      else{
        insertDoc(fp,&hashTable,filename,m,mm); // insert doc
        if(load_factor >=0.8 ){
          printf("\n[WARNING!] Load Factor: %f\n",load_factor); // load factor warning 
        }
        if(load==0){
          //printHash(&hashTable,m);
          saveHash(&hashTable,m); // save hash in each given doc
        }
      }
    }
    else if(select == 2){
      printf("Enter the word that you want to search: ");
      scanf(" %s",word);
      search(&hashTable,word,m,mm); // search for a key
    }
    else if(select == 3){
      printf("Current load factor is %f.\n",load_factor);
    }
    else{
      fprintf(stderr,"Invalid value!\n");
    }
  }
  fclose(fp);

  return 0;
}


void insertWord(HASH** hashTable, unsigned long long int key, char* word, char* doc, int m, int mm){
  /*
   *PARAMETERS:
   *  - HASH** hashTable: the hashTable
   *  - unsigned long long int key: key calculated by horner's function
   *  - char* word: word for inserting into hash
   *  - char* doc: the document of above word
   *  - int m: table size
   *  - int mm: mode value for hash2 function
   *
   *TASK:
   *  - takes a doc name and a word. Inserts the word and the doc if word is not in the hashtable
   *  - if word is in the hashtable, then just inserts the doc's name to related linked list
   *  - if the doc is given before, does nothing.
   */

  int i=0;
  // double hashing:
  int hash1 = key % m;
  int hash2 = 1 + (key % mm);
  int hashIndex = (hash1 + i * hash2) % m;
  NODE* new_node = createNode(word); // create node with word attribute

  if(!(*hashTable)[hashIndex].head){ // if there is no index with this key, means word is not in the hash table
    (*hashTable)[hashIndex].head = new_node; // at any index, linked list's head refers to the word.
    (*hashTable)[hashIndex].count = 1;
    ((*hashTable)[hashIndex].head)->next = createNode(doc); // nexts of the word refers to the related documents
    loaded++; // increase the number of elements in hash table
    load_factor =  (float)loaded/m; // compute the load factor with dividing by m
  }

  else if(strcmp(((*hashTable)[hashIndex].head->word_or_doc),word) == 0){ // if the word in the hash table just add new related doc
    NODE* current = (*hashTable)[hashIndex].head; // for iterating the linked list
    current = current->next;
    while(current->next != NULL && strcmp(current->word_or_doc,doc) != 0){ // go the the last element of linked list for inserting the doc name
      current = current->next;
    }
    if(current->next == NULL && strcmp(current->word_or_doc,doc) != 0){ // if the next is null and the current's doc name is not same with our doc name
      current->next = createNode(doc); // then add this document, if it is same with our document name, then do nothing (no else branch)
      ((*hashTable)[hashIndex].count)++;
    }
  }

  else if((((*hashTable)[hashIndex].head)) && strcmp(((*hashTable)[hashIndex].head->word_or_doc),word) != 0){
    // if the word is not in the hash table, nevertheless the index of this word is not null (collision)
    while((*hashTable)[hashIndex].head != NULL && i<m && strcmp(((*hashTable)[hashIndex].head->word_or_doc),word) != 0){
      i++; // just go to through the new place for our word
      hashIndex = (hash1 + i*hash2) % m;
    }
    if((*hashTable)[hashIndex].head != NULL && strcmp(((*hashTable)[hashIndex].head->word_or_doc),word) == 0){ // if there is this word but not the same document
      NODE* current = (*hashTable)[hashIndex].head; // for iterating the linked list
      current = current->next;
      while(current->next != NULL && strcmp(current->word_or_doc,doc) != 0){ // go the the last element of linked list for inserting the doc name
        current = current->next;
      }
      if(current->next == NULL && strcmp(current->word_or_doc,doc) != 0){ // if the next is null and the current's doc name is not same with our doc name
        current->next = createNode(doc); // then add this document, if it is same with our document name, then do nothing (no else branch)
        ((*hashTable)[hashIndex].count)++;
      }
    }
    else if(i<m){ // this means our hashtable is not full
      if(i>10){
        printf("%s\n",word);
      }
      (*hashTable)[hashIndex].head = new_node; // add the word into hash table
      (*hashTable)[hashIndex].count = 1;
      ((*hashTable)[hashIndex].head)->next = createNode(doc); // add the related doc into hash table
      loaded++; // calculate load factor again
      load_factor = (float) loaded/m;
    }
    else{
      fprintf(stderr,"[WARNING!] Load factor is 1. The word cannot be inserted!: %s\n",word); // warning for load factor is 1
    }
  }
}



void insertDoc(FILE* fp, HASH** hashTable, char* doc, int m, int mm){
  /*
   *PARAMETERS:
   *  - FILE* fp: the document for words
   *  - HASH** hashTable: the hash table
   *  - char* doc: the name of the document
   *  - int m: table size
   *  - int mm: mode value for hash2 function
   *
   *TASK:
   *  - takes the document file pointer and tokenizes the words by itering through words. While iterating through the words
   *  - makes uppercase letters lowercase, deletes punctuation marks. Each iteration, calls insertWord and insert the current
   *  - iterated word into hash table.
   */

  int i;
  char buffer[200];// buffer for reading words in our doc
  unsigned long long int key; // what horner method calculates. Too big -> unsigned long long int

  while(fscanf(fp,"%s",buffer) == 1){ // while end of the document
    for(i=0; i<strlen(buffer); i++){
      if(buffer[i]>=65 && buffer[i]<=90){
        buffer[i]=buffer[i]+32; // if uppercase letter, then do it lowercase
      }
      else if(!(buffer[i]>=97 && buffer[i]<=122)){
        buffer[i] = ' '; // if punctuation then do it a blank
      }
    }
    if(strcmp(buffer," ")){ // if not a blank (only word with lowercase letters)
      key = hornerKey(buffer); // calculate the word's key via horner's method
      insertWord(hashTable,key,buffer,doc,m,mm); // then insert this key with double hashing
    }
  }
  if(load_factor != 1){
    printf("The document %s and its words are loaded into hash...\n",doc);
  }
}

NODE* createNode(char* word_or_doc){
  /*
   *PARAMETERS:
   *  - char* word_or_doc: the word or word's document
   *
   *TASK:
   *  - just creates a node with related informations.
   */
  NODE* new_node = (NODE*)malloc(sizeof(NODE)); // allocate the node
  strcpy(new_node->word_or_doc,word_or_doc); // attach the related information
  new_node->next = NULL; // next to null
  return new_node;
}

void search(HASH** hashTable, char* word, int m, int mm){
  /*
   *PARAMETERS:
   *  - HASH** hashTable: our hash table
   *  - char* word: word for search
   *  - int m: table size
   *  - int mm: double hash mode
   *
   *TASK:
   *  - given a word, calculates its key via horner's method. Then calculates
   *  - its hash index with double hashing function. If hash index not null
   *  - and equal to the parameter word, then we found. If hash index is null
   *  - then the word is not in the hash table. If hash index not null but
   *  - not equal to the parameter word, then it search by double hashing by
   *  - increasing i parameter.
   *
   */
  int i;
  unsigned long long int key; // key from horner's method
  int hash1; // first hash function
  int hash2; // second hash function
  int hashIndex; // full hashindex
  NODE* current;  // variable for iterating the head

  for(i=0; i<strlen(word); i++){
    if(word[i]>=65 && word[i]<=90){
      word[i]=word[i]+32; // if the word includes uppercase letters then make them lowercase
    }
  }
  key = hornerKey(word); // calculate the horner key of the word for search
  i=0;
  hash1 = key % m; // first hash function
  hash2 = 1 + (key % mm); // second hash function
  hashIndex = (hash1 + i * hash2) % m; // final hash index
  if((*hashTable)[hashIndex].head == NULL){
    printf("There is no word %s in hash.\n",word); // if hash index is null then the word is not in the hash table.
  }
  else if(strcmp(((*hashTable)[hashIndex].head)->word_or_doc,word) == 0){
    current = (*hashTable)[hashIndex].head;// If hash index not null and equal to the parameter word, then we found.
    current = current->next;
    printf("The word %s in the documents:",word);
    while(current->next != NULL){ // while loop for printing all documents that word is in
      printf(" %s,",current->word_or_doc); // nothing differs from printing simple linked list
      current = current->next;
    }
    printf(" %s\n",current->word_or_doc);
    printf("Found in 0 step.\n");
  }
  else{
    //If hash index not null but
    //not equal to the parameter word, then it search by double hashing by
    //increasing i parameter.
    i=0;
    while(i<m && (*hashTable)[hashIndex].head != NULL && strcmp(((*hashTable)[hashIndex].head)->word_or_doc,word) != 0){
      i++; // increase i while if we find it
      hashIndex = (hash1 + i*hash2) % m;
    }
    if((*hashTable)[hashIndex].head != NULL && strcmp(((*hashTable)[hashIndex].head)->word_or_doc,word) == 0){ // if we find it, then print the documents again
      current = (*hashTable)[hashIndex].head; // same as above
      current = current->next;
      printf("The word %s in the documents:",word);
      while(current->next != NULL){
        printf(" %s,",current->word_or_doc);
        current = current->next;
      }
      printf(" %s\n",current->word_or_doc);
      printf("Found in %d steps.\n",i);
    }
    else{
      printf("There is no word %s in hash.\n",word);
    }
  }
}


unsigned long long int hornerKey(char* string){
  /*
   *PARAMETERS:
   *  - char* string: just a string for calculate the horners key
   *
   *TASK:
   *  - calculates horner's key by given string (word)
   */
  int R=31; // horner's hyperparameter
  int L = strlen(string); // string's length
  unsigned long long int key = 0;
  int i;
  for(i=0; i<L; i++){
    key = key + power(R,L-i-1) * (string[i] - 'a' + 1); // method for horner's function
  }
  return key;
}

unsigned long long power(int a, int b){
  /*
   *PARAMETERS:
   *  - int a: bottom number
   *  - top number
   *TASK:
   *  - calculates a^b recursively.
   */
  if(b==0){ // if b 0, it is our initial state
    return 1;
  }
  else if(b%2==0){ // if b is even, then everything is easy
    return power(a,b/2) * power(a,b/2);
  }
  else{ // if not even:
    return a * power(a,b/2) * power(a,b/2);
  }
}

void printHash(HASH** hashTable, int m){
  int i;
  NODE* current;
  for(i=0; i<m; i++){
    if((*hashTable)[i].head != NULL){
      printf("%d: %s (",i,((*hashTable)[i].head)->word_or_doc);
      //current = (*hashTable)[i].head;
      //current = current->next;
      /*
      while(current->next != NULL) {
        printf("%s, ",current->word_or_doc);
        current = current->next;
      }
      if(current != NULL){
        printf("%s)",current->word_or_doc);
        }*/
      printf("\n");
    }
  }
}

void saveHash(HASH** hashTable, int m){
  /*
   *PARAMETERS:
   *  - HASH** hashTable: our hash table
   *  - int m: table size
   *
   *TASK:
   *  - saves hash into hash.txt
   */
  FILE* fp = fopen("17011086.txt","w"); // open the hash.txt
  if(fp==NULL){
    fprintf(stderr,"File Error!\n");
    exit(EXIT_FAILURE);
  }
  int i;
  NODE* current;  // variable for iterating the head
  fprintf(fp,"%f\n",load_factor); // first row of hash.txt is load factor

  for(i=0; i<m; i++){ // while the end of the hash table
    if((*hashTable)[i].head != NULL){ // if the hashindex not null then save it to the hash.txt
      fprintf(fp,"%d",i); // row's first column is the hashindex of word
      fprintf(fp," %s",((*hashTable)[i].head)->word_or_doc); // row's second column is the word
      current = (*hashTable)[i].head; // other columns are documents of this word
      if(((*hashTable)[i].head)->next != NULL){
        current = current->next;
        while(current->next != NULL) { // while the end of the documents save all documents via iterating the current = head

          fprintf(fp," %s",current->word_or_doc);
          current = current->next;
        }
        fprintf(fp," %s\n",current->word_or_doc);
      }
    }
  }
  fclose(fp);
  printf("The hash is saved into 17011086.txt...\n");
}

void loadHash(FILE* fp, HASH** hashTable, int m){
  /*
  *PARAMETERS:
  *  - FILE* fp: hash.txt
  *  - HASH** hashTable: our hash table
  *  - int m: length of hash table
  *
  *TASK:
  *  - loades hash into our hash table.
  */
  char buffer[200]; // buffer for reading hash.txt
  int hashIndex; // hash index
  NODE* current; // variable for iterating the head
  NODE* new_node; // new node variable
  int i;
  char* ptr1; // variable for tokenizing new line character
  char* ptr2; // variable for tokenizing space character
  int line = 0;
  while(fgets(buffer,201,fp)){ // while the end of the hash.txt
    if(line == 0){ // if the first line
      ptr1 = strtok(buffer,"\n"); // then tokenize the new line
      load_factor = atof(ptr1); // tokenized is the load_factor, first row of the hash.txt -> make it float via atof
      loaded = load_factor * m;
      line++;
    }
    else{ // other ones are words and documents
      ptr1 = strtok(buffer,"\n"); // tokenize the new line character
      ptr2 = strtok(ptr1," "); // first tokenized is the hash index of word
      hashIndex = atoi(ptr2); // make it integer via atoi
      ptr2 = strtok(NULL," "); // second tokenized is the word of related hash index

      new_node = createNode(ptr2); // make a node for this word (remember it, the place of words is head, documents is head's nexts)

      (*hashTable)[hashIndex].head = new_node; // word is ready
      (*hashTable)[hashIndex].count = 1;
      current = ((*hashTable)[hashIndex].head);
      ptr2 = strtok(NULL," "); // other tokenized ones are related documents

      while(ptr2 != NULL){ // while there is no document in tokenized ptr2
        //printf("%s \n",ptr2);
        while(current->next != NULL){
          current = current->next;
        }
        current->next = createNode(ptr2); // create a node with related document and assign it
        ptr2 = strtok(NULL," ");
      }
    }
  }
}
