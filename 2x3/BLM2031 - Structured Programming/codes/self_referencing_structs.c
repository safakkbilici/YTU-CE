#include<stdio.h>
#include<stdlib.h>

struct s {
	
		int a,b;
		float c;
		
		struct s* pointer_to_s;
		
	};
	
	
int main() {
	
	struct s S1={1,2,1.2,NULL};
	
	struct s S2={3,4,5.6,NULL};
	
	S1.pointer_to_s=&S2;
	S2.pointer_to_s=&S1;
	
	printf("%d %d", (S1.pointer_to_s)->a,(S1.pointer_to_s)->b); // 3,4
	printf("\n");
	printf("%d %d", (S2.pointer_to_s)->a,(S2.pointer_to_s)->b); // 1,2
	
	
	return 0;
	
}
	
	
	

