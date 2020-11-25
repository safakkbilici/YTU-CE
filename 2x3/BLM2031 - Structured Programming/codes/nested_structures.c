#include<stdio.h>
#include<stdlib.h>



typedef struct {
	
	char date;
	char month;
	char year;
	
}DATE;

typedef struct{
	
	char name[20];
	int payment;
	DATE xdate;
	
}EMPLOYEE;


int main () {
	
	EMPLOYEE employee2={"marx","17000",{11,10,90}};
	EMPLOYEE employee1;
	
	employee1.xdate.month=2;
	employee1.payment=10000;
	employee1.xdate.date=20;
	
	return 0;
	
}
