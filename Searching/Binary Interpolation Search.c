#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define n 100

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


int linear(int A[], int k, int key)
{
	int i;
	 
	for (i = 0; i < k; i++)
   	{
      	if (A[i] == key)
      	{
         	return i;
         	break;
      	}
   	}
   	
	if (i == k)
      return -1;
}

int BIS2(int A[], int left, int right, int key)
{
    int mid, i, size, counter;
    size = right - left + 1;
    counter = 0; 
    mid = (size * (key - A[left]) / (A[right] - A[left])); //middle is calculated with this mathematical function
    
    while(key != A[mid])
	{	
       	i = 1;
       	size = right - left + 1;
        
        if (size <= 3)
        	linear(A, 3, key); //if the size of the array is equal or smaller than 3 we use linear search
       	
		if(key >= A[mid]) //if the key is larger than the middle element
		{
           	while(key > A[(int)(mid  + (i * sqrt(size)) - 1)]) //we calculate the sqrt(size) steps needed to find larger elements than the one we search for
           		i= 2*i; //instead of single steps we lower the time by calculating 2^i steps
            
        
           	right = mid + i * sqrt(size); //and use the number of steps to calculate our new boundaries
           	left = mid  + (i - 1) * sqrt(size); //right and left
       	}
       	else if(key < A[mid]) //if the key is smaller than the middle element
		{
           	while(key <  A[(int)(mid  - i * sqrt(size) + 1)]) //we calculate the sqrt(size) steps needed to find smaller elements than the one we search for
               	i = 2*i; //again instead of single steps we lower the time by calculating 2^i steps
            
            
           	right = mid - (i - 1) * sqrt(size); //and use the number of steps to calculate our new boundaries
           	left = mid - i* sqrt(size); //right and left
       	}
       	mid = left + ((right - left + 1) * ((key -  A[left]) / (A[right] - A[left]))); //and calculate the new middle with the new left and right boundaries
       	counter++; //having a counter counting the times we repeat the process
       	
       	if (counter > n) //so we know when to stop if our element is not found
       		break;
    }
    
	if(key == A[mid])//if found 
        return mid; //return the position to which we found our element
    else
	    return -1;  //else return -1
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
	
	printf("Enter element to search for: ");
	scanf("%d", &key);
	
	start = clock();
	pos = BIS2(Array, 1, n, key);
	end = clock();
	
	time = (double) (end - start) / CLOCKS_PER_SEC;
	
	if (pos == -1)
  		printf("\nElement %d not found\n", key);
 	else
  		printf("\nElement %d found at position %d\n", key, pos + 1);
	
	printf("Time needed: %lf seconds", time);
	
 	return 0;	
}
