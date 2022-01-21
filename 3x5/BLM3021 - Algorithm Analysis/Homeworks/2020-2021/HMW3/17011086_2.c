#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hash{
  struct node* head;
};

struct node{
  int key;
  char word[200];
  char correct[200];
  struct node* next;
};

typedef struct hash HASH;
typedef struct node NODE;

void vocab2hash(FILE*, HASH**, int, int); //turns smallDictionary.txt to hash.

NODE* createNode(char*); // creates node with related word member of struct node.

unsigned long long int hornerKey(char*); // calculates key from given string.

unsigned long long int power(int, int); // power function.

void search(HASH**, HASH** ,char*,int,int); // searches given string in vocab hash.

void printHash(HASH**,int); // prints hash.

void saveHash(HASH**,int); // saves hash into 17011086.txt.

void loadHash(HASH**); // loads hash from 17011086.txt if it exists.

void insertionSort(int**,int**,int); // sorts min edit distances while changing index of words.

void minEditDistance(int**,int**, HASH**,char*,int); // computes min edit distance between the input and whole hash.

int min(int,int,int); // finds minimum.

int checkChoice(char**,char*,int); // checks whether selected word is in recommended words.

void saveCorrectedWord(HASH**, char*,char*,int,int); // saves selected corrected word into corrected hash.

int findCorrectedInHash(HASH**,char*,int,int); // finds typo input if it is loaded into corrected hash.

int main(){

  FILE* fp1; // smallDictionary.txt
  FILE* fp2; // 17011086.txt

  /* Does 17011086.txt is necessary?
   * the hmw pdf file not clear about "hash is computed once"
   * the "once" means "once, every time it runs"
   * or
   * "once, from the first run"
   * due to this ambiguity
   * i choose to save and load the vocab hash,
   * from this perspective the hash is calculated "only" once
   */

  int m=499; // the vocab hash table size.
  int mm=493; // other mode variable for double hashing.
  HASH* hashTable = NULL; // our vocab hash table.
  hashTable = (HASH*)calloc(m, sizeof(HASH));

  HASH* hashCorrected = NULL; // hash for already corrected words.
  hashCorrected = (HASH*)calloc(m, sizeof(HASH));


  fp2 = fopen("17011086.txt","r"); // open saved hash.
  if(fp2 == NULL){ // if never saved the hash (first time of the program).
    fp1 = fopen("smallDictionary.txt","r"); // then open the real vocabulary.
    if(fp1 == NULL){
      fprintf(stderr, "Wow, you must do something wrong.");
      exit(EXIT_FAILURE);
    }
    vocab2hash(fp1, &hashTable, m, mm); // load the smallDictionary.txt to vocab hash.
    printf("Hash is created...\n");
    saveHash(&hashTable,m); // save this vocab hash (as i mentioned above).
    printf("Hash is saved into 17011086.txt...\n");
    fclose(fp1);
  }

  else{ // if vocab hash is saved before (2nd or 3rd or ... running).
    loadHash(&hashTable); // load 17011086.txt into vocab hash file.
    printf("Hash is loaded from 17011086.txt...\n\n");
  }

  char sentence[500]; // the user inputs his/her sentence to this variable.
  while(strcmp(sentence,"safak") != 0){ // user just write safak to input to exit.
    printf("---------------------------\n");
    printf("Enter the sentence: ");
    scanf("%[^\n]%*c", sentence); // user enters the sentence
    printf("\n");
    search(&hashTable, &hashCorrected, sentence, m, mm); // and the program calculates everything about this sentence.
    printf("\n");
  }

  return 0;
}


