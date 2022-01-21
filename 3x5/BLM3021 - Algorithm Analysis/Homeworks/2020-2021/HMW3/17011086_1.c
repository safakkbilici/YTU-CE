#include<stdio.h>
#include<stdlib.h>

int divideCeiling(int,int); // divide function
float calculateProbabilities(float**,float,float,int); // calculates the probability
void printMatrix(float**,int); // prints matrix

int main(){
  int i; // iterator
  int j; // iterator
  float p; // probability of A wins a game
  float q; // probability of B wins a game, 1-p
  int n_matches; // number of matches that will be played
  float** P_matrix; // our probability matrix
  int n_matrix; // matrix is nxn, this keeps this n variable
  float winner_a; // final probability

  printf("Enter the probability of A wins a game: ");
  scanf("%f", &p);
  printf("\n");
  q = 1-p;
  printf("Enter the number of matches: ");
  scanf("%d", &n_matches);
  printf("\n");

  n_matrix = divideCeiling(7,2)+1; //calculate the n of nxn

  P_matrix = (float**)calloc(n_matrix,sizeof(float*)); // allocate rows
  for(i=0; i<n_matrix; i++){
    P_matrix[i] = (float*)calloc(n_matrix,sizeof(float*)); // allocate columns
  }

  winner_a = calculateProbabilities(P_matrix, p, q, n_matrix); // calculate probabilities
  printMatrix(P_matrix, n_matrix); // print the matrix
  printf("\n");
  printf("The Probability: %f\n",winner_a); // print the final probability 


  return 0;
}


int divideCeiling(int a, int b){
  return (a+b-1)/b;
}

float calculateProbabilities(float** P_matrix, float p, float q, int n_matrix){
  /*PARAMETERS:
   *  - float** P_matrix : matrix for holding probabilities
   *  - float p          : probability of a wins a game
   *  - float q          : probability of b wins a game, formally it is 1-p
   *  - int n_matrix     : both row and column size of the probability matrix P_matrix
   *
   *TASK:
   *  - calculates the probability of team A winning.
   *
   *
   *         ALGORITHM
   *         -------------------
   *            1. initialize: P_matrix[0][j] = 1
   *            2. initialize: P_matrix[j][0] = 0
   *            3. calculate: P_matrix[i][j] = p * P_matrix[i-1][j] + q * P_matrix[i][j-1];
   *            4  return: P_matrix[n_matrix - 1][n_matrix - 1];
   *
   *RETURNS:
   *  - P_matrix[n_matrix - 1][n_matrix - 1], the probability of team A winning.
   */
  int i;
  int j;
  for(j=1; j<n_matrix; j++){
    P_matrix[0][j] = 1; // initial process
  }
  for(i=1; i<n_matrix; i++){
    P_matrix[i][0] = 0; // initial process
    for(j=1; j<n_matrix; j++){
      P_matrix[i][j] = p * P_matrix[i-1][j] + q * P_matrix[i][j-1]; // recurrence relation
    }
  }
  return P_matrix[n_matrix - 1][n_matrix - 1];
}

void printMatrix(float** P_matrix, int n_matrix){
  int i;
  int j;
  for(i=0; i<n_matrix; i++){
    for(j=0; j<n_matrix; j++){
      printf("%f ",P_matrix[i][j]);
    }
    printf("\n");
  }
}
