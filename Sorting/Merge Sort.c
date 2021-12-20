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

void merge(int A[],int beg,int mid,int end)
{
  int tmp[n];
  int i,j,k,m;
  j=beg;
  m=mid+1;
  for(i=beg; j<=mid && m<=end ; i++)
  {
     if(A[j]<=A[m])
     {
         tmp[i]=A[j];
         j++;
     }
     else
     {
         tmp[i]=A[m];
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=end; k++)
     {
         tmp[i]=A[k];
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        tmp[i]=A[k];
        i++;
     }
  }
  for(k=beg; k<=end; k++)
     A[k]=tmp[k];
}

void merge_sort(int A[], int beg, int end)
{
	if (beg < end)
	{
		int mid  = (beg+end) / 2;
		merge_sort(A, beg, mid);
		merge_sort(A, mid+1, end);
		merge(A, beg, mid, end);
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
	merge_sort(Array, 0, n-1);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time);
	
	return 0;	
}
