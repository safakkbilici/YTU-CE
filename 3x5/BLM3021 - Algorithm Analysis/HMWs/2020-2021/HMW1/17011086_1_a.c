#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* initArray(int*,int);
void printArray(int*,int);
int minDiff(int*,int,int*,int*);

int main(int argc, char** argv){
  int n; // length of array
  int* arr; // the array
  int min; // variable for minimum value
  int i; // index of first element from min calculation
  int j; // index of second element from min calculation

  printf("Enter the number of element of array: ");
  scanf("%d",&n);

  arr = initArray(arr, n); // initializes the array
  printf("\n");
  printf("Array: [ ");
  printArray(arr,n); // prints the array
  printf("]\n");
  min = minDiff(arr,n,&i,&j); // calculates min and returns it, also changes values i and j
  printf("Minimum difference is between index %d and %d and equal to %d.",i,j,min);

  return 0;
}

int* initArray(int* arr, int n){
  /*
   *PARAMETERS:
   *  int* arr: our array
   *  int n: length of our array
   *RETURNS:
   *  int* arr: the initialized array
   *TASK:
   *  allocates and initializes the array
   */
  int i; // iterator for column allocation
  arr = (int*)calloc(n,sizeof(int)); // allocating array
  for(i=0; i<n; i++){
    printf("Enter the element %d: ",i);
    scanf("%d",&arr[i]);
  }
  return arr;
}

void printArray(int* arr, int n){
  /*
   *PARAMETERS:
   *  int* arr: our array
   *  int n: length of our array
   *TASK:
   *  prints our array
   */
  int i; // iterator for printing
  for(i=0; i<n; i++){
    printf("%d ",arr[i]);
  }
}

int minDiff(int* arr, int n, int* i, int* j){
  /*
   *PARAMETERS
   *  int* arr: our array
   *  int n: length of our array
   *  int* i: stores first index of min calculation elements
   *  int* j: stores second index of min calculation elements
   *RETURNS:
   *  int min: lowest minimum value
   *TASK:
   *  finds minimum difference value in an array
   */
  int min = 1000; // first min value
  int diff; // stores the lowest minimum difference value
  int k; // iterator for outer for loop
  int l; // iterator for inner for loop
  for(k=0; k<n-1; k++){
    for(l=k+1; l<n; l++){
      diff = abs(arr[k] - arr[l]); // computes the absolute value of elements
      if(diff < min){ // if lower than last lowest difference value
        min = diff; // change to new lowest min value
        *i = k; // keep index 1
        *j = l; // keep index 2
      }
    }
  }
  return min;
}
