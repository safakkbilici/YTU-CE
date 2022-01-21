#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct path{
	int *cities;
	int num_of_cities;
	int cost_of_flights;
	int total_flight_time;
	struct path* next;
}PATH;

typedef struct flight{
	char from[20];
	char to[20];
	int hour;
	int minute;
	int price;
}FLIGHT;

typedef struct node{
	int vertex;//destination
	int hour;
	int minute;
	int price;
	struct node* next;
}NODE;

typedef struct graph{
	int numVertex;
	int* visited;
	struct node** AdjList;
}GRAPH;

PATH* create_path(int);
NODE* create_node(int,FLIGHT);
GRAPH* create_graph(int);				//initilization of graph
void add_edge(GRAPH*,int,int,FLIGHT);			//adding two given edges and their weightes
void print_graph(GRAPH*);				//for printing the representation of the graph to the console
PATH* find_path(GRAPH*,PATH*,int*,int,int,int);		//finding al possible paths between two nodes and save them in a linked list 
char** get_total_city_number(int*); 			//return matrix with city names in it and return number of cities with a pointer
void add_all_edges(GRAPH*,char**);			//reading text and adding all edges to initialized graph
void calculate_time_and_cost(GRAPH*,PATH*);		//after finding possible paths, to calculate their cost and time
void sort_by_time(PATH**,int);				//for sorting the linked list for paths by their time
void sort_by_cost(PATH**,int);				//for sorting the linked list for paths by their cost
PATH* swap(PATH*,PATH*);				//swapping two linked list nodes
void print_flights(PATH*,int,char**,int,int);		//print paths within given constraints

int main(){
	
	int i, count, from, to, transit, timeORcost, terminate = 0;		//count-> total path   
										//from->source city of the flight   to->destnation city of the flight
										//transit->max transit flights of connection given by user
										//timeORcost->for user to decide sorting type
	int *path, path_index, num_of_cities;					//path-> to save possible roats temporarily 
	char **cities;								//matrix for storing city names
	GRAPH *g1;								
	PATH *p1 = NULL, *tmp; 							//head(pointer) of the linked list that stores all possible paths and a temporary pointer(tmp)
	
	//Read text and initiliaze the graph
	cities = get_total_city_number(&num_of_cities);
	g1 = create_graph(num_of_cities);
	add_all_edges(g1, cities);
	
	//Allocate memory for path and set path_index to zero
	path = malloc(num_of_cities * sizeof(int));
	path_index = 0;
	
	system("title BLM3021_Assignment_3");
	while(!terminate){
		printf("\t\t\tAll Cities Listed Down Below\n");
		
		for(i=0;i<num_of_cities;i++){
			printf("%d-->%s\n", i, cities[i]);
		}
		
		printf("\nPlease Choose Cities With It`s Given Index Above!!\n");
		printf(" From : "); scanf("%d", &from);
		printf(" To   : "); scanf("%d", &to);
		printf("\nPlease Specify, Up to How Many Transit(Connection) Do You Want to List Flights : "); scanf("%d",&transit);
		printf("\nPlease Specify, How do You Wish to List Flights\n For By Time, Please Enter 1\n For By Cost, Please Enter 0\n Your Choice : "); scanf("%d",&timeORcost);
		
		
		p1 = find_path(g1, p1, path, path_index, from, to);
		calculate_time_and_cost(g1, p1);
		
		//Counting how many possible path do we have for 'from'->'to'
		tmp = p1;
		count = 0;
		while(tmp){
			count++;
			tmp = tmp->next;
		}
		system("cls");
		print_flights(p1, count, cities, transit, timeORcost);
		
		printf("\n\nFor Listing New Flights,       Please Enter 0\nFor Terminating the Programme, Please Enter 1\n Your Choice : "); scanf("%d", &terminate);
		system("cls");
	}
	
	
	//free allocated memory!!
	
	for(i=0;i<num_of_cities;i++)
		free(cities[i]);
	free(cities);
	
	free(path);					
	
	while(p1!=NULL){
		tmp = p1;
		p1 = p1->next;
		free(tmp);	
	}
	
	for(i=0;i<g1->numVertex;i++)
		free(g1->AdjList[i]);
	free(g1->AdjList);
	free(g1->visited);
	free(g1);
	
	return 0;
}

