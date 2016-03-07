#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int no = 1;

void 
randomize_matrix(int size, int A[][size]) {
	int i = 0;
	int j = 0;
	for(i = 0;i < size;i++) {
		for(j=0;j < size;j++) {
			A[i][j] = rand() % 21 + (-10);
		}
	}
}

int
generate_random_value(int range){
	int val = 0;
	val = rand() % range + 0;
	return val;
}

void
display_matrix(int size, int W[][size]){
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0;i < size;i++){
		printf("\n");
		for(j=0; j < size; j++){
			printf(" %d ", W[i][j]);
		}
	}
}

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

main()
{
	srand(time(NULL));
	int k = 0, size = 0, x_mis = 0, y_mis = 0;
	printf("\nPlease enter the value of k : ");
	scanf("%d",&k);
	size = pow(2,k);
	int M[size][size];
	x_mis = generate_random_value(size);
	y_mis = generate_random_value(size);
	printf("\n x_mis : %d",x_mis);
	printf("\n y_mis : %d",y_mis);
	M[x_mis][y_mis] = -1;
	tromino_algo(0, 0, size, size, x_mis, y_mis, size, size, M);
	printf("\n\n Final matrix is : ");
	display_matrix(size, M);
	printf("\n\n");
	return 0;
}
