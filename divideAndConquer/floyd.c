#include<stdio.h>
#include<string.h>
#define NO_NODES 5

/*
	This method is used to display the contents of 2D array.
*/
void
display_array(int W[NO_NODES][NO_NODES]){
	int i = 0;
	int j = 0;
	for(i=0;i<NO_NODES; i++){
		printf("\n");
		for(j=0; j<NO_NODES; j++){
			printf("%d ", W[i][j]);
		}
	}
}

/*
	This method copies all elements from one array to another.
*/
void
copy_array(int W[NO_NODES][NO_NODES], int D[NO_NODES][NO_NODES]){
	int i = 1;
	int j = 1;
	for(i=0;i<NO_NODES; i++){
		for(j=0; j<NO_NODES; j++){
			D[i][j] = W[i][j];
		}
	}
}

/*
	Initialize all elements of an array to 0.
*/
void
initialize_array(int W[NO_NODES][NO_NODES]){
	int i = 1;
	int j = 1;
	for(i=0;i<NO_NODES; i++){
		for(j=0; j<NO_NODES; j++){
			W[i][j] = -1;
		}
	}
}

/*
	This method is used to find and display shortest path between two nodes.
*/
void path(int P[NO_NODES][NO_NODES],int q,int r){
	if (P[q][r]!=-1){
	             path(P, q, P[q][r]);
	             printf(" v%d ", P[q][r] + 1);
	             path(P, P[q][r], r);
	}
}

void
floyd_algorithm(int size, int W[][size], int D[][size], int P[][size]){
	int i= 0, j = 0, k = 0;
	copy_array(W, D);
	initialize_array(P);	
	for(k = 0; k<NO_NODES; k++){
		for(i = 0; i<NO_NODES; i++){
			for(j = 0; j<NO_NODES; j++){
				if(D[i][j] > (D[i][k] + D[k][j])){
					D[i][j] = (D[i][k] + D[k][j]);
					P[i][j] = k;
				}
			}
		}
	}
}

int main(){
	int infinity = 500;
	int i= 0, j = 0, k = 0,v1 = 0, v2 = 0, no_nodes = 5;
	char choice;
	int W[NO_NODES][NO_NODES] = {{0, 1, infinity, 1, 5}, {9, 0, 3, 2, infinity}, {infinity, infinity, 0, 4, infinity}, {infinity, infinity, 2, 0, 3}, {3, infinity, infinity, infinity, 0}};
	int D[NO_NODES][NO_NODES];
	int P[NO_NODES][NO_NODES];
	floyd_algorithm(NO_NODES, W, D, P);
	display_array(D);
	printf("\n");
	display_array(P);
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
			path(P, (v1 - 1), (v2 - 1));
			printf(" v%d ", v2);
		}
		printf("\n\nDo you want to continue (y/n) ? : ");	
		scanf(" %c", &choice);
	}while((choice == 'y' || choice == 'Y'));
	printf("\n\n");
	return 0;
}
