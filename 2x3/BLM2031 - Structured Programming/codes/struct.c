#include<stdio.h>




typedef struct {
	
	
	int a,b,c;
	
}SON;
void __init__(SON*);

int main () {
	
	SON data;
	
	__init__(&data);
	
	printf("%d %d %d",data.a,data.b,data.c);
	
	return 0;

}
void __init__(SON* data) {
	
	
	scanf("%d %d %d",&data->a,&data->b,&data->c);
	
	
}
