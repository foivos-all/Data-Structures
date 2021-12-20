#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 10000

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

int interpolation_search(int a[], int bottom, int top, int item) 
{
	int mid;
	
 	while (bottom <= top) 
	{
  		mid = bottom + (top - bottom) * ((item - a[bottom]) / (a[top] - a[bottom]));
  		
		if (item == a[mid])
   			return mid + 1;
  		if (item < a[mid])
   			top = mid - 1;
  		else
   			bottom = mid + 1;
 	}
 	
	 return -1;
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
	int Array[n], key, pos;
	double time;
	clock_t start, end;
	
	array_fill(Array);
	
	quick_sort(Array, 0, n-1);
	
	printf("\nArray: \n");
	array_print(Array);
	
	printf("Enter element to search for from 0 - 100000: ");
	scanf("%d", &key);
	
	start = clock();
	pos = interpolation_search(Array, 0, n-1, key);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	if (pos == -1)
  		printf("\nElement %d not found\n", key);
 	else
  		printf("\nElement %d found at position %d\n", key, pos);
	
	printf("Time needed: %lf seconds", time);
	
 	return 0;	
}
