#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(int *input_arr,int low, int high);
void randomized_quick_sort(int *input_arr, int low, int high);
void display_step(int *arr,int low, int high);

// This variable stores the size of an array. Mostly used for printing purpose.
int size;

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
generateRandomNumbersArray(char *algo_name, int n, int *input_arr){
	int count = 0;
	if(n <= 20){
		for(count = 0; count< n; count ++){
			// generate random number between 0 and 15.
			input_arr[count] = rand() % 15;
		}
	}else if(strcmp(algo_name, "Counting_sort") == 0){
		for(count = 0; count< n; count ++){
			// generate random number between 0 and 99.
			input_arr[count] = rand() % 99;
		}
	}else {
		for(count = 0; count< n; count ++){
			// generate random number.
			input_arr[count] = rand();
		}
	}
}

/*
	This function prints stars on the console.
*/
void display_stars(int count){
	int i =0;
	for(i = 0; i < count;i++){
		printf("*");
	}
}

/*
	This function is responsible for displaying current contents of the array. 
	It displays the contents of the array only if the size of the array is <= 20. 
*/
void
display_step(int *arr,int low, int high){
	if(size <= 20){
		printf("------------------------------\n");
		int count = 0;
		for(count = low; count < high; count++){
			int in_count = arr[count];
			int i = 0;
			display_stars(in_count);		
			if(count != high - 1){
				printf("\n");
			}
		}
		printf("\n------------------------------\n");
	}
}

/*
	Display function, commonly used to display sorted array.
*/
void
display_array(int *arr, int num){
	int count =0;
	printf("\n");
	for(count = 0; count < num; count++){
		printf("%d ", arr[count]);
	}
	printf("\n");
}

/*
	This display function calls display_array(int *arr, int num) function if and only if the number of elements is less than 20.
	This helps to understand visualization better.
*/
void
display_input_array(int *arr, int num){
	if(num <= 20){
		printf("\nRandomized input :");
		display_array(arr, num);
		printf("\n");
	}
}

/*
	Implementation of insertion sort.
*/
void
insertion_sort(int num, int *input_arr){
	int i = 0;
	int j = 0;
	for(i = 1; i < num; i++){
		for(j=i; j > 0; j--){
			if(input_arr[j] < input_arr[j - 1]){
				swap(&input_arr[j], &input_arr[j - 1]);
			}
		}
		display_step(input_arr, 0, size);
	}
}

/*
	Implementation of Counting sort.
*/
void counting_sort(int num, int *input_arr){
	int aux_arr[99];
	int i = 0;
	// Initializing auxiliary array.
	for(i = 0; i < 99; i ++){
		aux_arr[i] = 0;
	}
	// populating auxiliary array.
	for(i = 0;i < num; i++){
		aux_arr[input_arr[i]] = aux_arr[input_arr[i]] + 1;
	}
	if(size <= 20){
		printf("Auxiliary array- \n");	
		for(i = 0;i < 16;i++){
			int no_stars = aux_arr[i];
			printf("[%d] : ",i);
			display_stars(no_stars);
			if(i != 16 - 1){
				printf("\n");
			}
		}
		printf("\n------------------------------\n");
	}
	int arr_count = 0;
	for(i = 0;i < 99;i++){
		while(aux_arr[i] > 0){
			input_arr[arr_count] = i;
			aux_arr[i] = aux_arr[i] - 1;
			arr_count = arr_count + 1;
		}
	}	
}

/*
	Implementation of merge.
*/
void
merge(int *input_arr, int low, int mid, int high){
	int intermediate_arr[high];
	int i, k;
	int j = mid + 1;
	i = low;
	k = 0;
	while((i <= mid) && (j <= high)){
		if(input_arr[i] <= input_arr[j]){
			intermediate_arr[k++] = input_arr[i++];
		}else{
			intermediate_arr[k++] = input_arr[j++];
		}
	}
	while(i <= mid){ // copy rest of the elements from left half
		intermediate_arr[k++] = input_arr[i++];
	}
	while(j <= high){ // copy rest of the elements from right half
		intermediate_arr[k++] = input_arr[j++];
	}
	k--;
    	while (k >= 0) {
        	input_arr[low + k] = intermediate_arr[k];
        	k--;
    	}
	display_step(input_arr, low, high + 1);
}

