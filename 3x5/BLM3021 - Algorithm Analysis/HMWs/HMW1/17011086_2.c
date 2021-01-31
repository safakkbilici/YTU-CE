#include<stdio.h>
#include<stdlib.h>

void printMatrix(int**, int);
int** vonNeumannNeighborhood(int**,int);
int** allocateMatrix(int);
void recursiveVonNeumannNeighborhood(int***, int, int, int, int, int);

int main(int argc, char** argv){

  int N; // von neumann number
  int** matrix; // our matrix
  char iter_rec;
  printf("Enter the neighborhood value N: ");
  scanf("%d",&N);
  printf("\n");
  matrix = allocateMatrix(N);
  printf("Enter the type of algorithm (for iterative type i, for recursive type r): ");
  scanf(" %c",&iter_rec);
  printf("\n");
  if(iter_rec == 'r'){
    recursiveVonNeumannNeighborhood(&matrix,1,1,N+1,N,1); 
    /*as i mentioned in function section
     * first parameter matrix, second parameter initial row value (1)
     * third patameter how many 1's i need in this row (initial 1 always)
     * fourth parameter first 1's initial collumn position (initial N+1 always)
     * fifth parameter matrix's size
     * sixth parameter iterating parameter for assigning 1s
     */
  }
  else if(iter_rec == 'i'){
    vonNeumannNeighborhood(matrix,N);
  }
  printMatrix(matrix,N);
  return 0;
}

void printMatrix(int** mat, int N){
  /*
   *PARAMETERS:
   *   int** mat: matrix to print
   *   int N: von neumann number
   *TASK:
   *   prints the matrix
   */
  int i; // iterating row
  int j; // iterating col
  int row = (N*2+1)+2; // height
  int col = (N*2+1)+2; // width
  for(i=0; i<row; i++){
    for(j=0; j<col; j++){
      printf("%d \t",mat[i][j]);
    }
    printf("\n \n");
  }

}

int** allocateMatrix(int N){
  int i;
  int row = (N*2+1)+2; // this variable is for height of our matrix
  int col = (N*2+1)+2; // this variable is for width of our matrix
  int** matrix; // our matrix

  matrix = (int**) calloc(row,sizeof(int*)); // allocating the rows
  for(i=0; i<row; i++){
    matrix[i] = (int*)calloc(col,sizeof(int)); //allocating the columns
  }
  return matrix;
}

int** vonNeumannNeighborhood(int** matrix, int N){
  /*
   *PARAMETERS:
   *   int N: von neumann number
   *RETURNS:
   *   int** matrix: matrix with neighborhood information
   *TASK:
   *   initializes the matrix and calculates the neighborhoods then returns the matrix
   */

  int i; // this variable is for matrix allocation loop
  int j; // this variable is for keeping the column information of our algorithm
  int k; // this variable is for iterating the "how many ones i need in this row"
  int total=0; // variable for sum of total 1s
  int row2 = (N*2+1)+2; // i will change the row variable, so keep the original constant row value in row2
  int row = 1; // this variable is for iterating the rows, initialized as 1 due to first row is always 0

  i = 1; // this variable is for keeping the information "how many ones i need in this row"
  j = N+1; // this variable is for keeping the information "what is the initial column position of 1". Initialized as N+1, it must start from this value

  while(row != N*2+2){ // i need to iterate N*2+2 columns (from 1 to N*2+2) due to first and last columns are always zero
    k = i; // column index iterator
    printf("Total 1 in row %d is: %d\n",row,i);
    total = total + i;
    while(k != 0){
      matrix[row][j+k-1] = 1; // elements to one (I have i=k ones in this column from j to k-1)
      k--;
    }
    if(row < (int) row2/2){ // if my iterating row value lower than height of matrix then:
      j = j-1;              // initial "1" position of column is the previous status minus 1
      i = i + 2;            // how many i need 1 value is the previous status plus 2
    }
    else{                   // if my iterating row value greater and equal than height of matrix then:
      j = j+1;              // initial "1" position of column is the previous status plus 1
      i = i-2;              // how many i need 1 value is the previous status minus 2
    }
    row++; // increase the row
  }
  printf("Total 1 in this matrix is: %d\n\n",total);
  return matrix;
}

void recursiveVonNeumannNeighborhood(int*** matrix, int row, int i, int j, int N, int repeat){
  /*
   *PARAMETERS:
   *   int*** matrix: my matrix
   *   int row: inital row = 1, then increase through the total row number minus 2
   *   int i:  keeping the information "how many ones i need in this row" (initial 1 always)
   *   int j:  keeping the column information of our algorithm (initial = N+1 always)
   *   int N:  size of our matrix
   *   int repeat: column index iterator
   *
   *   in other words: I HAVE {repeat} ONES FROM COLUMN {j} TO {j+repeat-1} in {row} ROW
   */

  if(row != N*2+2){ //from row 1 to row total row - 2
    if(row < (int) ((N*2+1)+2)/2){  // if my iterating row value lower than height of matrix then:
      (*matrix)[row][j+repeat-1]=1; 
      if(repeat != 1){
        recursiveVonNeumannNeighborhood(matrix,row,i,j,N,repeat-1); // repeat until there is no "how many ones i need in this row"
      }
      else if(repeat == 1){
        printf("Total 1 in row %d is: %d\n",row,i);
        recursiveVonNeumannNeighborhood(matrix,row+1,i+2,j-1,N,i+2); // after iterating all 1s, it is time to increase the row
      }
    }
    else{  // if my iterating row value greater and equal than height of matrix then:
      (*matrix)[row][j+repeat-1]=1;
      if(repeat != 1){
        recursiveVonNeumannNeighborhood(matrix,row,i,j,N,repeat-1);  // repeat until there is no "how many ones i need in this row"
      }
      else if(repeat == 1){
        printf("Total 1 in row %d is: %d\n",row,i);
        recursiveVonNeumannNeighborhood(matrix,row+1,i-2,j+1,N,i-2);  // after iterating all 1s, it is time to increase the row
      }
    }
  }
}
