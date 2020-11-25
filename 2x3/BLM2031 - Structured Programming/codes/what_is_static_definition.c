      
#include<stdio.h> 
int fun() 
{ 
  static int count = 0; 
  count++; 
  return count; 
} 

int fun2() 
{ 
  int count = 0; 
  count++; 
  return count; 
} 
   
int main() 
{ 
  printf("%d ", fun()); //1 
  printf("%d ", fun()); //2
  
  printf("%d ", fun2()); //1
  printf("%d ", fun2()); //1
  
  
  return 0; 
}
