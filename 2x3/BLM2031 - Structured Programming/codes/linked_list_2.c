#include<stdio.h>
#include<stdlib.h>


struct nodes {
	
		int val;
		struct nodes* next;
	};
	
typedef struct nodes node;
void push(node*,int);
void list(node*);
node* pushFront(node*, int);
void deleteNode(node*,int);
void addNode(node*,int,int);
int main () {
	
	node *head, *newhead, *dummy;
	int num,i;
	
	head=(node*)malloc(sizeof(node));
	printf("enter num: ");
	scanf("%d",&num);
	head->val=num;
	head->next=NULL;
	
	for(i=0; i<10; i++) {
		
	printf("enter num: ");
	scanf("%d",&num);
	push(head,num);
	}
	
	list(head);
	
	printf("\nenter num: ");
	scanf("%d",&num);
	newhead=pushFront(head,num);
	
	list(newhead);
	
	printf("\n");
	
	addNode(newhead,31,69);
	
	list(newhead);
	

	if(num==newhead->val) {
		
		dummy=newhead->next;
		free(newhead);
	}
	
	else{
		
		deleteNode(newhead,num);
	
	}
	return 0;
	
}

void push(node* head, int num) {
	
	node* current=head;
	while(current->next!=NULL) {
		
		current=current->next;
		
	}
	
	current->next=(node*)malloc(sizeof(node));
	current->next->next=NULL;
	current->next->val=num;
	
}

void list(node* head) {
	
	node* current = head;
	
	while(current->next!=NULL) {
		
		printf("%d 	",current->val);
		current=current->next;
	}
	
	printf("%d",current->val);
	
}

node* pushFront(node* head, int num) {
	
	node* newN;
	
	newN=(node*)malloc(sizeof(node));
	newN->next=head;
	newN->val=num;
	
	return newN;
	
}

void deleteNode(node* newhead, int num) {
	
	node* current=newhead;
	node* before=NULL;
	
	while(current->val!=num &&  current->next!=NULL){
		
		before=current;
		current=current->next;
		
	}
		
		
	if(current->val!=num) {
		
		printf("no node contains num");
		
	}
	
	else{
		
		before->next=current->next;
		free(current); 
		
	}
}

void addNode(node* newhead, int num, int select) {
	
	node* current= newhead;
	node* before= (node*)malloc(sizeof(node));
	
	
	before->val=num;
	before->next=NULL;
	
	while(current->val!=select && current->next!=NULL) {
		
		current=current->next;
		
	}
	
	before->next=current->next;
	current->next=before;

	
	
}
	
	
	
	
	
	

		



