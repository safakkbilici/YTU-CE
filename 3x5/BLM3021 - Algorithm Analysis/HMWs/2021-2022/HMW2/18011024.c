#include<stdio.h>
#include<stdlib.h>

typedef struct reklam{
	int startTime;
	int duration;
	int value;
}REKLAM;

int get_total_sample_number();
void get_info(REKLAM*,int);
REKLAM* get_info_2(int);
void sort_by_endTime(REKLAM*,int);
void find_max_profit(REKLAM*,int);

int main() {
	
	int n, i;
/*	printf("Reklam Veren Sayisini Giriniz : ");
	scanf("%d", &n);
	
	REKLAM *reklamlar;	
	reklamlar = (REKLAM*) malloc( n * sizeof(REKLAM) );
	
	get_info(reklamlar, n);*/
	
	n = get_total_sample_number();
	REKLAM *reklamlar = get_info_2(n);
	sort_by_endTime(reklamlar, n);
	find_max_profit(reklamlar, n);
	
	free(reklamlar);
	return 0;
}

void get_info(REKLAM* reklamlar, int n){
	
	int i;
		
	for(i=0;i<n;i++){
		printf("%d. Reklam Veren Icin 'StartTime' & 'Duration' 'Price' Bilgilerini Giriniz", i+1);
		printf("\n -->StartTime : "); scanf("%d", &reklamlar[i].startTime);		
		printf(" -->Duration  : "); scanf("%d", &reklamlar[i].duration);		
		printf(" -->Price     : "); scanf("%d", &reklamlar[i].value);				
	}
	
}

void sort_by_endTime(REKLAM* reklamlar, int n){
	
	int i, j, key;
	REKLAM tmp_reklam;
	
	for(i=1;i<n;i++){
		key = reklamlar[i].startTime + reklamlar[i].duration;
		tmp_reklam = reklamlar[i];
		j= i-1;
		
		while( j>=0 && key<reklamlar[j].startTime + reklamlar[j].duration ){
			reklamlar[j+1] = reklamlar[j];
			j--;
		}
		
		reklamlar[j+1] = tmp_reklam;
	}
		
}

void find_max_profit(REKLAM* reklamlar, int n){
	
	int *profit_array, *secilen_reklamlar, i, j, k=0, l=0;
	profit_array = (int*) malloc( (n+1) * sizeof(int));
	secilen_reklamlar = (int*) malloc( n * sizeof(int));

	profit_array[0] = 0;
	for(i=1;i<=n;i++)
		profit_array[i] = INT_MAX;
	
	for(i=1;i<=n;i++){
		
		j = k-1;
		while( (reklamlar[k].startTime < reklamlar[j].startTime + reklamlar[j].duration) && j>=0){
			j--;
		}
		
		if( j == -1 ){ // Mevcut reklam diðer tüm reklamlar ile çakýþýyorsa
			if( profit_array[0] + reklamlar[k].value > profit_array[i-1] ){
				profit_array[i] = profit_array[0] + reklamlar[k].value;
			}
			else{
				profit_array[i] = profit_array[i-1];
			}
		}
		else{// Mevcut reklamýn çakþtýðý son reklama ulaþtýðýmýzda
			if( profit_array[j+1] + reklamlar[k].value > profit_array[i-1])
				profit_array[i] = profit_array[j+1] + reklamlar[k].value;
			else
				profit_array[i] = profit_array[i-1];
		}
		
		k++;
	}
	
	i=n;
	k=0;
	while( i >= 0 ){
		
		j=i;
		while( profit_array[j] <= profit_array[j-1] &&  0<j )
			j--;
		
		i=j;	
		secilen_reklamlar[k] = i;
		k++;
		
		j--;
		while( reklamlar[i-1].startTime < reklamlar[j-1].startTime + reklamlar[j-1].duration  && 0<=j )
			j--;
		
		i = j;			
	}
	
	
	printf("Toplam Kazanç : %d\nYayinlanacak Reklamlar : ", profit_array[n]);
	
	for(i=0;i<k;i++){
		if(secilen_reklamlar[i] != 0)
			printf("%d, ", secilen_reklamlar[i]);
	}
		

	free(profit_array);
	free(secilen_reklamlar);
}


int get_total_sample_number(){
	
	char ch;
	int count = 1;
	FILE *f_sample;
	f_sample = fopen("Sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	while((ch=getc(f_sample)) != EOF)
		if(ch == '\n')
			count++;
	
	fclose(f_sample);
	return count;
}


REKLAM* get_info_2(int n){
	
	REKLAM *reklamlar;	
	reklamlar = (REKLAM*) malloc( n * sizeof(REKLAM) );
	
	int i;
	FILE *f_sample;
	f_sample = fopen("Sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	for(i=0;i<n;i++){
		fscanf(f_sample, "%d %d %d", &reklamlar[i].startTime , &reklamlar[i].duration, &reklamlar[i].value);
	}
	
	
	fclose(f_sample);
	
	return reklamlar;
}


