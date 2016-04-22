#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define infinity 999

// This struct is used to store each of the edges of the graph.
struct Edge {
	int v1;
	int v2;
	int weight;
};

typedef struct Edge Edge;

/*
	This method is responsible for swaping two Edges in memory.
*/
void
swap(Edge *ip1, Edge *ip2){
	Edge temp;
	temp = *ip1;
	*ip1 = *ip2;
	*ip2 = temp;
}


/*
	This function chooses a random pivot and partiotions the array around the pivot element. It returns the index from the array where partition has occured.
*/
int partition(Edge *input_arr, int low, int high){
	//generating random index value between low and high as pivot.
	int pivotIndex = low + rand()%(high - low + 1);
	Edge pivot;
	int i = low - 1;
	int j;
	//pivot element
	pivot = input_arr[pivotIndex];
	swap(&input_arr[pivotIndex], &input_arr[high]);
	for (j = low; j < high; j++)
	{
		if (input_arr[j].weight < pivot.weight)
		{
		    i++;
		    swap(&input_arr[i], &input_arr[j]);
		}
	}
	swap(&input_arr[i + 1], &input_arr[high]);
	return i + 1;
}

/*
	Implementation of recursive randomized quick sort.
*/
void
randomized_quick_sort(Edge *input_arr, int low, int high){
	int j;
	if (low < high)
	{
		int p = partition(input_arr, low, high);
		randomized_quick_sort(input_arr, low, p - 1);
		randomized_quick_sort(input_arr, p + 1, high);
	}
}

/*
	This method is used to display the contents of 2D array.
*/
void
display_array(int size, int W[][size]){
	int i = 0;
	int j = 0;
	for(i=0;i<size; i++){
		printf("\n");
		for(j=0; j<size; j++){
			printf("%5d ", W[i][j]);
		}
	}
}

/*
	Initialize all elements of an array to 0.
*/
void
initialize_array(int size, int W[][size]){
	int i = 1;
	int j = 1;
	for(i=0;i<size; i++){
		for(j=0; j<size; j++){
			W[i][j] = -1;
		}
	}
}

/*
	This method validates whether a given string contains only digits from 0 to 9.
	Returns - 
	1 if given string contains only digits from 0 to 9.
	0 otherwise.
*/
int
is_number(char *pt){
	return (strspn(pt, "0123456789") == strlen(pt));
}

/*
	This method calculates number of nodes in adjacency matrix by counting number of lines present in input file.
*/
int
fetch_no_vertices(char *filename){
	int count = 0;
	char ch;
	FILE *fp = fopen(filename, "r");
	while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
	    count++;
	  }
	}
	return count;
}

/*
	This method reads the input file and populates the W matrix. This method also validates the data given in input file.
	It performs following validations :
	1. Validate if input file contains any invalid charactes (i.e. characters other then digits.).
	2. Validate if it has exptected number column values. (same as the number of row values.)
	3. Validate if value at every index is <= 500 because 500 is considered as infinity.
*/
int
read_graph(char *filename, int size, int W[][size]){
	char *pt, *line;
	size_t len = 0;
	ssize_t read;
	int i = 0, j = 0;
	FILE *fp = fopen(filename, "r");
	initialize_array(size, W);
	while ((read = getline(&line, &len, fp)) != -1) {
		pt = strtok (line,",");
		j = 0;
		while (pt != NULL) {
			// removes the trailing '\n' character from the last substring of a ',' seperated line.
			char *ch = strchr(pt,'\n');
			if (ch){
			      *ch = '\0';
			}
			if(is_number(pt) && strlen(pt)) {
			        int a = atoi(pt);
				// checks whether the read value is less than or equal to 500.
				if(a <= infinity){
					W[i][j] = a;
					j++;
					pt = strtok (NULL, ",");
				}else {
					return 0;
				}
			} else {
			        printf("\n Invalid Input. Atleast one invalid character detected !!");
				fclose(fp);
				return 0;
			}
		}
		if(j != size) {
			// checks whether the number of elements parsed from one line is exactly equal to the expected number.
			printf("\n Invalid input. Atleast one row has less/more elements than expected. (Exptected : %d) !!", size);
			fclose(fp);
			return 0;
		}
		i++;
    	}	
	// closing a file.
	fclose(fp);
	return 1;
}

