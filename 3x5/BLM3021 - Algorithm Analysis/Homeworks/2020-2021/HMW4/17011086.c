#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void scanMatrix(int**,int);//for input the matrix
int rowInFirstRow(int*,int*,int);//checks whether given row's elements in first row
int colorRepeatedInRow(int*,int);//checks whether a color is repeated in a row
int getColorIndex(char*);//gets color index by given string color
void printMatrixByColor(int**,int);//prints matrix by colors
void backtrack(int**,int,int,int**,int,int);//backtracking
void shift(int**,int,int,int);//shift row right


char colors[8][20] = {"red", "green", "blue", "gray", "yellow", "pink", "purple", "orange"}; // color encodings

int main(){


  int N; // matrix size
  int** table; // the matrix
  int i,j; // iterators
  int mode; //
  printf("-----------------------------------\n");
  printf("Available colors:\n \n");
  for(i=0; i<8; i++){
    printf("--> %s\n",colors[i]);
  }
  printf("-----------------------------------\n\n");

  do{
    printf("For the table, enter a number between 3 and 8: ");
    scanf("%d",&N);
  }while(N>8 || N<3);

  table = (int**)calloc(N,sizeof(int*)); // the matrix
  for(i=0; i<N; i++){
    table[i] = (int*)calloc(N,sizeof(int));
  }
  scanMatrix(table,N);
  printf("\n");

  int* shifted_times; // shifted array
  /*
   * this array contains the information
   * "how many times row i shifted"
   * row -> i
   * shifted times -> shifted_times[i]
   */
  shifted_times = (int*)calloc(N,sizeof(int));
  backtrack(table,N,1,&shifted_times,0,-1);

  return 0;
}


void scanMatrix(int** table, int N){
  /*
   *PARAMETERS:
   *  - int** table : our matrix
   *  - int N       : table size
   *
   *TASK:
   *  - user gives color input to this matrix
   *  - also checks some conventions
   */
  int i=0; //iterator
  int j=0; // iterator
  int k; // iterator
  int color_index; // color indexing
  int* first_row; // contains first row to check other rows in first row
  char scan_color[20]; // color input by user
  int first_row_flag = 0;

  first_row = (int*)calloc(N,sizeof(int));

  while(i<N){
    j=0;
    while(j<N){
      do{
        printf("Enter the color (%d,%d): ",i,j);
        scanf("%s",scan_color);
        color_index = getColorIndex(scan_color);
      }while(color_index == -1); // get input while the color is in color table

      table[i][j] = color_index; // give integer representation of this color to matrix

      j++;
    }

    if(first_row_flag == 1){ // if first row is initialized
      if(colorRepeatedInRow(table[i],N) == 1 || rowInFirstRow(first_row, table[i], N) == 0){ // check current row's elements are repeated in a row
        printf("You repeated a color in a row or you entered different colors from the first row. You must enter the row %d again! \n", i);
      }
      else{ // if everything is okey
        i++; // input the next row!
      }
    }

    else if(first_row_flag == 0){ // if the first row currently initialized
      if(colorRepeatedInRow(table[i],N) == 1){ // check current row's elements are repeated in a row
        printf("You repeated a color in a row. You must enter the row %d again! \n", i);
      }
      else{
        first_row_flag = 1; // if everything is okey
        for(k=0; k<N; k++){
          first_row[k] = table[0][k]; // copy first row to first_row array
        }
        i++;
      }
    }
  }
}

int rowInFirstRow(int* first_row, int* other_row, int N){
  /*
   *PARAMETERS:
   *  - int* first_row    :  contains first row's element
   *  - int* other_row    :  currently initialized row, we will compare it
   *                                                    with first_row
   *  - int N             :  the size
   *
   *TASK
   *  - If the user enters a color different from the colors in row 0 in that row (other than 0),
   *  - the user continues to request input for that row until they enter the same colors.
   *
   *RETURNS:
   *  - 0: if current row has at least one element different from first row's elements
   *  - 1: current row's elements are same as first row's.
   */

  int i=0; // iterator
  int j=0; // iterator
  int is_in=1; // if is in
  int counter = 0; // counter

  while(i<N  && is_in == 1){
    counter = 0;
    j = 0;
    while(j<N && is_in == 1){
      if(first_row[j] != other_row[i]){
        counter++;
      }
      j++;
    }
    if(counter == N){ // if this, then not in
      is_in = 0;
    }
    i++;
  }
  return is_in;
}

int colorRepeatedInRow(int* the_row, int N){
  /*
   *PARAMETERS:
   *  - int* the_row : current row
   *  - int N        : the size
   *
   *TASK:
   *  - checks whether the inputs/colros are repeated in a current row
   *
   *RETURNS:
   *  - 1: If a color is repeated more than once in that row
   *  - 0: otherwise
   *
   */
  int i=0; // iterator
  int j=0; // iterator
  int is_repeated=0; // is repeated

  while(i<N  && is_repeated == 0){
    j = i + 1;
    while(j<N && is_repeated == 0){
      if(the_row[j] == the_row[i]){ // if this elemets are equal
        is_repeated = 1; // then return this element is repeated in a row
        return is_repeated;
      }
      j++;
    }
    i++;
  }
  return is_repeated;
}

