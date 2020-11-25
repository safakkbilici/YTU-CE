#include<stdio.h>
typedef struct {
	unsigned int day:5;
	unsigned int month:4;
	unsigned int year:11;
}DATE;
int main () {
	DATE arr[3];
	int tarih1;
	// scanf("%d",&arr[0].day); is illegal 
	scanf("%d",&tarih1);
	arr[0].day=tarih1;
	printf("%d",arr[0].day);
	return 0;
}
