#include<stdio.h>

union doub {
	
	unsigned char c[2];
	unsigned short val;
	
};

typedef union {
	
	struct {
		
		char c1,c2;
		
	}s;
	long j;
	float x;
}u;

union asd {
	struct {
		char f1,f2;
		short f3;
	}us;
	unsigned char f4[5];
};


int main() {
	
	union doub d;
	d.c[0]=1;
	d.c[1]=3;
	
	printf("%d",d.val); // 0000001100000001 = 769 
	
	u example;
	example.s.c1='a';
	example.s.c2='b';
	example.j=6;
	printf("\n%d",example.s.c1); // prints 6
	printf("\n%d",example.s.c2); // prints 0
	
	union asd test={1,2,3,4,5,6};
	union asd test1={.f4 = {1,2,3,4,5,6}};
	printf("\n%d %d %d",test.us.f1,test.us.f2,test.us.f3);
	
	
	return 0;
}
