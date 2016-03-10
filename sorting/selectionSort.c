#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	This method is responsible for swaping two integers in memory.
*/
void
swap(int *ip1, int *ip2){
	int temp = 0;
	temp = *ip1;
	*ip1 = *ip2;
	*ip2 = temp;
}

/*
	This method generates 'n' random numbers and stores them in an array.
	Note: If 'n' <= 20 then it generates random number between 0 and 15.
*/
void
generateRandomNumbersArray(int size, int input_arr[size]){
	int count = 0;
	for(count = 0; count < size; count ++){
		input_arr[count] = rand() % 100 + (0);
	}
}

/*
	Display function, commonly used to display sorted array.
*/
void
display_array(int size, int arr[size]){
	int count =0;
	printf("\n");
	for(count = 0; count < size; count++){
		printf("%5d ", arr[count]);
	}
	printf("\n");
}

/*
	Implementation of selection sort.
	Method 1 - Select largest element in a sub-array and put it at the end of the sub-array.
*/
void
selection_sort_1(int num, int input_arr[num]){
	int i = 0;
	int j = 0;
	int max_index_pos = 0;
	for(i = num - 1; i > 0; i--){
		max_index_pos = i;
		for(j = 0; j < i; j++){
			if(input_arr[j] > input_arr[max_index_pos]){
				max_index_pos = j;
			}
		}
		swap(&input_arr[i], &input_arr[max_index_pos]);
	}
}

/*
	Implementation of selection sort.
	Method 2 - Select smallest element in a sub-array in each iteration and put it at the beginning of the sub-array.
*/
void
selection_sort_2(int num, int input_arr[num]){
	int i = 0;
	int j = 0;
	int min_index_pos = 0;
	for(i = 0; i < num; i++){
		min_index_pos = i;
		for(j = i + 1; j < num; j++){
			if(input_arr[j] < input_arr[min_index_pos]){
				min_index_pos = j;
			}
		}
		swap(&input_arr[i], &input_arr[min_index_pos]);
	}
}


/* 
	This function scans number of elements from the command line.
*/
int
get_a_number(){
	int n;
	printf("\n Please enter number of elements : ");
	scanf("%d",&n);
	return n;
}

/* 
	This function checks whether the given input is withini specified range.
*/
int validate_no_ele(int no_ele){
	if((no_ele < 0) || (no_ele > 1000)){
		return 0;
	}
	return 1;
}

int copy_array(int size, int A[size], int B[size]){
	int i = 0;
	for(i = 0; i < size; i++) {
		B[i] = A[i];
	}
}

/*
	main method implementation.
*/
int
main(int argc, char *argv[]) {
	srand (time(NULL));
	int no_ele = 0;
	no_ele = get_a_number();
	if(validate_no_ele(no_ele)){
		int input_arr1[no_ele];
		int input_arr2[no_ele];
		generateRandomNumbersArray(no_ele, input_arr1);
		copy_array(no_ele, input_arr1, input_arr2);
		printf("\n\n Randomly generated array is : ");
		display_array(no_ele, input_arr1);
		selection_sort_1(no_ele, input_arr1);
		printf("\n\n Sorted Output by Method I (Select largest element in a sub-array in each iteration and put it at the end of the sub-array): ");
		display_array(no_ele, input_arr1);
		selection_sort_2(no_ele, input_arr2);
		printf("\n\n Sorted Output by Method II (Select smallest element in a sub-array in each iteration and put it at the beginning of the sub-array): ");
		display_array(no_ele, input_arr2);
	}else{
		printf("\nPlease a enter a valid number (Between 0 and 1000) !! \n");
	}			
	printf("\n\n");
	return 0;
}
