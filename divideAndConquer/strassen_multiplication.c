#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
	This method initializes all elements of a matrix to 0.
*/
void
initialize(int size, int A[][size]){
	int i = 0;
	int j = 0;
	for(i = 0;i < size;i++) {
		for(j=0;j < size;j++) {
			A[i][j] = 0;
		}
	}
}

/*
	This method populated random elements between -10 and 10 in a given matrix.
*/
void 
randomize_matrix(int size, int A[][size]) {
	int i = 0;
	int j = 0;
	// intializing matrix A.
	initialize(size, A);
	for(i = 0;i < size;i++) {
		for(j=0;j < size;j++) {
			// generating random number between -10 and 10 (inclusive).
			A[i][j] = rand() % 21 + (-10);
		}
	}
}

/*
	This method displays a matrix on the terminal.
*/
void
display_matrix(int size, int W[][size]){
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0;i < size;i++){
		printf("\n");
		for(j=0; j < size; j++){
			printf(" %5d ", W[i][j]);
		}
	}
}

/*
	This method subtracts element of matrix B from corresponding element of matrix A.
*/
void
sub(int size, int A[][size], int B[][size], int C[][size]){
	int i = 0, j = 0;
	initialize(size, C);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

/*
	This method adds corresponding elements of two matrices.
*/
void
add(int size, int A[][size], int B[][size], int C[][size]) {
	int i = 0, j = 0;
	initialize(size, C);
        for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

/*
	This method splits a matrix.
*/
void
split(int o_size, int size, int O[][o_size], int N[][size], int si, int sj) {
	int i1 =0, i2 = si, j1 = 0, j2 = sj;
        for(i1 = 0; i1 < size; i1++) {
		j2 = sj;
		for(j1 = 0; j1 < size; j1++) {
			N[i1][j1] = O[i2][j2];
			j2++;
		}
		i2++;
	}
}

/*
	This method joins two matrices together.
*/
void
join(int o_size, int size, int C[][size], int P[][o_size], int si, int sj) {
	int i1=0, i2 = si, j1=0, j2 =sj;
        for(i1 = 0; i1 < size; i1++) {
		j2 = sj;
		for(j1 = 0; j1 < size; j1++) {
			P[i2][j2] = C[i1][j1];
			j2++;
		}
		i2++;
	}
} 

/*
	standard multiplication of 2x2 matrix.
*/
void
multiply(int size, int A[][size],int B[][size], int C[][size]){
	int i = 0, j = 0, k = 0;
	int sum = 0;
	initialize(size, C);
	for(i = 0;i < size; i++){
		for(j = 0; j < size; j++){
			sum = 0;
	                for(k = 0;k < size;k++){
               			sum = sum + A[i][k]*B[k][j];
			}
		        C[i][j]=sum;
		}
	}
}

void
strassen_algorithm(int size, int A[][size], int B[][size], int C[][size]){

	if(size == 2){
		multiply(size, A, B, C);
	}else {
		int A11[size/2][size/2];
		int A12[size/2][size/2];
		int A21[size/2][size/2];
		int A22[size/2][size/2];
		int B11[size/2][size/2];
		int B12[size/2][size/2];
		int B21[size/2][size/2];
		int B22[size/2][size/2];
		int C11[size/2][size/2];
		int C12[size/2][size/2];
	        int C21[size/2][size/2];
		int C22[size/2][size/2];
		int M1[size/2][size/2];
		int M2[size/2][size/2];
		int M3[size/2][size/2];
		int M4[size/2][size/2];
		int M5[size/2][size/2];
	        int M6[size/2][size/2];
		int M7[size/2][size/2];
		int T1[size/2][size/2];
		int T2[size/2][size/2];
		int T3[size/2][size/2];

		// Splitting matrix A into 4 equal parts.
		split(size ,size/2, A, A11, 0 , 0);
		split(size, size/2, A, A12, 0 , size/2);
		split(size, size/2, A, A21, size/2, 0);
		split(size, size/2, A, A22, size/2, size/2);

		// Splitting matrix B into 4 equal parts.
		split(size, size/2, B, B11, 0 , 0);
		split(size, size/2, B, B12, 0 , size/2);
		split(size, size/2, B, B21, size/2, 0);
		split(size, size/2, B, B22, size/2, size/2);

		// Calculating M1 to M7 values.
		add(size/2, A11, A22, T1);
		add(size/2, B11, B22, T2);
		// M1 = (A11 + A22) * (B11 + B22)  
		strassen_algorithm(size/2, T1, T2, M1);
		add(size/2, A21, A22, T1);
		// M2 = (A21 + A22) * B11
		strassen_algorithm(size/2, T1, B11, M2);
		sub(size/2, B12, B22, T1);
		// M3 = A11 * (B12 - B22)
		strassen_algorithm(size/2, A11, T1, M3);
		sub(size/2, B21, B11, T1);
		// M4 = A22 * (B21 - B11)
		strassen_algorithm(size/2, A22, T1, M4);
		add(size/2, A11, A12, T1);
		// M5 = (A11 + A12) * B22
		strassen_algorithm(size/2, T1, B22, M5);
		sub(size/2, A21, A11, T1);
		add(size/2, B11, B12, T2);
		// M6 = (A21 - A11) * (B11 + B12)
		strassen_algorithm(size/2, T1, T2, M6);
		sub(size/2, A12, A22, T1);
		add(size/2, B21, B22, T2);
		// M7 = (A12 - A22) * (B21 + B22)
		strassen_algorithm(size/2, T1, T2, M7);

		// Combining results of M1 to M7 to form 4 sub matrices.
		add(size/2, M1, M4, T1);
		sub(size/2, T1, M5, T2);
		add(size/2, T2, M7, C11);
		add(size/2, M3, M5, C12);
		add(size/2, M2, M4, C21);
		add(size/2, M1, M3, T1);
		sub(size/2, T1, M2, T2);
		add(size/2, T2, M6, C22);

		// joining 4 sub matrices to form a single result matrix.
		join(size, size/2, C11, C, 0, 0);
		join(size, size/2, C12, C, 0, size/2);
		join(size, size/2, C21, C, size/2, 0);
		join(size, size/2, C22, C, size/2, size/2);
	}
}

/*
	Using standard matrix multiplication algorithm with time complexity of O(n^3).
*/
void
brute_force_algo(int size, int A[][size], int B[][size], int C[][size]) {
	int i = 0, j = 0, k = 0;
	int sum = 0;
	initialize(size, C);
	for(i = 0;i < size; i++){
		for(j = 0; j < size; j++){
			sum = 0;
	                for(k = 0;k < size;k++){
               			sum = sum + A[i][k]*B[k][j];
			}
		        C[i][j]=sum;
		}
	}
}

/*
	This method  resultant matrices generated by applying strassen's algorithm and brute force algorithm.
	Returns -
	1 if results are identical.
	0 otherwise.
*/
int
equal(int size, int A[][size], int B[][size]) {
	int i = 0,j =0;
	for(i = 0;i < size; i++){
		for(j = 0; j < size; j++) {
			if(A[i][j] != B[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

/*
	This method checks whether a method contains only digits (0-9).
*/
int
is_number(char *pt){
	return (strspn(pt, "0123456789") == strlen(pt));
}

/*
	This method validates the input.
	It performs following validations :
	1. Validate if input is a valid number i.e if it contains only digits (0-9).
	2. Validate if input number = 2^k where k is positive integer.
	Returns -
	1 if input satisfies above conditions.
	0 otherwise.
*/
int
validate_input(char *ip){
	int n = 0;
	if(!is_number(ip)){
		printf("\n Invalid value. Please enter an integer value (n = 2^k, k > 0) !!");
		return 0;
	}
	n = atoi(ip);
	if(((n < 2) || (n & (n - 1)))){
		printf("\n Please enter a valid number !! (n = 2^k, k > 0)");
		return 0;
	}
	return 1;
}


/*
	Main method.
*/
int main(){
	srand (time(NULL));
	int n;
	char ip[10];
	
	// Taking an input from the user for the value of n.
	printf("\n Please enter a value of n : ");
	scanf("%s",ip);
	
	if(validate_input(ip)){
		n = atoi(ip);
		int A[n][n];
		int B[n][n];
		int R1[n][n];
		int R2[n][n];

		// Populating matrices A and B with random numbers between -10 and 10.
		randomize_matrix(n, A);
		randomize_matrix(n, B);
	
		printf("\n Matrix A is : ");
		display_matrix(n, A);
		printf("\n\n Matrix B is : ");
		display_matrix(n, B);

		// apply strassen's algorithm.
		strassen_algorithm(n, A, B, R1);
	
		// apply standard matrix multiplication algorithm.
		brute_force_algo(n, A, B, R2);

		if(equal(n, R1,R2)){
			printf("\n\n Resultant matrix R is : ");
			display_matrix(n, R1);
		}
	}
	printf("\n\n");
	return 0;
}
