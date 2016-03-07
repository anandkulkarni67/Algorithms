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
	This method is used to find and display shortest path between two nodes.
*/
void path(int size, int P[][size],int q,int r){
	if (P[q][r]!=-1){
	             path(size, P, q, P[q][r]);
	             printf(" v%d ", P[q][r] + 1);
	             path(size, P, P[q][r], r);
	}
}

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

int
get_no_nodes(FILE *fp){
	int count = 0;
	char ch;
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

void
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
			int a = atoi(pt);
			W[i][j] = a;	
			j++;
			pt = strtok (NULL, ",");
		}
		i++;
    	}	
	fclose(fp);
}

int main(int argv,char **argc){
	int infinity = 500;
	int i= 0, j = 0, k = 0,v1 = 0, v2 = 0, no_nodes = 0;
	char choice;
	if(argv != 2){
		printf("\n\n Please enter valid number of arguments !!");
		printf("\n\n");
		return 0;
	}	
	FILE *fp = fopen(argc[1],"r");
	if(fp == NULL){
		printf("\n\n File not found !!");
		printf("\n\n");
		return 0;
	}
	no_nodes = get_no_nodes(fp);
	if(no_nodes == 0) {
		printf("\n\n File is empty or file could no be read !!");
		printf("\n\n");
		return 0;
	}
	int W[no_nodes][no_nodes];
	int D[no_nodes][no_nodes];
	int P[no_nodes][no_nodes];
	read_W_matrix(argc[1], no_nodes, W);
	floyd_algorithm(no_nodes, W, D, P);
	display_array(no_nodes, D);
	printf("\n");
	display_array(no_nodes, P);
	printf("\n");
	do{
		printf("\n\nPlease enter starting vertex (1...N) : ");
		scanf("%d", &v1);
		printf("\nPlease enter starting vertex (1...N) : ");
		scanf("%d", &v2);
		if(!(v1 > 0 && v1 <= no_nodes) || !(v2 > 0 && v2 <= no_nodes)){
			printf("\n Please enter valis values of vertices. !! (1..N, N = total number of nodes in a graph.)");
			printf("\n\n");
			return 0;
		}else{
			printf("\nShortest path between v%d and v%d is : ", v1, v2);
			printf(" v%d ", v1);
			path(no_nodes, P, (v1 - 1), (v2 - 1));
			printf(" v%d ", v2);
		}
		printf("\n\nDo you want to continue (y/n) ? : ");	
		scanf(" %c", &choice);
	}while((choice == 'y' || choice == 'Y'));
	printf("\n\n");
	return 0;
}
