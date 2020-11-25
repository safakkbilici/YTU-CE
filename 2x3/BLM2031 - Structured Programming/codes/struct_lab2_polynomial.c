#include<stdio.h>
#include<stdlib.h>

struct features {
	
	
		int coeff;
		int expo;
		
	};
	
struct polynoms {
	
		int n;
		struct features* ftrs;
		
		
	};
	
typedef struct features FEATURES;
typedef struct polynoms POLYNOMS;

int max(POLYNOMS*,POLYNOMS*);
void GetPolynoms(POLYNOMS*);
void PrintPolynoms(POLYNOMS*);
POLYNOMS* sumPolynoms(POLYNOMS*,POLYNOMS*);




int main() {
	
	POLYNOMS *poly1, *poly2, *sumPoly;
	
	poly1=(POLYNOMS*)calloc(1,sizeof(POLYNOMS));
	poly2=(POLYNOMS*)calloc(1,sizeof(POLYNOMS));
	GetPolynoms(poly1);
	GetPolynoms(poly2);
	PrintPolynoms(poly1);
	PrintPolynoms(poly2);
	sumPoly=sumPolynoms(poly1, poly2);
	
		
		
	
	
	
	return 0;
	
}


void GetPolynoms(POLYNOMS* poly) {
	
	static int number=1;
	int i;
	
	printf("\n");
	printf("Enter the Number of Term of Polynom%d: ",number);
	scanf("%d",&poly->n);
	printf("\n");
	number++;
	
	poly->ftrs=(FEATURES*)calloc(poly->n,sizeof(FEATURES));
	
	
	for(i=0; i<poly->n; i++) {
		
		printf("Enter the Coefficient for Term(%d): ",i+1);
		scanf("%d",&poly->ftrs[i].coeff);
		printf("\n");
		printf("Enter the Expo for Term(%d): ",i+1);
		scanf("%d",&poly->ftrs[i].expo);
		printf("\n");
	}
}

void PrintPolynoms(POLYNOMS* poly) {
	
	printf("\n");
	int i;
	static int polynumber=1;
	printf("Polynom %d is:   ",polynumber);
	polynumber++;
	for(i=0; i<poly->n; i++) {
		
		if(i<=(poly->n)-2) {
			
			printf("%d(x^%d) + ",poly->ftrs[i].coeff,poly->ftrs[i].expo);
			
		}
		
		else if(i == (poly->n)-1) {
			
			printf("%d(x^%d)",poly->ftrs[i].coeff,poly->ftrs[i].expo);
			
		}
	}
}

POLYNOMS* sumPolynoms(POLYNOMS* poly1, POLYNOMS* poly2) {
	
	POLYNOMS* sumpoly;
	int maxp,i,j;
	maxp=max(poly1,poly2);
	sumpoly=(POLYNOMS*)calloc(maxp,sizeof(POLYNOMS));
	
	for(i=0; i<poly1->n; i++) {
		
		sumpoly[poly1->ftrs[i].expo].ftrs->expo += (poly1->ftrs[i].coeff);
		
		
	}
	
	for(j=0; j<poly2->n; j++) {
		
		sumpoly[poly2->ftrs[j].expo].ftrs->expo += (poly2->ftrs[j].coeff) ;
		
	}	
	
	for(i=0; i<maxp; i++) {
		
		printf("%d\n",sumpoly[i].ftrs->expo);
		
	}
	
	return sumpoly;			
			
}			
			

			
	
int max(POLYNOMS* poly1, POLYNOMS* poly2) {
	
	int max=0,i;
	
	for(i=0; i<poly1->n; i++) {
		
		if(poly1->ftrs[i].expo > max ) {
			
			max=poly1->ftrs[i].expo;
			
		}
	}
	
	for(i=0; i<poly2->n; i++) {
		
		if(poly2->ftrs[i].expo > max) {
			
			poly2->ftrs[i].expo=max;
		
		}
	}
	
	
	return max;
	
}
