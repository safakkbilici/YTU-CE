#include<stdio.h>
#include<stdlib.h>

int max(int,int);
int knapsnack(int*,int*,int,int);

int main(){
  int nitems,i, w;
  printf("Please enter the number of items: ");
  scanf("%d", &nitems);
  printf("Please enter the w: ");
  scanf("%d", &w);

  int* values = (int*)calloc(nitems, sizeof(int));
  int* weights = (int*)calloc(nitems, sizeof(int));

  for(i=0; i<nitems; i++){
    printf("Please enter the value of %dth item: ", i+1);
    scanf("%d",&values[i]);
    printf("Please enter the weight of %dth item: ", i+1);
    scanf("%d",&weights[i]);
  }

  printf("%d\n",knapsnack(weights,values,w,nitems));

}


int knapsnack(int* weights, int* values, int w, int nitems){
  int i, j;
  int knap[nitems+1][w+1];
  for(i=0; i<nitems+1; i++){
    for(j=0; j<w+1; j++){
      if(i==0 || j==0){
        knap[i][j] = 0;
      }
      else if(weights[i-1] < w+1){
        knap[i][j] = max(values[i-1] + knap[i-1][j-weights[i-1]], knap[i-1][j]);
      }
      else{
        knap[i][j] = knap[i-1][j];
      }
    }
  }
  return knap[nitems][w];
}

int max(int a, int b){
  return (a > b)? a : b;
}