void search(HASH** hashTable, HASH** hashCorrected, char* sentence, int m, int mm){
  /*
   *PARAMETERS:
   *  - HASH** hashTable     :  Our vocabulary hash. Real tokenized words are in this hash.
   *  - HASH** hashCorrected :  Our corrected words. Contains prior knowledge about words, if the typo given before.
   *  - char* sentece        :  The user givves this sentence to correct.
   *  - int m                :  The vocab & corrected hash size.
   *  - int mm               :  Latter mode variable for vocab & corrected hash table
   *
   *TASK:
   *  - Takes an input sentence, tokenizes the sentence, checks if the words not in the vocabulary hash,
   *  - then it decides that tokenized word/s are/is typo. Checks if this typo is presented in prior corrected
   *  - hash table. If it is, then selects the corrected one of this typo (never asking an input). If it is not,
   *  - it calculates the min distances over the whole vocabulary hash. Then recommends corrected ones (1 or 1 and 2)
   *  - user inputs a word from recommended ones, then it loads this new typo into prior corrected hash.
   */

  int i = 0; // iterator
  int k = 0; // iterator
  int hash1; // double hashing
  int hash2; // double hashing
  int hashIndex; // hash index from double hashing
  unsigned long long int key; // key for hornerkey calculation

  int wordcount = 0; // counter for total words in input sentence
  int correct = 0; // counter for total correct words in input sentence
  // if wordcount == correct, then our sentence is completely correct.

  int* index = (int*)calloc(499,sizeof(int)); // this keeps hash indices of min edit distances
  int* cost = (int*)calloc(499,sizeof(int));  // this keeps costs of min edit distance hash indices

  /*example:
   * index    cost
   *  13       1    -> ((*hashTable)[index[0]].head)->word is recommended with 1 (cost[0]) min edit distance
   *  127      2    -> ((*hashTable)[index[1]].head)->word is recommended with 2 (cost[1]) min edit distance
   *  531      1    -> ((*hashTable)[index[2]].head)->word is recommended with 1 (cost[2]) min edit distance
   */

  char true_sentence[500] = ""; // we present our true sentence by concatenating corrected ones with this variable.
  char* recommended[499] = {'\0'}; // we keep all recommended words for checking if selected word is in recommended ones.

  for(i=0; i<499; i++){ // make all elements -1
    index[i] = -1;
    cost[i] = -1;
  }

  int j=0; // iterator

  char choice[100]; // after recommendations, we choose a word for our typo. This variable is for this chosen word.
  char* tokenized;  // for tokenization of our sentence.
  int oneortwo;     // variable for if min edit distances has whether 1.
  int found;        // variable for if we found rhe prior in corrected hash.

  tokenized = strtok(sentence, " "); // first tokenized word.

  while(tokenized != NULL){ // until the end of tokenization...

    i = 0; // double hashing iterator
    j = 0; // cost array's iterator (explained above)
    k = 0; // recommended array's iterator (explained above)

    found = -1; // not found
    key = hornerKey(tokenized); // calculate hornerkey for tokenized word
    wordcount++; // increase total word counter

    hash1 = key % m; // double hash indexing
    hash2 = 1 + (key % mm);  // double hash indexing
    hashIndex = (hash1 + i * hash2) % m;  // double hash indexing

    if((*hashTable)[hashIndex].head == NULL){ // --if the calculated hash index is NULL then the word is typo--

      found = findCorrectedInHash(hashCorrected,tokenized,m,mm); // check whether the typo word is represented in corrected hash

      if(found == -1){ // if not represented then..
        minEditDistance(&index,&cost,hashTable,tokenized,m); //calculate min edit distance over the vocab hash
        insertionSort(&index,&cost,m); // sort the costs

        /*example:
         * remember above example. After sorting, cost and index array will be
         * index    cost
         *  13       1    -> ((*hashTable)[index[0]].head)->word is recommended with 1 (cost[0]) min edit distance
         *  531      1    -> ((*hashTable)[index[1]].head)->word is recommended with 1 (cost[1]) min edit distance
         *  127      2    -> ((*hashTable)[index[2]].head)->word is recommended with 2 (cost[2]) min edit distance
         */

        oneortwo = cost[0]; // after sorting, our first element is 1 or 2.
        // if it is 1, no need to recommend 2s
        // if it is 2, there is only two.

        if(oneortwo != -1){ // if there is at least one recommended word
          printf("[WARNING!]: \"%s\" is not in the dictionary.",tokenized);
          printf(" Did you mean: ");

          while(cost[j] == oneortwo){ // while the 1 or 2
            if(cost[j+1] == oneortwo){ // if next one is not end (this control is just for visuality. Without this the last recommended has "or" word too)
              printf("\"%s\"(%d) or ",((*hashTable)[index[j]].head)->word,cost[j]); // (*hashTable)[index[j]].head)->word is recommended with
                                                                                    // cost of cost[j], remember our above example table.
              recommended[k] = ((*hashTable)[index[j]].head)->word; // add it to recommended string array
              k++;
              j++;
            }
            else{ // same thing with above if. Just more beautiful user interface.
              printf("\"%s\"(%d)?",((*hashTable)[index[j]].head)->word,cost[j]);
              recommended[k] = ((*hashTable)[index[j]].head)->word;
              k++;
              j++;
            }
          }

          printf("\n");
          printf("\nMy choice: ");
          scanf("%[^\n]%*c",choice); // give the choice
          while(checkChoice(recommended,choice,k) == 0){ // if this choice is not in the recommended ones, keep asking choice
            printf("The word %s is not recommended please try again.\n",choice);
            printf("My choice: ");
            scanf("%[^\n]%*c",choice);
          }

          saveCorrectedWord(hashCorrected,tokenized,choice,m,mm); // save this new corrected word into correct hash, this is what i called prior.
          strcat(true_sentence,choice); // concat this new word
          strcat(true_sentence," ");
          printf("\n");
        }

        else{ // if there is no recommended words
          printf("[WARNING!]: \"%s\" neither in the dictionary nor the prior corrections...\n",tokenized);
          strcat(true_sentence,"<UNK>"); // replace with <UNK> token.
          strcat(true_sentence,tokenized);
          strcat(true_sentence,"</UNK>");
          strcat(true_sentence," ");
          printf("\n");
        }
      }

      else{ // if the typo word is found in corrected hash,
        strcat(true_sentence,((*hashCorrected)[found].head)->correct); // not asking.
        strcat(true_sentence," ");
        printf("\n");
      }
    }

    else if(strcmp(((*hashTable)[hashIndex].head)->word, tokenized) == 0){ // word is not typo
      correct++;
      strcat(true_sentence,tokenized);
      strcat(true_sentence," ");
    }

    else{
      while(i<m && (*hashTable)[hashIndex].head != NULL && strcmp(((*hashTable)[hashIndex].head)->word, tokenized) != 0){
        // collision: double hashing.
        i++;
        hashIndex = (hash1 + i*hash2) % m;
      }

      if(i<m && (*hashTable)[hashIndex].head != NULL && strcmp(((*hashTable)[hashIndex].head)->word, tokenized) == 0){
        // word is not typo.
        correct++;
        strcat(true_sentence,tokenized);
        strcat(true_sentence," ");
      }
      else{// word is typo.
        found = findCorrectedInHash(hashCorrected,tokenized,m,mm); // check whether the typo word is represented in corrected hash
        if(found == -1){ // if not represented then..
          minEditDistance(&index,&cost,hashTable,tokenized,m); // calculate min edit distance over the vocab hash.
          insertionSort(&index,&cost,m); // sort the costs
          // abıve, there was an example, we do same things.

          oneortwo = cost[0]; // after sorting our first element is 1 or 2.

          if(oneortwo != -1){ // if there is at least one recommended word
            //from this line we do same things with without collision situation
            printf("[WARNING!]: \"%s\" is not in the dictionary.",tokenized);
            printf(" Did you mean: ");
            oneortwo = cost[0];
            while(cost[j] == oneortwo){
              if(cost[j+1] == oneortwo){
                printf("\"%s\"(%d) or ",((*hashTable)[index[j]].head)->word,cost[j]);
                recommended[k] = ((*hashTable)[index[j]].head)->word;
                k++;
                j++;
              }
              else{
                printf("\"%s\"(%d)?",((*hashTable)[index[j]].head)->word,cost[j]);
                recommended[k] = ((*hashTable)[index[j]].head)->word;
                k++;
                j++;
              }
            }
            printf("\n");
            printf("\nMy choice: ");
            scanf("%[^\n]%*c",choice);
            while(checkChoice(recommended,choice,k) == 0){
              printf("The word %s is not recommended please try again.\n",choice);
              printf("My choice: ");
              scanf("%[^\n]%*c",choice);
            }
            saveCorrectedWord(hashCorrected,tokenized,choice,m,mm);
            strcat(true_sentence,choice);
            strcat(true_sentence," ");
            printf("\n");
          }
          else{
            printf("[WARNING!]: \"%s\" neither in the dictionary nor the prior corrections...\n",tokenized);
            strcat(true_sentence,"<UNK>"); // replace with <UNK> token.
            strcat(true_sentence,tokenized);
            strcat(true_sentence,"</UNK>");
            strcat(true_sentence," ");
            printf("\n");
          }
        }
        else{
          strcat(true_sentence,((*hashCorrected)[found].head)->correct);
          strcat(true_sentence," ");
          printf("\n");
        }
      }
    }

    tokenized = strtok(NULL, " "); // tokenize other words.
  }
  if(correct != 0 && (wordcount == correct)){ // if it wordcount and correct is equal then the sentence is equal.
    printf("That's a correct sentence. No typo.\n");
  }

  printf("The Sentence: %s\n",true_sentence);

}

