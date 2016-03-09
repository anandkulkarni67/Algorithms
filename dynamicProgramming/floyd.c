#include<stdio.h>
#include<stdlib.h>
#include <string.h>


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
			printf("%d ", W[i][j]);
		}
	}
}

/*
	This method copies all elements from one array to another.
*/
void
copy_array(int size, int W[][size], int D[][size]){
	int i = 1;
	int j = 1;
	for(i=0;i<size; i++){
		for(j=0; j<size; j++){
			D[i][j] = W[i][j];
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
fetch_no_nodes(char *filename){
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
read_W_matrix(char *filename, int size, int W[][size]){
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
				if(a <= 500){
					W[i][j] = a;
					j++;
					pt = strtok (NULL, ",");
				}else {
					printf("\n Invalid Input. please enter weights <= 500. Weight = 500 is considered as infinity !!");
					fclose(fp);
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
	This method is used to find and display shortest path between two nodes.
*/
void path(int size, int P[][size],int q,int r){
	if (P[q][r]!=-1){
	             path(size, P, q, P[q][r]);
	             printf(" v%d ", P[q][r] + 1);
	             path(size, P, P[q][r], r);
	}
}

/*
	This method contains the implementation of floyd algorithm.
*/
void
floyd_algorithm(int size, int W[][size], int D[][size], int P[][size]){
	int i= 0, j = 0, k = 0;
	copy_array(size, W, D);
	initialize_array(size, P);	
	for(k = 0; k<size; k++){
		for(i = 0; i<size; i++){
			for(j = 0; j<size; j++){
				if(D[i][j] > (D[i][k] + D[k][j])){
					D[i][j] = (D[i][k] + D[k][j]);
					P[i][j] = k;
				}
			}
		}
	}
}

/*
	Main method.
*/
int main(int argc,char **argv){
	int infinity = 500;
	int i= 0, j = 0, k = 0, no_nodes = 0, v1_i = 0, v2_i = 0;
	char v1[3], v2[3];
	char choice;
	if(validate_command_line_arguments(argc, argv)) {
		// checks if file is empty.
		if(!(no_nodes = fetch_no_nodes(argv[1]))) {
			printf("\n File is empty or error occured while reading a input !!");
		}else {
			int W[no_nodes][no_nodes];
			if(read_W_matrix(argv[1], no_nodes, W)) {
				int D[no_nodes][no_nodes];
				int P[no_nodes][no_nodes];			
				display_array(no_nodes, W);
				floyd_algorithm(no_nodes, W, D, P);
				do{
					printf("\n\n Please enter a starting vertex (1...N) : ");
					scanf("%s", v1);
					printf("\n Please enter an ending vertex (1...N) : ");
					scanf("%s", v2);
					// validates if the given input is a number.
					if(!(is_number(v1) && is_number(v2))) {
						printf("\n Please enter valid integer values of vertices !! (1..N, where N = total number of nodes in a graph.)");	
					}else {
						v1_i = atoi(v1);
						v2_i = atoi(v2);
						// validates if the given input is within appropriate range.
						if(!(v1_i > 0 && v1_i <= no_nodes) || !(v2_i > 0 && v2_i <= no_nodes)){
							printf("\n Please enter valid values of vertices !! (1..N, where N = total number of nodes in a graph.)");	
						} else {
							printf("\n Shortest path between v%d and v%d is : ", atoi(v1), atoi(v2));
							printf(" v%d ", v1_i);
							path(no_nodes, P, (v1_i - 1), (v2_i - 1));
							printf(" v%d ", v2_i);
						}
					}
					printf("\n\n Do you want to continue ? (press 'y'/'Y' to continue or any other key to quit.) : ");
					scanf(" %c", &choice);
				}while((choice == 'y' || choice == 'Y'));				
			}
		}
	}
	printf("\n\n");
	return 0;
}
