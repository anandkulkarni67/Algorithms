#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define infinity 999

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
			W[i][j] = 0;
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
read_graph(char *filename, int size, int G[][size]){
	char *pt, *line;
	size_t len = 0;
	ssize_t read;
	int i = 0, j = 0;
	FILE *fp = fopen(filename, "r");
	initialize_array(size, G);
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
					G[i][j] = a;
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
display_mst(int size, int *parent, int graph[size][size])
{
	int i = 0;
	printf("\n Minimum Spanning Tree :");
	for (i = 1; i < size; i++) {
		printf("\n edge %d,%d", parent[i] + 1, i + 1);
	}
}

/*
	This method is used to find the minimum entry from the array of entries.
*/
int
get_minimum(int size, int *queue, int *mst_set)
{
	int min = infinity, min_index;
	int i = 0;
	for (i = 0; i < size; i++) {
		if (mst_set[i] == 0 && queue[i] < min) {
			 min = queue[i];
			 min_index = i;
		}
	}
	return min_index;
}

/*
	This method contains the implementation of Prim's algorithm.
*/
void
prims_algorithm(int size, int graph[][size]){
	// This array stores the Minimum spanning tree
	int parent[size];
	int queue[size];
	// This array is used to represent set of vertices not yet included in MST
	int mst_set[size];  
 	int i = 0, count = 0, v = 0;
	// Initialize all entries from the queue to infinite.
	for (i = 0; i < size; i++) {
		queue[i] = infinity;
		mst_set[i] = 0;
	}
 
	// Starting with the first vertex.
	queue[0] = 0;
	parent[0] = -1;

	// The MST will have V vertices
	for (count = 0; count < size-1; count++)
	{
		// Pick minimum vertex which is not included in the minimum spanning tree yet.
		int u = get_minimum(size, queue, mst_set);
		mst_set[u] = 1;
		for (v = 0; v < size; v++) {
			// Update the queue only if graph[u][v] is smaller than queue[v]
			if (graph[u][v] && mst_set[v] == 0 && graph[u][v] <  queue[v]) {
				parent[v] = u;
				queue[v] = graph[u][v];
			}
		}
	}
	display_mst(size, parent, graph);
}

/*
	Main method.
*/
int main(int argc,char **argv){
	int i= 0, j = 0, k = 0, no_vertices = 0, v1_i = 0, v2_i = 0;
	char choice;
	if(validate_command_line_arguments(argc, argv)) {
		// checks if a file is empty.
		if(!(no_vertices = fetch_no_vertices(argv[1]))) {
			printf("\n File is empty or error occured while reading an input !!");
		}else {
			int graph[no_vertices][no_vertices];
			if(read_graph(argv[1], no_vertices, graph)) {
				prims_algorithm(no_vertices, graph);
			}
		}
	}
	printf("\n\n");
	return 0;
}