int getColorIndex(char* color){
  /*
   *PARAMETERS:
   *  - char* color  : the color
   *
   *TASK:
   *  - calculates the integer representation of this color string
   *
   *RETURNS:
   *  -  i:  index of this color in global variable char** colors
   *  - -1:  if the given color string nott in the color array
   *
   */
  int i=0;
  while(strcmp(colors[i],color) !=0 && i<8){
    i++;
  }
  if(strcmp(colors[i],color) ==0){
    return i; // if this color is in color string array
  }
  else{
    printf("Upss. Typo... Enter again:\n");
    return -1; // if not in the color array
  }
}

void backtrack(int** table, int N, int at_row, int** shifted_times, int back, int solution){
  /*
   *
   *PARAMETERS:
   *  - int** table         :  the matrix
   *  - int N               :  the size
   *  - int at_row          :  index of current row
   *  - int** shifted_times :  --explained in main()--
   *  - int back            :  if there is no shift in that row
   *                           back to the previous row
   *  - int solution        :  contains whether the solution is found (not necessary)
   *
   *TASK:
   *  - algorithm is clearly explained in report of this homework, to make a short explanation:
   *  - (1) if current row is shifted N times then back to the previous row
   *  - (2) if current row is perfectly located then back to the next row
   *  - (3) if current row is not perfectly located and not shifted N times, then keep going shifting
   *  - (4) if current row number + 1 is equal to the N, then there is a solution
   *  - (5) if current row is 0, then there is no solution
   *
   *INITIAL CALL:
   *  - backtrack(table,N,1,&shifted_times,0,-1) -> start from second (1) row
   *
   */
  int i=0,j=0,k,l; // all iterators
  int at_row_decrease = at_row-1; // iterator variable for checking the row is perfectly located
  int count = 0; // control variable for checking the row is perfectly located

  if(at_row<N && at_row >=0 && solution == -1){
    if(back == 1){ // if nack
      shift(table,N,at_row,1); // then shift once and keep going (1)
      (*shifted_times)[at_row]++; // increase shifting count
    }
    while(at_row_decrease>=0){ // while to the first row
      j=0;
      while(j<N){
        if(table[at_row][j] == table[at_row_decrease][j]){
          count++; // if not perfectly located, then increase this
        }
        j++;
      }
      at_row_decrease--;
    }

    if(count != 0 && at_row!=0){ // if not perfectly located
      if((*shifted_times)[at_row] < N){ // and the shifting times lower than N
        shift(table,N,at_row,1); // shift one more time
        (*shifted_times)[at_row]++; // increase shifted time
        backtrack(table,N,at_row,shifted_times,0,-1); // (3)
      }
    }

    if((*shifted_times)[at_row] == N && at_row!=0){ // if n times shifted
      (*shifted_times)[at_row] = 0; // shifting is equal to 0 again
      printf("Row %d cannot be located. Backing to the row %d.\n",at_row,at_row-1);
      backtrack(table,N,at_row-1,shifted_times,1,-1); // back to the previous row (1)
    }

    else if(count == 0){ // if perfectly located
      if(at_row == 0){ // and the row is first row (first row is always perfectly located in theory)
        printf("\nNO SOLUTION\n"); // (5)
        return;
      }
      else{ // not the first row
        printf("Row %d is perfectly located:\n",at_row);
        printMatrixByColor(table,N); // print the perfectly located stage of this algorithm (as wanted from us )
        printf("\n");
        if(at_row+1 == N){ // if the rows are ended
          printf("\nTHERE IS SOLUTION: \n");
          printMatrixByColor(table,N);
          return; // (4)
        }
      }
      backtrack(table,N,at_row+1,shifted_times,0,-1); // (2) if current row is perfectly located then back to the next row
    }
  }
}

void shift(int** table, int N, int row, int times){
  /*
   *PARAMETERS:
   *  - int** table    : our matrix
   *  - int N          : the size
   *  - int row        : the current row
   *  - int times      : how many times shifting
   *                     (not necessary in our problem but given as a parameter for flexibility)
   *
   *
   *TASK:
   *  - shifts current row by right
   */

  int i=0; // iterator
  int* shifted; // shifted array
  shifted = (int*)calloc(N,sizeof(int));
  for(i=N-1; i>=0; i--){
    shifted[(i+times) % N] = table[row][i]; // shifting operation
  }
  for(i=0; i<N; i++){
    table[row][i] = shifted[i]; // copy the shifted array into current row
  }
}

void printMatrixByColor(int** table, int N){
  /*
   *PARAMETERS:
   *  - int** table : the matrix
   *  - int N       : the size
   *
   *TASK:
   *  - prints the matrix by its color with hidden representation of color (integer)
   */
  int i=0;
  int j=0;
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("[%-10.10s(%d)]", colors[table[i][j]],table[i][j]); // print string with padding
    }
    printf("\n");
  }
}
