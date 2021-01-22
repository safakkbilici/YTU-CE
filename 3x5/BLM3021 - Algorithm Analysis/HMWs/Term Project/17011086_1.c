/*
 *Compiled by gcc 5.4.0
 * - gcc 17011086.c -o 17011086 -lm
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX_BOOK_NAME_LEN 20
#define MAX_BUFFER_SIZE 1000

void readCSV(FILE*, char**, int**, int**, int, int, int); // reads given .csv file, loads values into book string array, train matrix, test matrix
void printData(char**,int**,int**,int,int,int); // prints data (not neccesary)
float* sim(int,int**,int**,int,int); // calculates similarity between test i and train
float** getK(float**,int,int); // selects maximum k element of an array
float** pred(int,int**,int**,int,float**,int,int); // predicts rates for test user i on non-read books
int maxRate(float**,int); // gives max rate

int main(){

  int i, j; // iterators
  char filename[100]; // filename input
  FILE* csv; // csv file
  int n_train; // train set length (20)
  int n_test; // test set length (5)
  int n_books; // number of books (8)
  char** books; // book string array
  int** train; // train matrix
  int** test; // test matrix
  float* similars; // for a test user, keeps similarity values on whole train dataset
  int k; // neighbor value
  float** preda; // predict book rates matrix
  float** k_similars; // k similars matrix
  int max_rate; // max predicted book rate
  int select; // whole test set or one specific user?
  int user; // if one specific user, which one?
  char str[12]; // variable for sprintf (just for better UI)
  int sum_book=0; // holds a value for test user i, number of non-read books


  printf("Enter the name of csv file (e.g., xxx.csv): ");
  scanf("%s",filename);
  csv = fopen(filename, "r"); // open csv
  if(csv == NULL){ // if there is not file
    fprintf(stderr,"File %s cannot opened!",filename);
    exit(EXIT_FAILURE);
  }

  printf("Enter the number of train data sample: ");
  scanf("%d",&n_train);

  printf("Enter the number of test data sample: ");
  scanf("%d",&n_test);

  printf("Enter the number of unique book: ");
  scanf("%d",&n_books);

  printf("Enter the number k: ");
  scanf("%d", &k);

  printf("Show all test user (press 0), show specific user (press 1): ");
  scanf("%d",&select);

  printf("\n");



  books = (char**)calloc(n_books, sizeof(char*)); // allocation of book string array
  for(i=0; i<n_books; i++){
    books[i] = (char*)calloc(MAX_BOOK_NAME_LEN, sizeof(char));
  }

  train = (int**)calloc(n_train, sizeof(int*)); // allocation of train set matrix
  for(i=0; i<n_train; i++){
    train[i] = (int*)calloc(n_books, sizeof(int));
  }

  test = (int**)calloc(n_test, sizeof(int*)); // allocation of test set matrix
  for(i=0; i<n_test; i++){
    test[i] = (int*)calloc(n_books, sizeof(int));
  }

  k_similars = (float**)calloc(2, sizeof(float*)); // allocation of k_similars matrix
  for(i=0; i<2; i++){
    k_similars[i] = (float*)calloc(k, sizeof(float));
  }

  readCSV(csv, books, train, test, n_train, n_test, n_books); // read csv


  if(select == 0){
    for(i=0; i<n_test; i++){ // in whole test set
      similars = sim(i,train,test,n_books,n_train); // get similarity matrix between test user i and whole train set
      k_similars = getK(&similars, n_train, k); // select k of them

      sum_book=0;
      for(j=0; j<n_books; j++){ // calculate how many non-read books on test user i
        if(test[i][j] == 0){
          sum_book++;
        }
      }
      preda = (float**)calloc(2, sizeof(float*)); // allocate a matrix with that non-read book size
      for(j=0; j<2; j++){
        preda[j] = (float*)calloc(sum_book, sizeof(float));
      }

      preda = pred(i,train,test,n_books,k_similars,k,sum_book); // get those non-read book predicted ratings
      max_rate = maxRate(preda, sum_book); // select the index of maximum rate to recommend

      // user interface section. no need to explain. just some printfs
      sprintf(str,"%d",i);
      printf("##############################################\n\n");
      printf("The user NU%s \t \n",str);
      printf("-----------------------------------------\n");
      printf("|  Most similar readers  |  Similarity  |\n");
      printf("-----------------------------------------\n");
      for(j=0; j<k; j++){
        sprintf(str,"%d",(int)k_similars[1][j]);
        printf("|\t  U%-14.14s|  %-10.10f| \n",str,k_similars[0][j]);
        printf("-----------------------------------------\n");
      }
      printf("|      ***Non-read book rates***        |\n");
      printf("-----------------------------------------\n");
      for(j=0; j<sum_book; j++){
        printf("|%-17.17s ~~~ %-16f |\n", books[(int)preda[1][j]], preda[0][j]);
      }
      printf("-----------------------------------------\n");
      printf("|We recommend you to read...            |\n");
      printf("|%-20s                   |\n",books[max_rate]);
      printf("-----------------------------------------\n");
      printf("\n");
    }
  }

  else if(select == 1){ // if a specific user
    do{
      printf("Enter test user's id: ");
      scanf("%d", &user);
      if(user>=n_test){
        printf("Try again, the given id is bigger than size of the test set.\n");
      }
    }while(user>=n_test);

    similars = sim(user,train,test,n_books,n_train); // get similarity matrix between THE test user and whole train set
    k_similars = getK(&similars, n_train, k); // select k of them

    sum_book=0;
    for(j=0; j<n_books; j++){
      if(test[i][j] == 0){ // calculate how many non-read books on the test user
        sum_book++;
      }
    }
    preda = (float**)calloc(2, sizeof(float*));  // allocate a matrix with that non-read book size
    for(j=0; j<2; j++){
      preda[j] = (float*)calloc(sum_book, sizeof(float));
    }

    preda = pred(user,train,test,n_books,k_similars,k,sum_book); // get those non-read book predicted ratings
    max_rate = maxRate(preda, sum_book); // select the index of maximum rate to recommend

    // user interface section. no need to explain. just some printfs
    sprintf(str,"%d",user);
    printf("##############################################\n\n");
    printf("The user NU%s \t \n",str);
    printf("-----------------------------------------\n");
    printf("|  Most similar readers  |  Similarity  |\n");
    printf("-----------------------------------------\n");
    for(j=0; j<k; j++){
      sprintf(str,"%d",(int)k_similars[1][j]);
      printf("|\t  U%-14.14s|  %-10.10f| \n",str,k_similars[0][j]);
      printf("-----------------------------------------\n");
    }
    printf("|      ***Non-read book rates***        |\n");
    printf("-----------------------------------------\n");
    for(j=0; j<sum_book; j++){
      printf("|%-17.17s ~~~ %-16f |\n", books[(int)preda[1][j]], preda[0][j]);
    }
    printf("-----------------------------------------\n");
    printf("|We recommend you to read...            |\n");
    printf("|%-20s                   |\n",books[max_rate]);
    printf("-----------------------------------------\n");
    printf("\n");
  }

  return 0;
}

float* sim(int a, int** train, int** test, int n_books, int n_train){
  /*
   *PARAMETERS:
   *  - int a           :  index of test user
   *  - int** train     :  train matrix
   *  - int** test      :  test matrix
   *  - int n_books     :  number of books
   *  - int n_train     :  number of train set sample
   *
   *TASK:
   *  - After the user id is given, this function calculates for each user in the train.
   *  - In this way, a simpler operation was made by getting rid of 2 for nested in main ().
   *  - The function is computed for an instance of it traveling on the train with the loop, and a train-sized float array is returned.
   *  - This array keeps the same as the user on the train of test user with a index.
   *
   *RETURNS:
   *  - similarity array with size of (1 x n_train)
   *
   */

  float sum_numerator = 0; // sum term on numerator
  float sum_denominator_1 = 0; // first sum term on denominator
  float sum_denominator_2 = 0; // second sum term on denominator
  float ra = 0; // mean of a
  float rb = 0; // mean of b
  float* similars = (float*)calloc(n_train, sizeof(float)); // we return this
  int i=0,j=0,m=0; // iterators and indices
  int book=0; // for calculating how many books are read by user

  while(j<n_books){
    if(test[a][j] != 0){ // if the book is read
      ra += test[a][j]; // add to mean term
      book++; // increase read book number
    }
    j++;
  }
  ra = ra/book; // calculate the mean of this test user
  book = 0;
  j = 0;

  while(i<n_train){ // in whole train set
    j=0;
    book = 0;
    while(j<n_books){
      if(train[i][j] != 0){ // calculate the mean of train sample i like above way
        rb += train[i][j];
        book++;
      }
      j++;
    }
    rb = rb/book; // calculate the mean of train sample i
    j = 0;
    while(j<n_books){
      if(train[i][j] !=0 && test[a][j]!=0){ // if those book are read, then calculate
        sum_numerator += (train[i][j] - rb) * (test[a][j] - ra); // numerator
        sum_denominator_1 += (train[i][j] - rb)*(train[i][j] - rb); // denominator 1 (raised by 2)
        sum_denominator_2 += (test[a][j] - ra)*(test[a][j] - ra); // denominator 2 (raised by 2)
      }
      j++;
    }
    j=0;
    similars[m] = sum_numerator / (sqrt(sum_denominator_1) * sqrt(sum_denominator_2)); // calculate the similarity value
                                                                                       // on train index i and test user a
    m++;
    i++;
    sum_numerator = 0;
    sum_denominator_1 = 0;
    sum_denominator_2 = 0;
    rb = 0;
  }
  return similars;
}

