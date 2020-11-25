#include<stdio.h>
#include<stdlib.h>

struct main {
	
	int obj;
	struct main* next;
};
typedef struct main MAIN;
void getobjects(MAIN*,int);
void list_the_list(MAIN*);
void sort_the_list(MAIN*,void (*swap)(int*,int*));
void swapped(int*,int*);
MAIN* reis_hemen_one_degeri_koy(MAIN*,int);
void reis_ortaya_caksana_bi_tane(MAIN*,int,int);

int main() {
	MAIN* head, *new_head;
	int n;
	
	printf("Enter the number of objects: ");
	scanf("%d",&n); 
	head=(MAIN*)malloc(sizeof(MAIN));
	head->obj=10;
	head->next=NULL;
	getobjects(head,n);
	list_the_list(head);
	sort_the_list(head,swapped);
	printf("\n");
	list_the_list(head);
	new_head=reis_hemen_one_degeri_koy(head,313);
	sort_the_list(new_head,swapped);
	printf("\n");
	list_the_list(new_head);
	reis_ortaya_caksana_bi_tane(new_head,137,3);
	printf("\n");
	list_the_list(new_head);

	return 0;
}

void getobjects(MAIN* head, int n){
	
	MAIN* current=head;
	int i=0,obj;
	
	for(i=0; i<n; i++) {
		current=head;
		
		while(current->next!=NULL) {
			
			current=current->next;
		
		}
		printf("Enter the Price: ");
		scanf("%d",&obj);
		current->next=(MAIN*)malloc(sizeof(MAIN));
		current->next->obj=obj;
		current->next->next=NULL;
	}
		
}
void list_the_list(MAIN* head) {
	
	MAIN* current= head;
	
	while(current->next != NULL) {
		
		printf("%d  ",current->obj);
		current=current->next;
	}
	printf("%d",current->obj);
	
}
void sort_the_list(MAIN* head, void(*swap)(int* a,int* b)) {
	
	
	MAIN* current=head;
	MAIN* control=NULL;
	int swapped;
	
	do{
		current=head;
		swapped=0;
		while(current->next != control) {
			
			if(current->obj > current->next->obj) {
				
				(*swap)(&(current->obj),&(current->next->obj));
				
			}
			
			current=current->next;
		}
		control=current;
	}while(swapped);
}
void swapped(int* a, int* b) {
	
	int temp=*a;
	*a=*b;
	*b=temp;
}

MAIN* reis_hemen_one_degeri_koy(MAIN* head,int val) {
	
	MAIN* new_head;
	
	new_head=(MAIN*)malloc(sizeof(MAIN));
	new_head->obj=val;
	new_head->next=head;
	return new_head;
	
}

void reis_ortaya_caksana_bi_tane(MAIN* head, int val, int location) {
	
	MAIN* current=head,*newnode;
	
	int i=0;
	
	newnode=(MAIN*)malloc(sizeof(MAIN));
	
	newnode->obj=val;
	newnode->next=NULL;
	
	while(i<location) {
		current=current->next;
		i++;
	}
	
	newnode->next=current->next;
	current->next=newnode;
	
}
