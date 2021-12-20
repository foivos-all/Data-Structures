#include <stdio.h>

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

int main()
{
	int A[100], i, n, search, pos = -1, begin, end, middle;
	
	printf("Give size of array: ");
	scanf("%d", &n);
	
	begin = 0;
	end = n - 1;
	
	for (i = 0; i < n; i++)
	{
		printf("Give number for array: ");
		scanf("%d", &A[i]);
	}
	
	quick_sort(A, begin, end);
	
	printf("Array (sorted): ");
	for (i = 0; i < n; i++)
		printf("%d\t", A[i]);
	
	printf("\nGive element to search for: ");
	scanf("%d", &search);
	
	middle = (begin + end) / 2;
	
	while( begin <= end )
   {
      if (A[middle] < search)
         begin = middle + 1;
      else if (A[middle] == search)
      {
         printf("%d found at position %d.\n", search, middle);
         break;
      }
      else
         end = middle - 1;

      middle = (begin + end)/2;
   }
   if ( begin > end )
      printf("Not found! %d is not present in the list.\n", search);			
	
	return 0;
}
