#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* initArray(int*,int);
void printArray(int*,int);
void mergeSort(int*,int,int);
void merge(int*,int,int,int);
int  minDiff(int*, int, int*);

int main(int argc, char** argv){

  int n; // length of array
  int* arr; // the array
  int min; // variable for minimum value
  int i;

  printf("Enter the number of element of array: ");
  scanf("%d",&n);

  arr = initArray(arr, n); // initializes the array
  printf("\n");
  printf("Array: [ ");
  printArray(arr,n); // prints the array
  printf("]\n");
  mergeSort(arr,0,n-1);
  printf("\n");
  printf("Sorted Array: [ ");
  printArray(arr,n); // prints the array
  printf("]\n");

  min = minDiff(arr,n,&i); // calculates min and returns it, also changes values i and j
  printf("Minimum difference is between index %d and %d and equal to %d.",i,i+1,min);


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

void mergeSort(int* arr, int p, int r){ //sorts the elements in the subarray A[p..r]
  /*PARAMETERS:
   *   int* arr: the array
   *   int p: leftmost index (initial: 0)
   *   int r: rightmost index (initial: n-1)
   */
  int q;
  if(p<r){
    q = (p+r)/2;
    mergeSort(arr, p, q); // A[p..r] into two subarrays: A[p..q]
    mergeSort(arr,q+1, r); // and A[q + 1..r]
    merge(arr,p,q,r); // merging pairs of 1-item sequences to form sorted sequences of length 2, 
                      //merging pairs of sequences of length 2 to form sorted sequences of length 4, 
                      //and so on, until two sequences of length n=2 are merged to form the final
                      //sorted sequence of length n.
  }
}

void merge(int* arr, int p, int q, int r){
  /*PARAMETERS:
   *  int* arr: the array
   *  int p: leftmost index (initial: 0)
   *  int q: middle index
   *  int r: rightmost index (initial: n-1)
   *
   */
  int i;
  int j;
  int k;
  int nB;
  int *B;
  nB = r-p+1;
  B = (int*)malloc(nB*sizeof(int));
  i=p;
  j=q+1;
  k=0;
  while((i<=q) && (j<=r)){
    if(arr[i] < arr[j]){
      B[k++] = arr[i++];
    }
    else{
      B[k++] = arr[j++];
    }
  }
  while(i<=q) B[k++] = arr[i++];
  while(j<=r) B[k++] = arr[j++];

  for(i=p; i<=r; i++){
    arr[i] = B[i-p]; // copy the sorted array
  }

  free(B);
}

int minDiff(int* arr, int n, int* index){
  /*
   * PARAMETERS:
   *  int* arr: the array
   *  int n: size
   *  int* index: it will be assigned as index of pairs
   */
  int i; //iterator
  int min = 10000; //initial min
  int diff; // minimum difference
  for(i=0; i<n-1; i++){
    diff = abs(arr[i+1] - arr[i]); // find absoulte difference
    if(diff < min){
      min = diff;
      *index = i;
    }
  }
  return min;
}