float** pred(int a, int** train, int** test, int n_books, float** k_similars, int k, int size_pred){
  /*
   *PARAMETERS:
   *  - int a              :  index of test user
   *  - int** train        :  train matrix
   *  - int** test         :  test matrix
   *  - int n_books        :  number of books
   *  - float** k_similars :  selected k similars
   *  - int k              :  value of neighbors
   *  - int size_pred      :  "how many books test set did not read?" (for allocation matrix for memory efficiency)
   *
   *TASK:
   *  - takes special value to unread p book. It does the calculations by hovering over the
   *  - train set ids in the k \ _similars matrix, using each one's rating on the p book and their average without the overall zero.
   *  - Returns a matrix of "2 x unread books" (given as arguments). The first line holds the predict rating for the books,
   *  - while the second line holds the book for which.
   *
   *RETURNS:
   *  - Returns a matrix of "2 x unread books" (given as arguments). The first line holds the predict rating for the books,
   *  - while the second line holds the book for which.
   *
   */

  int i,j,m,l=0; // iterators and indices
  float rb=0, rbp; // mean of train and train rate on p
  float ra=0; // mean of test
  float sum_numerator=0; // sum term in numerator
  float sum_denominator=0; // sum term in denominator
  int nbook=0, book=0; // calculating read books number on train sample j
  float preda; // value of pred(a,p)

  float** book_recommend = (float**)calloc(2, sizeof(float*)); // value-id matrix of pred(a,p) (described in above and the report)
  for(i=0; i<2; i++){
    book_recommend[i] = (float*)calloc(size_pred, sizeof(float));
  }
  j=0;
  while(j<n_books){
    if(test[a][j] != 0){  // if the book is read
      ra += test[a][j]; // add to mean term
      book++;  // increase read book number
    }
    j++;
  }
  ra = ra/book; // the mean on test sample a

  for(i=0; i<n_books; i++){ // iterating through all books
    if(test[a][i] == 0){ // for the non-read book

      sum_numerator = 0;
      sum_denominator = 0;

      for(j=0; j<k; j++){ // iterating through train samples
        rb = 0;
        nbook = 0;
        for(m=0; m<n_books; m++){ // calculate mean of train j
          rb += train[(int)k_similars[1][j]][m]; // jth train's mean
          if(train[(int)k_similars[1][j]][m] != 0){
            nbook++; // "not including zeros"
          }
        }

        rb = rb / nbook; // jth train's mean
        rbp = train[(int)k_similars[1][j]][i]; // jth train's rate on book i
        sum_numerator +=k_similars[0][j] * (rbp - rb); // the value of numerator
        sum_denominator += k_similars[0][j]; // the value of denominator
      }
      preda = ra + sum_numerator / sum_denominator; // after all, the predicted rate between test user a and book i
      book_recommend[0][l] = preda; // assing the value
      book_recommend[1][l] = i; // which book? index
      l++;
    }
  }

  return book_recommend;

}