/*
	This method validates the command line arguments.
	It performs following validations :
	1. Validate if number of arguments passed = 2.
	2. Validate if there exists a file with the given filename. Filename is provided as a command line argument.
*/
int
validate_command_line_arguments(int argc, char **argv){
	if(argc != 2){
		printf("\n Please enter valid number of arguments !!");
		return 0;
	}	
	FILE *fp = fopen(argv[1],"r");
	if(!fp){
		printf("\n File not found !!");
		return 0;
	}	
	return 1;
}

/*
	This method is used to display all edges of a minimum spanning tree.
*/
void
display_mst(int size, Edge *edges)
{
	int i = 0;
	printf("\n Minimum Spanning Tree :");
	for(i = 0; i < size - 1; i++){
		printf("\n edge %d,%d", edges[i].v1 + 1, edges[i].v2 + 1);
	}
}

/*
	This methos is used to find the root of a particular node in a tree.
*/
int find3(int i, int set[])
{
	int root = 0, parent =0;
	int node = 0;
	root = i;
	while(root != set[root]) {
		root = set[root];
	}
	node = i;
	while(node != root) {
		parent = set[root];
		set[node] = root;
		node = parent;
	}
	return root;
}

/*
	This method is used to merge two connected components/trees.
*/
void union3(int u,int v, int height[], int dset[])
{       
        if(height[u] == height[v]) {
		height[u] = height[u] + 1;
		dset[v] = u;
	}
	else {
		if(height[u] > height[v]) {
			dset[v] = u;
		}else {
			dset[u] = v;
		}
	}
}

/*
	This method contains the implementation of floyd algorithm.
*/
void
kruskal_algorithm(int size, int graph[][size]){
	Edge edges[size * size];
	int i = 0,j = 0, ecount = 0, mst_ecount = 0, count = 0;
	int x = 0, y = 0, u = 0, v = 0;
	int temp = 0;
	int dset[size];
	int height[size];
	Edge mst_edges[size - 1];
	// Initialize 'edges' array.
	for(i = 0;i < size; i++) {
		for(j = 0; j < size; j++) {
			Edge edge;
			edge.v1 = i;
			edge.v2 = j;
			edge.weight = graph[i][j];
			edges[count] = edge;
			count++;
		}
	}
	// Sort the edges based on weight of each edge.
	randomized_quick_sort(edges, 0, (size * size) - 1);
	// Initialize dis-joint set and height arrays.
	for(i = 0; i < size; i++) {
		dset[i] = i;
		height[i] = 0;
	}
	while(mst_ecount < size - 1) {
		x = edges[ecount].v1;
		y = edges[ecount].v2;
		// finding roots of x and y vertex.
		u = find3(x, dset);
		v = find3(y, dset);
		if(u != v){
			// merging trees with root u and v.
		        union3(u, v, height, dset);
			Edge edge;
			edge.v1 = edges[ecount].v1;
			edge.v2 = edges[ecount].v2;
			edge.weight = edges[ecount].weight;
			mst_edges[mst_ecount] = edge;
		        mst_ecount++;
		}
		ecount++;
	}
	display_mst(size, mst_edges);
}

/*
	Main method.
*/
int main(int argc,char **argv){
	int no_vertices = 0;
	char choice;
	if(validate_command_line_arguments(argc, argv)) {
		// checks if file is empty.
		if(!(no_vertices = fetch_no_vertices(argv[1]))) {
			printf("\n File is empty or error occured while reading an input !!");
		}else {
			int graph[no_vertices][no_vertices];
			if(read_graph(argv[1], no_vertices, graph)) {
				kruskal_algorithm(no_vertices, graph);
			}						
		}
	}
	printf("\n\n");
	return 0;
}
