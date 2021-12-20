#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 1000

void array_fill(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
		A[i] = rand() % 1000;
}

void insertion_sort(int A[])
{
	int i, j;
	
	for (int i = 1; i < n; i++)
	{// insert a[i] into a[0:i-1]
 		int t = A[i];
 		int j;
 		
 		for (j = i - 1; j >= 0 && t < A[j]; j--)
 			A[j + 1] = A[j];
 				
 		A[j + 1] = t;
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
	clock_t start, end;
	
	array_fill(Array);
	printf("Unsorted Array: \n");
	array_print(Array);
	
	start = clock();
	insertion_sort(Array);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