/*
	Implementation of recusive merge sort.
*/
void
merge_sort(int *input_arr,int low, int high){
	if (low < high) {
		int mid = (low + high)/2;
		merge_sort(input_arr, low, mid);
		merge_sort(input_arr, mid + 1, high);
		merge(input_arr, low, mid, high);
	}
}

/*
	This function chooses a random pivot and partiotions the array around the pivot element. It returns the index from the array where partition has occured.
*/
int partition(int *input_arr, int low, int high){
	//generating random index value between low and high as pivot.
	int pivotIndex = low + rand()%(high - low + 1);
	int pivot;
	int i = low - 1;
	int j;
	//pivot element
	pivot = input_arr[pivotIndex];
	if(size <= 20){
		printf("\n[%d]\n", pivot);
	}
	swap(&input_arr[pivotIndex], &input_arr[high]);
	for (j = low; j < high; j++)
	{
		if (input_arr[j] < pivot)
		{
		    i++;
		    swap(&input_arr[i], &input_arr[j]);
		}
	}
	swap(&input_arr[i+1], &input_arr[high]);
	display_step(input_arr, low, high + 1);
	return i + 1;
}

/*
	Implementation of recursive randomized quick sort.
*/
void
randomized_quick_sort(int *input_arr, int low, int high){
	int j;
	if (low < high)
	{
		int p = partition(input_arr, low, high);
		randomized_quick_sort(input_arr, low, p - 1);
		randomized_quick_sort(input_arr, p + 1, high);
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
	int input_arr[size];
	if((no_ele < 0) || (no_ele > 1000)){
		return 0;
	}
	return 1;
}

/*
	main method implementation.
*/
int
main(int argc, char *argv[] )  {
	srand (time(NULL));
	int choice = 0;
	int no_ele = 0;
	
	while(choice != 5){
		printf("\n1. Insertion Sort.");
		printf("\n2. Counting Sort.");
		printf("\n3. Merge Sort.");
		printf("\n4. Randomized quick Sort.");
		printf("\n5. Exit.");
		printf("\n   Enter your choice (Between 1 and 5) : ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				no_ele = get_a_number();
				if(validate_no_ele(no_ele)){
					int input_arr[no_ele];
					size = no_ele;
					generateRandomNumbersArray("Insertion_sort", size, input_arr);
					display_input_array(input_arr, size);
					insertion_sort(size, input_arr);
					printf("\nSorted Output: ");
					display_array(input_arr, size);
				}else{
					printf("\nPlease a enter a valid number (Between 0 and 1000) !! \n");
				}			
				break;
			case 2:
				no_ele = get_a_number();
				if(validate_no_ele(no_ele)){
					int input_arr[no_ele];
					size = no_ele;
					generateRandomNumbersArray("Counting_sort", size, input_arr);
					display_input_array(input_arr, size);
					counting_sort(size, input_arr);
					printf("\nSorted Output: ");
					display_array(input_arr, size);
				}else{
					printf("\nPlease a enter a valid number (Between 0 and 1000) !! \n");
				}
				break;
			case 3:
				no_ele = get_a_number();
				if(validate_no_ele(no_ele)){
					int input_arr[no_ele];
					size = no_ele;
					generateRandomNumbersArray("Merge_sort", size, input_arr);
					display_input_array(input_arr, size);
					merge_sort(input_arr, 0, size - 1);
					printf("\nSorted Output: ");
					display_array(input_arr, size);
				}else{
					printf("\nPlease a enter a valid number (Between 0 and 1000) !! \n");
				}
				break;
			case 4:
				no_ele = get_a_number();
				if(validate_no_ele(no_ele)){
					int input_arr[no_ele];
					size = no_ele;
					generateRandomNumbersArray("Randomized_quick_sort", size, input_arr);
					display_input_array(input_arr, size);
					randomized_quick_sort(input_arr, 0, size - 1);
					printf("\nSorted Output: ");
					display_array(input_arr, size);
				}else{
					printf("\nPlease a enter a valid number (Between 0 and 1000) !! \n");
				}
				break;
			case 5:
				exit(0);
				break;
			default:
				printf("Please enter a valid option !!");
		}	
	}
	printf("\n");
	return 0;
}
