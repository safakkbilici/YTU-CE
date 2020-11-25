#include<stdio.h>
#include<stdlib.h>

struct node {
	
	int val;
	struct node* next;
};

typedef struct node NODE;
void sona_ekle(NODE*);
NODE* basa_ekle(NODE*);
void bastir(NODE*);
void orta(NODE*);
int main() {
	NODE* head;
	head=(NODE*)malloc(sizeof(NODE));
	head->val=10;
	head->next=NULL;
	sona_ekle(head);
	sona_ekle(head);
	sona_ekle(head);
	sona_ekle(head);
	NODE* yeni=basa_ekle(head);
	bastir(yeni);
	orta(yeni);
	bastir(yeni);
	return 0;
}
void sona_ekle(NODE* head) {
	
	
	NODE* current=head;
	
	while(current->next != NULL ) {
		
		current=current->next;
	}
	current->next=(NODE*)malloc(sizeof(NODE));
	current->next->next=NULL;
	current->next->val=20;
	
}
NODE* basa_ekle(NODE* head) {
	
	NODE* yeni;
	
	yeni=(NODE*)malloc(sizeof(NODE));
	yeni->val=0;
	yeni->next=head;
	return yeni;
}

void bastir(NODE* head) {
	
	printf("\n");
	NODE* current=head;
	
	while(current->next != NULL ) {
		
		printf("%d	",current->val);
		current=current->next;
	}
	printf("%d",current->val);
}
void orta(NODE* head) {
	
	
	NODE* tek;
	tek=(NODE*)malloc(sizeof(NODE));
	tek->val=1000;
	tek->next=NULL;
	NODE* current=head;
	
	while(current->val != 20) {
		
		current=current->next;
	}
	tek->next=current->next;
	current->next=tek;
}