void vocab2hash(FILE* fp, HASH** hashTable, int m, int mm){
  /*PARAMETERS:
   *  - FILE* fp            :  smallDictionary.txt file
   *  - HASH* hashTable     :  Our vocabulary hash. Real tokenized words are in this hash.
   *  - int m               :  The vocab & corrected hash size.
   *  - int mm              :  Latter mode variable for vocab & corrected hash table
   *
   *TASK:
   *  - inserts words into our vocab hash table hashTable.
   */

  int i = 0; // iterator for collision
  char buffer[200]; // buffer for file's line.
  unsigned long long int key; // key for hornerkey calculation.

  int hash1; // double hashing
  int hash2; // double hashing
  int hashIndex; // double hashing
  NODE* new_node;

  while(fscanf(fp, "%s", buffer) == 1){ // while the end of the file. 
    if(strcmp(buffer," ")){
      i = 0;
      key = hornerKey(buffer); // calculate key
      hash1 = key % m; // double hashing
      hash2 = 1 + (key % mm); // double hashing
      hashIndex = (hash1 + i * hash2) % m; // double hashing
      new_node = createNode(buffer); // create a node with that related word.
      if(!(*hashTable)[hashIndex].head){ // if null - no collision
        (*hashTable)[hashIndex].head = new_node;
      }

      else{ // if not null collision
        while(i<m && (*hashTable)[hashIndex].head != NULL){
          // collision
          i++;
          hashIndex = (hash1 + i*hash2) % m;
        }
        if(i<m){
          // empty.
          (*hashTable)[hashIndex].head = new_node;
        }
        else{
          fprintf(stderr, "Wow, you must do something wrong. Try increase the table size.");
          exit(EXIT_FAILURE);
        }
      }
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

NODE* createNode(char* word){
  /*
   *PARAMETERS:
   *  - char* word: the word
   *
   *TASK:
   *  - just creates a node with related informations.
   */
  NODE* new_node = (NODE*)malloc(sizeof(NODE)); // allocate the node
  strcpy(new_node->word,word); // attach the related information
  new_node->next = NULL; // next to null
  return new_node;
}


unsigned long long int power(int a, int b){
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
  /*PARAMETERS:
   *  - HASH** hashTable: the hash table
   *  - int m: table size
   */
  int i;
  for(i=0; i<m; i++){
    if((*hashTable)[i].head != NULL){
      printf("%d:  %s\n",i,((*hashTable)[i].head)->word);
    }
  }
}

void saveHash(HASH** hashTable, int m){
  /*PARAMETERS
   *  - HASH** hashTable:  the hash table
   *  - int m           :  size of the hash table
   *
   *TASK:
   *  - saves the hash into 17011086.txt
   */
  int i;
  FILE* fp = fopen("17011086.txt", "w");
  if(fp == NULL){
    fprintf(stderr,"File error!");
  }

  for(i=0; i<m; i++){
    if((*hashTable)[i].head != NULL){
      fprintf(fp,"%d %s\n",i,((*hashTable)[i].head)->word);
    }
  }
  fclose(fp);
}

void loadHash(HASH** hashTable){
  /*PARAMETERS:
   *  - HASH** hashTable    :  the hash table
   *
   *TASK:
   *  - loads hash from 17011086.txt
   */
  int i;
  FILE* fp = fopen("17011086.txt","r");
  if(fp == NULL){
    fprintf(stderr,"File error!");
    exit(EXIT_FAILURE);
  }

  char buffer[250];
  char* ptr1;
  char* ptr2;
  int hashIndex;

  while(fgets(buffer, 251, fp)){
    ptr1 = strtok(buffer,"\n");
    ptr2 = strtok(ptr1, " ");
    hashIndex = atoi(ptr2);
    ptr2 = strtok(NULL, " ");
    ((*hashTable)[hashIndex].head) = createNode(ptr2);
  }
  fclose(fp);
}

void minEditDistance(int** index, int** cost, HASH** hashTable, char* word, int m){
  /*PARAMETERS:
   *  - int** index           :  index's of recommended words in vocab hash
   *  - int** cost            :  min edit distane costs of those recommended words
   *  - HASH** hashTable      :  the hash table for vocab
   *  - char* word            :  tokenized word
   *  - int m                 :  size of the hash table
   *
   *TASK:
   *  - calculates min edit distance among the tokenized word and whole vocab hash
   *  - only selects costs of one and 2
   *
   *                  |
   *                  |D[i-1,j]     + 1 (deletion)
   *      D[i,j] = min|D[i,j-1]     + 1 (insertion)
   *                  |D[i-1,j-1]   + 1 if x[i] = y[j], else 0 (substitution)
   *                  |
   *
   */

  int hashIndex; // index
  int i; // iterator for string tokenized
  int j; // iterator for string from hash
  int k; // iterator for memory allocation of distance matrix
  int delete; // deletion cost
  int insert; // insertion xost
  int subs; // substitution cost
  int** D; // the dstance matrix
  int len_word = strlen(word); // length of tokenized word
  int len_target; // length of string from hash
  int recommend_index = 0; // index for, index array and cost array, as we described in search function
  int _min_ = -1;
  int p; // bonus section :)

  /*
   *BONUS:
   *  if minimum of a row is greater than 2
   *  then the distance must be greater than 2
   *  since we are taking the recursive value
   *  from the up or left.
   */

  for(hashIndex = 0; hashIndex<m; hashIndex++){ // from the start of hash to end
    _min_ = -1;
    i=0;
    if((*hashTable)[hashIndex].head != NULL){ // if not empty
      len_target = strlen(((*hashTable)[hashIndex].head)->word); // length of string hash[hashIndex]
      D = (int**)calloc(len_word+1,sizeof(int*)); // allocate rows

      for(k=0; k<len_word+1; k++){
        D[k] = (int*)calloc(len_target+1, sizeof(int)); // allocate columns
      }
      while(i<len_word+1 && _min_<3){
        for(j=0; j<len_target+1; j++){
          if(i==0){
            D[i][j] = j; // initialize columns first elements
          }
          else if(j==0){
            D[i][j] = i; // initialize rows first elements
          }
          else{
            delete = D[i-1][j] + 1; //deletion cost
            insert = D[i][j-1] + 1; //insertion cost
            if(word[i-1] == (((*hashTable)[hashIndex].head)->word)[j-1]){
              subs = 0;
            }
            else{
              subs = 1;
            }
            subs =  D[i-1][j-1] + subs; // substitiution cost
            D[i][j] = min(delete, insert, subs); // choose minimum
          }
        }

        _min_ = D[i][0];
        for(p=0; p<len_target+1; p++){
          if(D[i][p]<_min_){
            _min_ = D[i][p];
          }
        }
        i++;
      }
      if(D[len_word][len_target] != 0){ // if the final cost is lower than 3
        (*index)[recommend_index] = hashIndex; // add hashIndex into index array
        (*cost)[recommend_index] = D[len_word][len_target]; // add cost into cost array
        recommend_index++;
      }
    }
  }
}

int min(int i, int d, int s){
  /*PARAMETERS:
   *  - int i : insertion cost
   *  - int d : deletion cost
   *  - int s : substitution cost
   *
   *TASK:
   *  - returns minimum of this 3 parameters
   *
   */
  if (i < d && i < s){
    return i;
  }
  else if(d < i && d < s){
    return d;
  }
  else{
    return s;
  }
}

void insertionSort(int** index, int** cost, int n){
  /*PARAMETERS:
   *  - int** index  : the index array, explained in search() function
   *  - int** cost   : the cost array, explained in search() function
   *  - int n        : size of those arrays.
   *
   *TASK:
   *  - sorts the cost array, while doing this, swaps index array
   *  - depends on cost array swaps.
   *
   */
  int i=1, key, key2, j;
  while((*cost)[i] != -1 && i<n){
    key = (*cost)[i];
    key2 = (*index)[i];
    j = i-1;
    while(j>=0 && (*cost)[j] > key){
      (*cost)[j+1] = (*cost)[j];
      (*index)[j+1] = (*index)[j];
      j = j-1;
    }
    (*cost)[j+1] = key;
    (*index)[j+1] = key2;
    i++;
  }
}


int checkChoice(char** str, char* choice, int n){
  /*PARAMETERS:
   *  char** str  :  the array of recommended strings
   *  char* choice:  user's input
   *  int n       :  size of array
   *TASK:
   *  if given input is in recommended strings
   */
  int i=0;
  int is_in = 0;
  while(i<n && is_in == 0){
    if(strcmp(str[i],choice) == 0){
      is_in = 1;
    }
    i++;
  }
  return is_in;
}


void saveCorrectedWord(HASH** correctedHash, char* input, char* correct, int m, int mm){
  /*PARAMETERS:
   *  HASH** correctedHash  : prior correct hash
   *  char* input           : tokenized typo word
   *  char* correct         : selected recommended word
   *  int m, mm
   *
   *TASK:
   *  computes key based on tokenized typo then does double hashing to get index,
   *  then save the tokenized word and selected recommended word to that node/index
   */
  int i = 0;
  unsigned long long int key;

  int hash1; //double hashing
  int hash2; //double hashing
  int hashIndex; //double hashing
  NODE* new_node; //double hashing
  i = 0; //double hashing
  key = hornerKey(input); // hornerkey
  hash1 = key % m; // double hashing
  hash2 = 1 + (key % mm); // double hashing
  hashIndex = (hash1 + i * hash2) % m; // double hashing
  new_node = createNode(input); // create node based on typo tokenized word

  if(!(*correctedHash)[hashIndex].head){ // if empty then import
    (*correctedHash)[hashIndex].head = new_node;
    strcpy(((*correctedHash)[hashIndex].head)->correct,correct); // save corrected one
    printf("The corrected version is added to correction hash...\n");
  }
  else{
    while(i<m && (*correctedHash)[hashIndex].head != NULL){
      // collision
      i++;
      hashIndex = (hash1 + i*hash2) % m;
    }
    if(i<m){
      (*correctedHash)[hashIndex].head = new_node;
      strcpy(((*correctedHash)[hashIndex].head)->correct,correct);  // save corrected one
      printf("The corrected version is added to correction hash...\n");
    }
    else{
      fprintf(stderr, "Wow, you must do something wrong. Mayve you should increase the table size.");
      exit(EXIT_FAILURE);
    }
  }
}

int findCorrectedInHash(HASH** correctedHash, char* input, int m, int mm){
  /*PARAMETERS:
   *  HASH** correctedHash  : prior correct hash
   *  char* input           : tokenized typo word
   *  int m,mm
   *
   *TASK:
   *  searches the typo tokenized input word into prior corrected hash
   *  if the word is in this hash, returns its hash index,
   *  else returns -1
   *
   *Returns: hash index of corrected word
   */
  int i = 0;
  unsigned long long int key;

  int hash1;
  int hash2;
  int hashIndex;
  NODE* new_node;
  i = 0;
  key = hornerKey(input);
  hash1 = key % m;
  hash2 = 1 + (key % mm);
  hashIndex = (hash1 + i * hash2) % m;

  if(!(*correctedHash)[hashIndex].head){
    // not in hash
    return -1;
  }
  else if(strcmp(((*correctedHash)[hashIndex].head)->word, input) == 0){
    // is in hash without collision
    printf("Correction of %s is found in correction hash...\n",input);
    return hashIndex;
  }
  else{
    while(i<m && (*correctedHash)[hashIndex].head != NULL && strcmp(((*correctedHash)[hashIndex].head)->word, input) != 0){
      //collision
      i++;
      hashIndex = (hash1 + i*hash2) % m;
    }
    if(i<m && (*correctedHash)[hashIndex].head != NULL && strcmp(((*correctedHash)[hashIndex].head)->word, input) == 0){
      // is in hash with collision
      printf("Correction of %s is found in correction hash...\n",input);
      return hashIndex;
    }
    else{
      return -1;
    }
  }
}