void readCSV(FILE* fp, char** books, int** train, int** test, int n_train, int n_test, int n_books){
  /*
   *PARAMETERS:
   *  - FILE* fp           :  the csv file
   *  - char** books       :  book string array
   *  - int** train        :  train matrix
   *  - int** test         :  test matrix
   *  - int n_train        :  number of train samples
   *  - int n_test         :  number of test samples
   *  - int n_books        :  numner of books
   *
   *TASK:
   *  - Each line is tokenized with new line (\n), then tokenized with comma (,).
   *  - If I am in the first line, if the flag (at_book_row variable) is zero, there is no information about the train or test.
   *  - Book names are put into the book string array given as arguments.
   *  - Then, if the line count we passed is less than the number of readers in the train set,
   *  - the tokenized values ​​are thrown into the train matrix given as an argument.
   *  - If the tokenized value is a space ( ), it is considered zero.
   *  - Since there is 1 space between the train and test in the given CSV file,
   *  - the remaining values ​​after that space are placed in the test set in the same tokenization logic.
   *
   */

  char buffer[MAX_BUFFER_SIZE]; // buffer for reading files
  char* ptr1; // new line tokenization
  char* ptr2; // comma tokenization
  int at_book_row = 0; // flag for file pointer is at first row
  int book_index = 0; // indexing for book
  int train_index = 0; // indexing for train samples
  int test_index = 0; // indexing for test samples
  int count = -1; // file line counter (first line does not contain information about samples, just books)
  int ato; // idk why but atoi is broken, if i assign atoi value directly the matrix, it assigns zero :/

  while(fgets(buffer,MAX_BUFFER_SIZE - 1, fp)){
    ptr1 = strtok(buffer, "\n"); //tokenize new lines
    ptr2 = strtok(ptr1, ","); // tokenize commas
    ptr2 = strtok(NULL,","); // tokenize comma for get rid of indices
    while(ptr2 != NULL){
      if(at_book_row == 0){ // if the first line
        if(strcmp(ptr2, " ") != 0){ // and the index of first line is just space
          strcpy(books[book_index], ptr2); // get the book names
          book_index++; // increase the book_index for indexing operations
        }
      }
      else{
        if(count < n_train){ // if the given row is in train
          if(strcmp(ptr2, " ") != 0){ // if not space
            ato = atoi(ptr2);
            train[count][train_index] = ato;
            train_index++;
          }
          else{ // if space it is zero
            train[count][train_index] = 0;
            train_index++;
          }
        }
        /*
         * the first question that will come to mind is that
         * you skip a line by saying train is count<n_train
         * and test is count>n_train.
         * the reason why I do this is given input file's format.
         * train and test samples are seperated with a line that contains just commas.
         *
         */
        else if(count > n_train){
          if(strcmp(ptr2, " ") != 0){ // if not space
            ato = atoi(ptr2);
            test[count - n_train - 1][test_index] = ato;
            test_index++;
          }
          else{ // if space it is zero
            test[count - n_train - 1][test_index] = 0;
            test_index++;
          }
        }
      }
      ptr2 = strtok(NULL,",");
    }
    count++;
    train_index = 0;
    test_index = 0;
    at_book_row++;
  }
}

