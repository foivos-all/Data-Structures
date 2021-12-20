#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 1000

void array_fill(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
		A[i] = rand() % 1000; //Filling the array with random numbers
}

void bubble_sort(int A[])
{
	int i, j, temp;
    
  	for (i = 0 ; i < ( n - 1 ); i++)
  	{
    	for (j = 0 ; j < n - i - 1; j++)
    	{
      		if (A[j] > A[j+1]) /* For decreasing order use < */
      		{
      			temp = A[j]; //The value of the larger element is palced in a temporary variable
    			A[j] = A[j+1]; //The value of the smaller element is placed in the largest element position
    			A[j+1] = temp; //And the largest value is placed in the position of the smaller element
      		}
    	}
  	}
}

void array_print(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
	{
		printf("%d\t", A[i]);
		
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
}

int main()
{
	int Array[n];
	double time;
	clock_t start, end; //using two clock_t variables to get the starting and the ending time of the algorithm
	
	array_fill(Array);
	printf("Unsorted Array: \n");
	array_print(Array);
	
	start = clock();
	bubble_sort(Array); //calling the function
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC; //measuring wall clock time by dividing with a constant
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
