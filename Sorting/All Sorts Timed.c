#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 11000

void array_fill(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
		A[i] = rand() % n; //Filling the array with random numbers
}

void array_print(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
	{	
		printf("%d\t", A[i]);
		
		if ((i+1) % 10 == 0)
			printf("\n");
	}
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

void selection_sort(int A[])
{
    int i,j,temp,pos;

    for ( i = 0 ; i < (n - 1) ; i++ )
    {
        pos = i;

        for ( j = i + 1 ; j < n ; j++ )
        {
            if ( A[pos] > A[j] )
                pos = j; //finding the position of the largest element
        }
        if ( pos != i )
        {
            temp = A[i];   //The value of the larger element is palced in a temporary variable
            A[i] = A[pos]; //The value of the smaller element is placed in the largest element position
            A[pos] = temp; //And the largest value is placed in the position of the smaller element
        }
    }
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
         tmp[i]=A[j]; //placing the smaller elements in the beggining of the array
         j++;
     }
     else
     {
         tmp[i]=A[m]; //and the larger in the end
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=end; k++)
     {
         tmp[i]=A[k]; //filling the array
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        tmp[i]=A[k]; //filling the array
        i++;
     }
  }
  for(k=beg; k<=end; k++)
     A[k]=tmp[k]; //merging the two arrays
}

void merge_sort(int A[], int beg, int end)
{
	if (beg < end) 
	{
		int mid  = (beg+end) / 2; //findind the middle
		merge_sort(A, beg, mid); //calling the merge sort on one part
		merge_sort(A, mid+1, end); //and then on the other part
		merge(A, beg, mid, end); //and merging the two arrays together
	} //until the begging and end of the array meet
}

void quick_sort(int A[], int beg, int end)
{
    int pivot, j, temp, i;
    if(beg < end)
    {
        pivot = beg; //setting the pivot
        i = beg;
        j = end;

        while(i < j)
        {
            while(A[i] <= A[pivot] && i < end) //finding the smallest element closest to the pivot
                i++;
            while(A[j] > A[pivot]) //and largest closer to the pivot
                j--;
            if(i<j)
            {
                temp = A[i]; //swapping places between
                A[i] = A[j]; //he largest and the smallest
                A[j] = temp; //element close to the pivot
            }
        }

        temp = A[pivot]; //the pivot element goes to a temporary variable
        A[pivot] = A[j]; //setting the pivot to a new element
        A[j] = temp; //the former pivot goes into place 
        quick_sort(A, beg, j-1); //recursive calls of the function to 
        quick_sort(A, j+1, end); //individual parts of the array

    }
}

void heapify(int heap[])
{
	int i, c, root, temp;
	
	for (i = 1; i < n; i++)
    {
        c = i;
        do
        {
            root = (c - 1) / 2; //setting the root to the middle
            if (heap[root] < heap[c])   /* to create MAX heap array */
            {
                temp = heap[root]; //the root goes to a temporary variable
                heap[root] = heap[c]; //the smaller element becomes the new root
                heap[c] = temp; //and the former root goes to the position of the smaller element
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
        heap[0] = heap[i];    /* swap max element with rightmost leaf element */
        heap[i] = temp;
        root = 0;
        do
        {
            c = 2 * root + 1;    /* left node of root element */
            if ((heap[c] < heap[c + 1]) && c < i-1)
                c++;
            if (heap[root]<heap[c] && c<i)    /* again rearrange to max heap array */
            {
                temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            root = c;
        } while (c < i);
    }
}

int main()
{
	int Array[n], choice;
	double time;
	clock_t start, end; //using two clock_t variables to get the starting and the ending time of the algorithm
	
	array_fill(Array);
	printf("Unsorted Array: \n");
	array_print(Array);
	
	printf("\nPlease press the corresponding number of the method of sorting you would like to use: \n");
	printf("1:\tBubble Sort.\n");
	printf("2:\tInsertion Sort.\n");
	printf("3:\tSelection Sort.\n");
	printf("4:\tMerge Sort.\n");
	printf("5:\tQuick Sort.\n");
	printf("6:\tHeap Sort.\n");
	scanf("%d", &choice);
	
	while((choice < 1) || (choice > 6))
	{
		printf("\nThe answer you have given is not valid! Please press a proper number: ");
		scanf("%d", &choice);	
	}
	
	switch(choice)
	{
		case 1:
			start = clock(); //setting the starting time right before the function's call
			bubble_sort(Array);
			end = clock(); //and the time once the function has finished
		break;
		
		case 2:
			start = clock();
			insertion_sort(Array);
			end = clock();	
		break;
		
		case 3:
			start = clock();
			selection_sort(Array);
			end = clock();
		break;
		
		case 4:
			start = clock();
			merge_sort(Array, 0, n-1);
			end = clock();
		break;
		
		case 5:
			start = clock();
			quick_sort(Array, 0, n-1);
			end = clock();
		break;
		
		case 6:
			heapify(Array);
	
			start = clock();
			heap_sort(Array);
			end = clock();
		break;	
	}
	
	time = (double) (end - start) / CLOCKS_PER_SEC; //measuring wall clock time by dividing with the constant CLOCKS_PER_SEC
	
	printf("\nSorted Array: \n");
	array_print(Array);
	printf("Time taken to sort the array: %lf seconds", time); //printing the time
	
	return 0;
}
