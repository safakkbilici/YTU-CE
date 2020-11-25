#include<stdio.h>
#include<stdlib.h>

struct node {
	
	int val;
	struct node* next;
	
};
typedef struct node NODE;
void pushend(NODE*,int);
void list(NODE*);
NODE* pushfront(NODE*,int);
void swap(int*,int*);
void BubbleSort(NODE*, void(*swaplist)(int*,int*));
void pushintosomewhere(NODE*,int,int);
int main() {
	
	NODE* head, *newhead;
	int num,integerlocation;
	
	head=(NODE*)malloc(sizeof(NODE));
	
	printf("Num: ");
	scanf("%d",&num);
	
	head->val=num;
	head->next=NULL;
	for( int i=0; i<10; i++) {
	printf("Num: ");
	scanf("%d",&num);
	pushend(head,num);
}
	
	list(head);
	
	printf("\nNum: ");
	scanf("%d",&num);
	newhead=pushfront(head,num);
	list(newhead);
	
	
	printf("\nNum: ");
	scanf("%d",&num);
	printf("Integer Location: ");
	scanf("%d",&integerlocation);
	pushintosomewhere(newhead,num,integerlocation);
	list(newhead);
	
	BubbleSort(newhead,swap);
	list(newhead);
	
	return 0;
}

void pushend(NODE* head, int num) {
	
	NODE* current=head;
	
	while(current->next != NULL) {
		
		current=current->next;
		
	}
	current->next=(NODE*)malloc(sizeof(NODE));
	current->next->val=num;
	current->next->next=NULL;
	
}

void list(NODE* head) {
	
	NODE* current=head;
	printf("\n");
	while(current->next != NULL) {
		
		printf("%d	",(current->val));
		current=current->next;
	}
	printf("%d",(current->val));
		
}		

NODE* pushfront(NODE* head, int num) {
	
	NODE* newhead;
	newhead=(NODE*)malloc(sizeof(NODE));
	
	newhead->next=head;
	newhead->val=num;
	return newhead;
 }
 
void swap(int* x, int* y) {
	
	int tmp;
	tmp=*x;
	*x=*y;
	*y=tmp;
}

void BubbleSort(NODE* head, void (*swaplist)(int* a, int* b)) {
	
	NODE* current, *icurrent=NULL;
	int swapped;
	
	do{
		swapped=0;
		current=head;
		
		while(current->next != icurrent ) {
			
			if(current->val > current->next->val) {
				
				(*swaplist)(&(current->val),&(current->next->val));
				swapped=1;
			}
			current=current->next;
		}
		icurrent=current;
	}while(swapped);
}

void pushintosomewhere(NODE* head, int num, int integerlocation) {
	
	NODE* current=head;
	NODE* reishemensimdi=(NODE*)malloc(sizeof(NODE));
	int i=0;
	
	reishemensimdi->val=num;
	reishemensimdi->next=NULL;
	
	while(i<integerlocation) {
		
		current=current->next;
		i++;
		
	}
	reishemensimdi->next=current->next;
	current->next=reishemensimdi;
}
