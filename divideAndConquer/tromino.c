#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int no = 1;

/*
	This method generates a random value between 0 and the given input number (inclusive).
	Returns -
	random value.
*/
int
generate_random_value(int range){
	int val = 0;
	val = rand() % range + 0;
	return val;
}

/*
	This method displays the matrix on terminal. It prints 'X' where a hole is placed.
*/
void
display_matrix(int size, int W[][size]){
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0;i < size;i++){
		printf("\n");
		for(j=0; j < size; j++){
			if(W[i][j] == -1){
				printf("%5c",'X');
			}else {
				printf("%5d", W[i][j]);
			}
		}
	}
}

/*
	Tromino algorithm implementation.
*/
void
tromino_algo(int x_min, int y_min, int x_max, int y_max, int x_mis, int y_mis, int size,int m_size, int M[][m_size]){
	//printf("\n\nx_min : %d, y_min : %d, x_max : %d, y_max : %d",x_min, y_min, x_max, y_max);
	//printf("\nx_miss : %d, y_miss : %d", x_mis, y_mis);
	if(size == 2){
		if(x_min == x_mis) {
			if(y_min == y_mis) {
				M[x_min][y_min + 1] = no;
				M[x_min + 1][y_min] = no;
				M[x_min + 1][y_min + 1] = no;
			} else {
				M[x_min][y_min] = no;
				M[x_min + 1][y_min] = no;
				M[x_min + 1][y_min + 1] = no;
			}
		}else {
			if(y_min == y_mis) {
				M[x_min][y_min] = no;
				M[x_min][y_min + 1] = no;
				M[x_min + 1][y_min + 1] = no;
			} else {
				M[x_min][y_min] = no;
				M[x_min][y_min + 1] = no;
				M[x_min + 1][y_min] = no;
			}
		}
		no++;
		/*printf("\n\n");
		printf("\n%d %d", M[x_cord][y_cord], M[x_cord][y_cord + 1]);
		printf("\n%d %d", M[x_cord + 1][y_cord], M[x_cord + 1][y_cord + 1]);*/
		return;
	}	
	
	int x_cent = 0, y_cent = 0, x11_miss = 0, y11_miss = 0, x12_miss = 0, y12_miss = 0, x21_miss = 0, y21_miss = 0, x22_miss = 0, y22_miss = 0;
	x_cent = x_min + (x_max - x_min) / 2;
	y_cent = y_min + (y_max - y_min) / 2;

	//printf("\n\nx_cent : %d",x_cent);
	//printf(" y_cent : %d",y_cent);
	if(x_mis < x_cent){
		x21_miss = x_cent;
		y21_miss = y_cent - 1;
		x22_miss = x_cent;
		y22_miss = y_cent;
		M[x21_miss][y21_miss] = no;
		M[x22_miss][y22_miss] = no;
		if(y_mis < y_cent){
			x11_miss = x_mis;
			y11_miss = y_mis;
			x12_miss = x_cent - 1;
			y12_miss = y_cent;
			M[x12_miss][y12_miss] = no;
		}else {
			x12_miss = x_mis;
			y12_miss = y_mis;
			x11_miss = x_cent - 1;
			y11_miss = y_cent - 1;
			M[x11_miss][y11_miss] = no;
		}
	}else {
		x11_miss = x_cent - 1;
		y11_miss = y_cent - 1;
		x12_miss = x_cent - 1;
		y12_miss = y_cent;
		M[x11_miss][y11_miss] = no;
		M[x12_miss][y12_miss] = no;
		if(y_mis < y_cent){
			x21_miss = x_mis;
			y21_miss = y_mis;
			x22_miss = x_cent;
			y22_miss = y_cent;
			M[x22_miss][y22_miss] = no;
		}else {
			x22_miss = x_mis;
			y22_miss = y_mis;
			x21_miss = x_cent;
			y21_miss = y_cent - 1;
			M[x21_miss][y21_miss] = no;
		}
	}
	no++;
	/*printf("\n");
	printf("\nx11_miss : %d",x11_miss);
	printf("\ny11_miss : %d",y11_miss);
	printf("\nx12_miss : %d",x12_miss);
	printf("\ny12_miss : %d",y12_miss);
	printf("\nx21_miss : %d",x21_miss);
	printf("\nx21_miss : %d",y21_miss);
	printf("\nx22_miss : %d",x22_miss);
	printf("\ny22_miss : %d",y22_miss);*/

	/*
	          
		first quadrant -  11 | 12 - second quadrant
				 ---------
		third quadrant -  21 | 22 - fourth quadrant
		 
	*/
	tromino_algo(x_min, y_min, x_min + (x_max-x_min)/2, y_min + (y_max-y_min)/2, x11_miss, y11_miss, size / 2, m_size, M);
	tromino_algo(x_min, y_cent, x_min + (x_max-x_min)/2, y_max, x12_miss, y12_miss, size / 2, m_size, M);
	tromino_algo(x_cent, y_min, x_max, y_min + (y_max-y_min)/2, x21_miss, y21_miss, size/2, m_size, M);
	tromino_algo(x_cent, y_cent, x_max, y_max, x22_miss, y22_miss, size/2, m_size, M);
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
	2. Validate if input is not equal to 0.
	Returns -
	1 if input satisfies above conditions.
	0 otherwise.
*/
int
validate_input(char *ip){
	int k = 0;
	if(!is_number(ip)){
		printf("\n Invalid value. Please enter an integer value (k > 0) !!");
		return 0;
	}
	k = atoi(ip);
	if(k == 0){
		printf("\n Invalid value. Please enter an integer value greater than 0 !!");		
		return 0;
	}
	return 1;
}

/*
	Main method.
*/
int
main()
{
	srand(time(NULL));
	int k = 0, size = 0, x_mis = 0, y_mis = 0;
	char ip[10];
	printf("\n Please enter a value of k (k > 0) : ");
	scanf("%s",ip);
	if(validate_input(ip)) {
		k = atoi(ip);
		size = pow(2, k);
		// create matrix of size 2^k * 2^k
		int M[size][size];
		// generate random co-ordinates as co-ordinates of a hole.
		x_mis = generate_random_value(size);
		y_mis = generate_random_value(size);
		printf("\n Co-ordinates of a hole are : [%d, %d]",x_mis, y_mis);
		M[x_mis][y_mis] = -1;
		tromino_algo(0, 0, size, size, x_mis, y_mis, size, size, M);
		printf("\n\n Tiling of the board with trominos : ");
		display_matrix(size, M);
	}
	printf("\n\n");
	return 0;
}