void printData(char** books, int** train, int** test, int n_train, int n_test, int n_books){
  /*
   *
   *  This function is just for debugging by hand. No need to explain.
   *
   *
   */
  int i,j;
  for(i=0; i<n_books; i++){
    printf("%s, ",books[i]);
  }
  printf("\n");
  for(i=0; i<n_train; i++){
    for(j=0; j<n_books; j++){
      printf("%d, ", train[i][j]);
    }
    printf("\n");
  }
  for(i=0; i<n_test; i++){
    for(j=0; j<n_books; j++){
      printf("%d, ", test[i][j]);
    }
    printf("\n");
  }
}

float** getK(float** similars, int n, int k){
  /*
   *PARAMETERS:
   *  - float** similars     :  returned array from sim() function
   *  - int n                :  n_train (also the size of the similars array)
   *  - int k                :  given neighbor number
   *
   *TASK:
   *  - Inside the while loop "similarity array is returned x k" times. Each new kth step finds the maximum and marks it.
   *  - In this way, in another step, it ignores the marked ones and finds the next maximum.
   *
   *RETURNS:
   *  - k selected maximum matrix: The first line keeps the values ​​of this k neighbors,
   *  - while the second line keeps the user indices in the train set.
   *
   *COMPLEXITY:
   *  - Theta(n x k) --> O(n)
   */

  int i; // for iterating
  float** k_similars = (float**)calloc(2,sizeof(float*)); // we return this
  for(i=0; i<2; i++){
    k_similars[i] = (float*)calloc(k,sizeof(float));
  }

  int* selected = (int*)calloc(n,sizeof(int)); // marking selected maximums
  int j=0,m=0; // indexing and iterating
  float max = -1; // initial max value
  int max_idx; // index of maximum in float** similars

  i=0;
  while(i<n*k){ // in n*k steps we find k maximums

    if(selected[j]==0){ // if not selected
      if((*similars)[j] > max ){ // and bigger than max (step individual)
        max=(*similars)[j]; // assign new max
        max_idx = j; // assign its index
      }
    }

    j++;
    i++;
    if(j==n){ // if a step is completed in n*k
      j=0;
      k_similars[0][m] = (*similars)[max_idx]; // assign the max
      k_similars[1][m] = max_idx; // assign the index of max
      selected[max_idx] = 1; // "i was selected"
      m++;
      max = -1; // initial value for max, again (individual steps)
    }
  }
  return k_similars;
}

int maxRate(float** preda, int n){
  /*
   *PARAMETERS:
   *  - float** preda  :  predicted rates matrix
   *  - int n          :  non-read book number (column size of float** preda)
   *
   *TASK & RETURNS:
   *  - returns the index of maximum rate to recommend max rated predicted book
   */
  float max = -100;
  int i, max_idx;
  for(i=0; i<n; i++){
    if(preda[0][i] > max){
      max = preda[0][i];
      max_idx = preda[1][i];
    }
  }
  return max_idx;
}
