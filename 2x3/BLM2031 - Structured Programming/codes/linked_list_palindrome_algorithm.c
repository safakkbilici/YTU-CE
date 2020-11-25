#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
struct node {
	
	char* word;
	struct node* next;
};
typedef struct node NODE;

void getlist(NODE*, char*);
int list_the_list_and_get_score(NODE*,int (*palindromee)(int),int(*normall)(int));
int palindrome(int);
int normal(int);

int main () {
	
	int max_word,n;
	NODE* head;
	char* word;
	
	
	
	head=(NODE*)malloc(sizeof(NODE));
	
	printf("Enter the maximum length of your word: ");
	scanf("%d",&max_word);
	
	head->word=(char*)calloc(max_word,sizeof(char));
	word=(char*)calloc(max_word,sizeof(char));
	
	printf("Enter the length of your word list: ");
	scanf("%d",&n);
	
	printf("Enter the element 1: ");
	scanf("%s",word);
	head->word=word;
	head->next=NULL;
	
	
	for(int i=1; i<n; i++) {
		
		printf("Enter the element %d: ",i+1);
		scanf("%s",word);
		getlist(head,word);
		
	}
	int score =list_the_list_and_get_score(head,palindrome,normal);
		
		
	
	
	
	
	
	
	
	
	return 0;
}

void getlist(NODE* head, char* word) {
	
	
	NODE* current=head;
	
	while(current->next != NULL) {
		
		current = current->next;
		
	}
	current->next=(NODE*)malloc(sizeof(NODE));
	current->next->word=word;
	current->next->next=NULL;
	
}

int list_the_list_and_get_score(NODE* head,int (*palindromee)(int a), int (*normall)(int a)) {
	
	NODE* current=head;
	int final_score=0,a,size;
	
	while( current->next != NULL) {
		
		size=strlen(current->word);
		int counter=0;
		int i=0;
		while((current->word[0][i] == current->word[0][size-i-1] && i<size )) {
			counter++;
			i++;
		}
		if(i==(size-1)) {
			
			a=(*palindromee)(size);
			final_score=final_score+a;
			
		}
		
		else{
			
			a=(*normall)(size);
			final_score=final_score+a;
		}
			
			
			
			 
		printf("\n%s",current->word);
		current=current->next;
		
	}
	printf("\n%s",current->word);
	return final_score;
	
}




int palindrome(int size) {
	
	return size*2;
	
}

int normal(int size) {
	
	return size;
	
}
		
		