PATH* create_path(int path_index){
	
	PATH *p = malloc(sizeof(PATH));
	p->cities = malloc( (path_index+1) * sizeof(int));
	p->num_of_cities = path_index + 1;
	p->cost_of_flights = 0;
	p->total_flight_time = 0;
	p->next = NULL;
	
	return p;
}

NODE* create_node(int V, FLIGHT flight){
	
	NODE *newNode = malloc(sizeof(NODE));
	newNode->vertex = V;
	newNode->hour = flight.hour;
	newNode->minute = flight.minute;
	newNode->price = flight.price;
	newNode->next = NULL;
	
	return newNode;
}

GRAPH* create_graph(int num_of_vertexes){

	int i;
	
	GRAPH *g = malloc(sizeof(GRAPH));
	if(g == NULL){
		perror("An Error Occurred at Graph Initialization : ");
		exit -1;
	}
	
	g->numVertex = num_of_vertexes;
	g->visited = calloc(num_of_vertexes, sizeof(int));  // Initialize "visited" array and set all elements to 0 with the help of calloc
	g->AdjList = malloc(num_of_vertexes * sizeof(NODE*));
	
	for(i=0;i<num_of_vertexes;i++)
		g->AdjList[i] = NULL;
	
	return g;
}

void add_edge(GRAPH* graph, int from, int to, FLIGHT flight){
	
	NODE *newNode = create_node(to, flight);
	
	// Add edge "from" -> "to". New node added to head(not the end of the list)
	newNode->next = graph->AdjList[from];
	graph->AdjList[from] = newNode;
	
	
	//If graph is UNDIRECTED, add edge "to" -> "from". New node added to head(not the end of the list)
	newNode = create_node(from, flight);
	newNode->next = graph->AdjList[to];
	graph->AdjList[to] = newNode;
}

void print_graph(GRAPH* graph){
	
	int i;	
	NODE* tmp;
	
	for(i=0;i<graph->numVertex;i++){
		
		tmp = graph->AdjList[i]; 
		printf("%d -> ", i);
		while(tmp){
			printf("%d -> ", tmp->vertex);
			tmp = tmp->next;
		}
		printf("NULL\n");			
	}
	
//	free(tmp);
}

PATH* find_path(GRAPH* graph, PATH* all_paths, int* path, int path_index, int from, int to){

	if(from == to){
		
		int i;
		PATH *newPath = create_path(path_index);
		newPath->next = all_paths;
		all_paths = newPath;
		
		for(i=0;i<path_index;i++){
			newPath->cities[i] = path[i];
		}
		newPath->cities[i] = to;	
	}	
	else{
		graph->visited[from] = 1;
		path[path_index] = from;
		path_index++;
		
		NODE* tmp = graph->AdjList[from];
		
		while(tmp){
			if(!graph->visited[tmp->vertex])
				all_paths = find_path(graph, all_paths, path, path_index, tmp->vertex, to);
			tmp = tmp->next;
		}
		
		graph->visited[from] = 0;
		path_index--;
		free(tmp);
	}
	return all_paths;
}

