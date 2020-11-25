#include<stdio.h>
#include<stdlib.h>


struct node {
	
		int val;
		
		struct node* next;
		
	};
	
void list(struct node*);
	
int main() {
	
	struct node *head,*node2;
	
	head=(struct node*)malloc(sizeof(struct node));
	
	
	head->val=10;
	head->next=NULL;
	node2=(struct node*)malloc(sizeof(struct node));
	node2->val=20;
	node2->next=NULL;
	
	head->next=node2;
	
	list(head);
	
	
	return 0;
	
}

void list( struct node* head) {
	
	
	struct node* current = head;
	
	while(current->next!=NULL) {
		
		printf("%d",current->val);
		current=current->next;
		
	}
	
	printf("\n%d",current->val);
}
		
		
		
	
	
	



