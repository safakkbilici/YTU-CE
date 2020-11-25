#include<stdio.h>
#include<stdlib.h>
typedef struct {
	
	int a,b,c;
	
}A;


void init(A*);

int main () {
	
	A* data;
	
	data=(A*)malloc(sizeof(A));
	init(data);
	printf("%d %d %d",data->a,data->b,data->c);
	
	return 0;
	
}


void init(A* data) {
	
	
	scanf("%d %d %d",&data->a,&data->b,&data->c);
	
}
