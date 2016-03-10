#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*
	Initialize all elements of an array to 0.
*/
void
initialize_array(int size, int arr[size]){
	int i = 0;
	for(i = 0;i < size; i++){
		arr[i] = 0;
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

void
generate_fibonacci_sequence(int size, int arr[size]){
	int i = 0;
	initialize_array(size, arr);
	arr[0] = 1;
	arr[1] = 1;
	for(i = 2; i < size; i++){
		arr[i] = arr[i - 1] + arr[i - 2];
	}
}

/*
	Main method.
*/
int main(int argc,char **argv){
	char input[1000];
	printf("\n\n Please enter a number n (n >= 0) : ");
	scanf("%s", input);
	if(is_number(input)) {
		int num = atoi(input);
		int arr[num];
		generate_fibonacci_sequence(num, arr);
		printf("\n\n Value at index %d of fibonacci sequence is : %d", num, arr[num - 1]);
	}
	printf("\n\n");
	return 0;
}
