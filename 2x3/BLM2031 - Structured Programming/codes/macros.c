#include<stdio.h>
#include<string.h>
#define LONG_MACRO "this is very\
					long macro"
#define N 100
#define MUL_BY_TWO(a) ((a)+(a))
#define square1(a) ((a)*(a))
#define square2(a) a*a
#define min(a,b) ((a)<(b) ? (a):(b))
#define TEST 20

int main () { 
	
	
	int j= 2*square1(3+4);
	printf("j:  %d\n",j);
	j=2*square2(3+4);
	printf("j:  %d\n",j);
	j=min(3,5);
	printf("j:  %d\n",j);
	int x=1;
	int y=5;
	j=min(++x,y); // ((++x) < (y) ? (++x) : (y))
	printf("j:  %d\n",j); // j=3
	

	#ifndef False
		#define False 0 
	#elif False
		#undef False
		#define False 0
	#endif
	
	int k=False;
	printf("False: %d",k); //0
	
	#if x==1
		#undef x
		#define x 0
	#elif x==2
		#undef x
		#define x 3
	#else 
		#define x 4
	#endif
	
	
	
	
	
	return 0;
}
