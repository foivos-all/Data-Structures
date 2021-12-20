#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 1000

void array_fill(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
		A[i] = rand() % n;
}

void quick_sort(int A[], int beg, int end)
{
    int pivot, j, temp, i;
    if(beg < end)
    {
        pivot = beg;
        i = beg;
        j = end;

        while(i < j)
        {
            while(A[i] <= A[pivot] && i < end)
                i++;
            while(A[j] > A[pivot])
                j--;
            if(i<j)
            {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }

        temp = A[pivot];
        A[pivot] = A[j];
        A[j] = temp;
        quick_sort(A, beg, j-1);
        quick_sort(A, j+1, end);

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
	quick_sort(Array, 0, n-1);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
