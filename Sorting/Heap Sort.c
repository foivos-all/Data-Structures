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

void heapify(int heap[])
{
	int i, c, root, temp;
	
	for (i = 1; i < n; i++)
    {
        c = i;
        do
        {
            root = (c - 1) / 2;
            if (heap[root] > heap[c])   /* to create MIN heap array */
            {
                temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            c = root;
        } while (c != 0);
    }
}

void heap_sort(int heap[])
{
	int i, c, root, temp;
	
	for (i = n - 1; i >= 0; i--)
    {
        temp = heap[0];
        heap[0] = heap[i];    /* swap min element with rightmost leaf element */
        heap[i] = temp;
        root = 0;
        do
        {
            c = 2 * root + 1;    /* left node of root element */
            if ((heap[c] > heap[c + 1]) && c < i-1)
                c++;
            if (heap[root]>heap[c] && c<i)    /* again rearrange to min heap array */
            {
                temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            root = c;
        } while (c < i);
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
		
	heapify(Array);
	printf("Heap: \n");
	array_print(Array);
	
	start = clock();
	heap_sort(Array);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
