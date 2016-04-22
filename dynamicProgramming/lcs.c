#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*
	This method is used to display the contents of a 2D character array.
*/
void
display_int_array(int m, int n, int M[m][n]){
	int i = 0, j = 0;
	for(i = 0;i < m; i++){
		printf("\n");
		for(j = 0; j < n; j++){
			printf("%5d ", M[i][j]);
		}
	}
}

/*
	This method is used to display the contents of a 2D character array.
*/
void
display_char_array(int m, int n, char M[m][n]){
	int i = 0, j = 0;
	for(i = 0;i < m; i++){
		printf("\n");
		for(j = 0; j < n; j++){
			printf("%5c ", M[i][j]);
		}
	}
}


/*
	Initialize all elements of an integer array to 0.
*/
void
initialize_int_array(int m, int n, int M[m][n]){
	int i = 0, j = 0;
	for(i = 0;i < m; i++){
		for(j = 0; j < n; j++){
			M[i][j] = 0;
		}
	}
}

/*
	Initialize all elements of a character array to 0.
*/
void
initialize_char_array(int m, int n, char M[m][n]){
	int i = 0, j = 0;
	for(i = 0;i < m; i++){
		for(j = 0; j < n; j++){
			M[i][j] = 0;
		}
	}
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
	This method is used to display the result of LCS algorithm.
*/
void
display_result(int m, int n, char M[m][n], char *x, char *y){
	char result[m];
	int size = 0, result_len = 0;
	m--;
	n--;
	while(m != 0 && n != 0) {
		if(M[m][n] == 'c') {
			m--;
			n--;
			result[size] = x[m];
			size++;
		}
		else if(M[m][n] == 'u') {
	                m--;
		}
		else {
	                n--;
		}
	}
	result_len = size;
	size--;
	printf("\n Longest common subsequence is : ");
	while(size >= 0){
		printf("%c", result[size]);
		size--;
	}
	printf(" %d", result_len);
}

/*
	This method contains an implementation of longest common subsequence algorithm.
*/
void
lcs_algorithm(char *x, char *y){
	int m=strlen(x);
	int n=strlen(y);
	int c[m][n];
	char b[m][n];
	int i = 0, j = 0;
	initialize_int_array(m, n, c);
	initialize_char_array(m, n, b);
	for(i = 1;i < m;i++) {
	        for(j = 1;j < n;j++)
	        {
                        if(x[i-1] == y[j-1])
                        {
                                c[i][j] = c[i-1][j-1] + 1;
				// 'c' is for cross direction.
                                b[i][j] = 'c';
                        }
                        else if(c[i-1][j] >= c[i][j-1])
                        {
                                c[i][j] = c[i-1][j];
				// 'u' is for upward direction.
                                b[i][j] = 'u';
                        }
                        else
                        {
                                c[i][j] = c[i][j-1];
				// 'l' is for left direction.
                                b[i][j] = 'l';
                        }
	        }
	}
	display_result(m, n, b, x, y);
}

/*
	Main method.
*/
int main(int argc,char **argv){
	int no_vertices = 0;
	char choice;
	char *seq1, *seq2;
	size_t len1 = 0, len2 = 0, read = 0;
	if(validate_command_line_arguments(argc, argv)) {
		FILE *fp = fopen(argv[1], "r");
		// reading input characher sequences.
		if((read = getline(&seq1, &len1, fp)) != -1 && (read = getline(&seq2, &len2, fp)) != -1) {
			lcs_algorithm(seq1, seq2);
		} else{
			printf("Either a line is emtpy or there was an error while reading input !!");
		}
		fclose(fp);
	}
	printf("\n\n");
	return 0;
}
