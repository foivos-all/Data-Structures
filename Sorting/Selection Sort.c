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

void selection_sort(int A[])
{
    int i,j,temp,pos;

    for ( i = 0 ; i < ( n - 1 ) ; i++ )
    {

        pos = i;

        for ( j = i + 1 ; j < n ; j++ )
        {
            if ( A[pos] > A[j] )
                pos = j;
        }
        if ( pos != i )
        {
            temp = A[i];
            A[i] = A[pos];
            A[pos] = temp;
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
	clock_t start, end;
	
	array_fill(Array);
	printf("Unsorted Array: \n");
	array_print(Array);
	
	start = clock();
	selection_sort(Array);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
