#include<stdio.h>
#include<stdlib.h>

struct node{
	
	int data;
	struct node* next;
};

typedef struct node NODE;
void get_member(NODE*,int);
void write_char(FILE*,NODE*);

int main () {
	
	FILE* fp;
	NODE* head;
	int n,i,val;
	
	head=(NODE*)malloc(sizeof(NODE));
	head->data=0;
	head->next=NULL;
	fp=fopen("linked_list_file.txt","w");
	
	printf("Member number: ");
	scanf("%d",&n);
	
	
	for(i=0; i<n; i++) {
		printf("Enter Val: ");
		scanf("%d",&val);
		get_member(head,val);
	}
	
	write_char(fp,head);
	
	
	
	return 0;
}

void get_member(NODE* head,int val) {
	
	
	NODE* current=head;
	
	while(current->next !=NULL) {
		
		current=current->next;
		
	}
	
	current->next=(NODE*)malloc(sizeof(NODE));
	current->next->data=val;
	current->next->next=NULL;
}

void write_char(FILE* fp, NODE* head) {
	NODE* current=head;
	int counter=0;
	while(current->next != NULL) {
		
		fprintf(fp,"member %d: %d\n",counter,current->data);
		current=current->next;
		counter++;
	}
	fprintf(fp,"member %d: %d\n",counter,current->data);
}
