Project Description -

Implement insertion sort, counting sort, merge sort, and randomized quick sort algorithms.
a) Let a user select the sorting algorithm to use and specify the number of input data n where 1 ≤ n ≤ 1,000.  Return an error message, if the selected sorting method is not supported by your program or n < 1 or n > 1,000. 
b) Randomly generate an array of n positive integers and print them.
Note 3: For counting sort, ensure that the value of each randomly generated data item is an integer that ranges between 0 and 99. For the other sorting algorithms, data values are arbitrary integers returned by the pseudo random number generator.
c) Sort the randomly generated data in non-descending order using the selected sorting algorithm. Print the final result.
d) If n ≤ 20, create random numbers that range between 0 and 15 and do simple textual visualization of the sorting process as follows. (Do not do this if n > 20.) For a number k that is randomly        generated in Step 2, print “*” k times and move to a new line. For example, if the data to sort are (7, 3, 5), your program needs to display the following before starting to sort them:
*******
***
*****
After executing one step of the selected sorting algorithm, print the array to show the current state.  For instance, if the array becomes (3, 7, 5) after executing one step of the selected sorting algorithm, your program needs to print the following:
***
*******
*****  

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Steps for execution -

1. Execute make command from within the directory -
	make
2. Run following command to execute different algorithms : 
	./a.out
3. Below Menu will be displayed on the command prompt :

	1. Insertion Sort.
	2. Counting Sort.
	3. Merge Sort.
	4. Randomized quick Sort.
	5. Exit.
	   Enter your choice (Between 1 and 5) : 'Enter your choice'
Note:
On selecting one of the options, program will ask user to enter the number of elements to be sorted.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