char** get_total_city_number(int* num_of_cities){
	
	
	//ch-> for reading char one by one from text
	//tmp-city-> storing the current city that have been read from text
	//cities[][]-> storing all cities
	char ch, *tmp_city, **cities;
	
	//count-> number of cities(will be calculated at end of the func.)
	//n-> The probability of the number of cities being the highest
	//i-> index for tmp_city 
	//j-> index for which city have been read from the line (each line has 2 cities)
	//k-> index for checking current city. Whether it is in the cities matrix or not
	int i, j, k, count = 0, n = 1;  
	
	FILE *f_sample;
	f_sample = fopen("sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	while((ch=getc(f_sample)) != EOF)
		if(ch == '\n')
			n++;
	rewind(f_sample); //file pointer at the begining of the text

	//Allocation of the cities matrix
	n = 2*n;	
	cities = (char**) calloc(n, sizeof(char*));
	if(cities == NULL){
		perror("Could Not Allocate : ");
		exit -1;
	}
	
	for(i=0;i<n;i++){
		cities[i] = calloc(256, sizeof(char));
	}

	tmp_city = calloc(256, sizeof(char));
	//read cities of the first flight from text and save them into "cities" matrix
	for(j=0;j<2;j++){
		i= 0;
		while((ch=getc(f_sample)) != ' '){
			tmp_city[i] = ch;
			i++;
		}
		strncpy(cities[count], tmp_city, 256);	
		memset(tmp_city, '\0', sizeof(tmp_city));
		count++; 
	}
	
	while((ch=getc(f_sample)) != '\n'); //file pointer -> end of the line
	
	//read remaining flights from txt and if any of the cities is different 
	//from the rest of the cities in the "cities" matrix, save them into the matrix
	while(ch != EOF){
		
		//read two(one city for one iteration) cities and compare one by one 
		for(j=0;j<2;j++){
			i= 0;
			while((ch=getc(f_sample)) != ' '){
				tmp_city[i] = ch;
				i++;
			}
			
			k = 0;
			while( (k < count) && (strcmp(cities[k], tmp_city) != 0) ) //compare current city with other cities
				k++;
			
			//If current city is not in the matrix, save it into matrix	
			if(k==count){
				strncpy(cities[count], tmp_city, 256);
				count++; 
			}
			memset(tmp_city, '\0', sizeof(tmp_city));	
		}
		
		while((ch=getc(f_sample)) != '\n' && ch != EOF);
	}	

	*num_of_cities = count;

	// free tmp_city memory
	free(tmp_city);

	//close file pointer
	fclose(f_sample);
	return cities;
}

void add_all_edges(GRAPH* graph, char** cities){
	
	FLIGHT flight;
	
	int i, k, from, to, n;
	char ch;
	FILE *f_sample;
	f_sample = fopen("sample.txt", "r");
	
	if(f_sample == NULL){
		perror("Could Not Open the File ");
		exit -1;
	}
	
	
	while((ch=getc(f_sample)) != EOF)
		if(ch == '\n')
			n++;
	rewind(f_sample); //file pointer at the begining of the text
	
	for(i=0;i<n+1;i++){
		fscanf(f_sample, "%s %s %d %d %d", flight.from , flight.to, &flight.hour, &flight.minute, &flight.price);
		
		//find which index 'flight.from' is saved in the 'cities' matrix
		k=0;
		while(strcmp(cities[k], flight.from) != 0)
			k++;
		from = k;
		
		//find which index 'flight.to' is saved in the 'cities' matrix
		k=0;
		while(strcmp(cities[k], flight.to) != 0)
			k++;
		to = k;
		
		//add them to the graph	
		add_edge(graph,from,to,flight);
	}
	
	
	fclose(f_sample);
	
}

void calculate_time_and_cost(GRAPH* graph, PATH* all_paths){
	
	int i;
	
	PATH *tmp_path;
	tmp_path = all_paths;
	
	NODE *tmp_node;
	
	while(tmp_path){
		for(i=0;i<tmp_path->num_of_cities-1;i++){
			tmp_node= graph->AdjList[tmp_path->cities[i]];
			while((tmp_node->vertex != tmp_path->cities[i+1]) && tmp_node){
				tmp_node = tmp_node->next;
			}
			if(tmp_node->vertex == tmp_path->cities[i+1]){
				tmp_path->cost_of_flights = tmp_path->cost_of_flights + tmp_node->price; //add current cost of flight to cost of previous flight(s)
				tmp_path->total_flight_time = tmp_path->total_flight_time + tmp_node->minute + (60 * tmp_node->hour); //add curent flight time(in minutes) to total time(in minutes) of previous flight(s)
				if(i > 1)
					tmp_path->total_flight_time = tmp_path->total_flight_time + 60;
			}
			else{
				printf("\n\n\n bir sikinti var \n\n\n");
			}
		}
		tmp_path = tmp_path->next;	
	}
	
}

void sort_by_time(PATH** all_paths, int count){
	
	int i, j, swapped = 1;
	PATH** tmp_head;
		
	for(i=0;i<=count;i++){
		swapped = 0;
		tmp_head = all_paths;
		
		for(j=0;j<count-1-i;j++){
			
			PATH* p1 = *tmp_head;
			PATH* p2 = p1->next;
			
			if(p1->total_flight_time > p2->total_flight_time){
				*tmp_head = swap(p1, p2);
				swapped = 1;
			}
			tmp_head = &(*tmp_head)->next;
		}
		if(swapped == 0)
			return;
	}
}

void sort_by_cost(PATH** all_paths, int count){
	
	int i, j, swapped = 1;
	PATH** tmp_head;
		
	for(i=0;i<=count;i++){
		swapped = 0;
		tmp_head = all_paths;
		
		for(j=0;j<count-1-i;j++){
			
			PATH* p1 = *tmp_head;
			PATH* p2 = p1->next;
			
			if(p1->cost_of_flights > p2->cost_of_flights){
				*tmp_head = swap(p1, p2);
				swapped = 1;
			}
			tmp_head = &(*tmp_head)->next;
		}
		if(swapped == 0)
			return;
	}
}

PATH* swap(PATH* ptr1, PATH* ptr2){
	
	PATH* tmp; 
	
	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;

	return ptr2;	
}

void print_flights(PATH* all_paths, int path_count, char** cities, int num_of_transit, int sortBy_timeORcost){
	
	if(all_paths == NULL){
		printf("There is not any flights between the cities you selected");
		return;
	}
	
	PATH* tmp;
	int i, control = 0;
	//  sortBy_timeORcost = 1 for TIME  
	//  sortBy_timeORcost = 0 for COST
	if(sortBy_timeORcost){
		//sort by TIME
		sort_by_time(&all_paths, path_count);
		tmp = all_paths;
		while(tmp){
			if((tmp->num_of_cities - 2) <= num_of_transit){
				
				if(tmp->num_of_cities == 2){
					//DIRECT FLIGHT
					printf("\n---------------------------------------------------\n");
					printf("FROM-->%s\n",cities[tmp->cities[0]]); //SOURCE
					printf("TO-->%s\n",cities[tmp->cities[1]]); //DESTINATION
					printf("STOPS-->NONE");
					printf("\nHOUR : %d \nMINUTE : %d\nCOST : %d", (tmp->total_flight_time / 60), (tmp->total_flight_time % 60), tmp->cost_of_flights);
				}
				else if(tmp->num_of_cities > 2){
					//NON-DIRECT FLIGHT
					printf("\n----------------------------------------------------\n");
					i = 0;
					printf("FROM-->%s\n",cities[tmp->cities[i]]); //SOURCE
					
					i = tmp->num_of_cities - 1;
					printf("TO-->%s\n",cities[tmp->cities[i]]); //DESTINATION
					
					printf("STOPS-->");
					for(i=1;i<tmp->num_of_cities - 1;i++){
						printf("%s ",cities[tmp->cities[i]]); //STOPS
					}
					
					printf("\nHOUR : %d \nMINUTE : %d\nCOST : %d", (tmp->total_flight_time / 60 + 1), (tmp->total_flight_time % 60), tmp->cost_of_flights);	
				}
			}
			tmp = tmp->next;
		}
	}
	else{
		//sort by COST
		sort_by_cost(&all_paths, path_count);
		tmp = all_paths;
		while(tmp){
			if((tmp->num_of_cities - 2) <= num_of_transit){
					
				if(tmp->num_of_cities == 2){
					//DIRECT FLIGHT
					printf("\n---------------------------------------------------\n");
					printf("FROM-->%s\n",cities[tmp->cities[0]]); //SOURCE
					printf("TO-->%s\n",cities[tmp->cities[1]]); //DESTINATION
					printf("STOPS-->NONE");
					printf("\nHOUR : %d \nMINUTE : %d\nCOST : %d", (tmp->total_flight_time / 60), (tmp->total_flight_time % 60), tmp->cost_of_flights);
				}
				else if(tmp->num_of_cities > 2){
					//NON-DIRECT FLIGHT
					printf("\n----------------------------------------------------\n");
					i = 0;
					printf("FROM-->%s\n",cities[tmp->cities[i]]); //SOURCE
					
					i = tmp->num_of_cities - 1;
					printf("TO-->%s\n",cities[tmp->cities[i]]); //DESTINATION
					
					printf("STOPS-->");
					for(i=1;i<tmp->num_of_cities - 1;i++){
						printf("%s ",cities[tmp->cities[i]]); //STOPS
					}
					
					printf("\nHOUR : %d \nMINUTE : %d\nCOST : %d", (tmp->total_flight_time / 60 + 1), (tmp->total_flight_time % 60), tmp->cost_of_flights);	
				}
			}
			tmp = tmp->next;
		}
	}
}

