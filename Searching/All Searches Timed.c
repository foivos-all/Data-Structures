#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define n 100

void array_fill(int A[])
{
	int i;
	
	for (i = 0; i < n; i++)
		A[i] = rand() % n; //filling the array with random numbers
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


int linear_search(int A[], int k, int key)
{
	int i;
	 
	for (i = 0; i < k; i++) //checking the array one by one
   	{
      	if (A[i] == key) //until the element we are searching for is found
      	{
         	return i; //returning the position to the main function
         	break;
      	}
   	}
   	
	if (i == k)
      return -1;
}

int binary_search(int A[], int begin, int end, int search)
{
	int middle = (begin + end) / 2; //splitting the array into half
	
	while( begin <= end ) //
   	{
      if (A[middle] < search) //if the middle element is smaller than the element we are searching for
         begin = middle + 1; //we narrow our search to the right part of the array
      else if (A[middle] == search) 
      {
         return middle; //return the position to the main function
         break;
      }
      else
         end = middle - 1; //else, if the middle element is larger than the element we are searching for
         				   //we narrow our search to the left part of the array

      middle = (begin + end)/2; //assing new middle with the new begging or end values
   	}
   
   if ( begin > end ) //if the starting point becomes larger than the end point, our element is not in the array
      return -1;
}

int interpolation_search(int a[], int bottom, int top, int item) 
{
	int mid;
	
 	while (bottom <= top) 
	{
  		mid = bottom + (top - bottom) * ((item - a[bottom]) / (a[top] - a[bottom])); //each time we search we take steps that are
  																					 //equal to the mathematical function above
  		
		if (item == a[mid]) //until we found the element we search for
		{
   			return mid; //and return the position to which we found it
   			break;
   		}
  		
		if (item < a[mid]) //if the element is smaller than the middle element
   			top = mid - 1; //we narrow our search to the left side of the array
  		else
   			bottom = mid + 1; //else, we narrow it to the right side of the array
 	}
 	
 	if (bottom > top) //if the starting point becomes larger than the end point, our element is not in the array
   		return -1;
}

int BIS(int A[], int left, int right, int key)
{
    int mid, i, size, counter;
    size = right - left + 1;
    counter = 0; 
    mid = (size * (key - A[left]) / (A[right] - A[left])); //middle is calculated with this mathematical function
    
    while(key != A[mid]) 
	{	
       	i = 0;
       	size = right - left + 1;
        
        if (size <= 3)
        	linear_search(A, 3, key); //if the size of the array is equal or smaller than 3 we use linear search
       	
		if(key >= A[mid]) //if the key is larger than the middle element
		{
           	while(key > A[(int)(mid  + (i * sqrt(size)) - 1)]) //we calculate the sqrt(size) steps needed to find larger elements than the one we search for
               	i++;
        
           	right = mid + i * sqrt(size); //and use the number of steps to calculate our new boundaries
           	left = mid  + (i - 1) * sqrt(size); //right and left
       	}
       	else if(key < A[mid]) //if the key is smaller than the middle element
		{
           	while(key <  A[(int)(mid  - i * sqrt(size) + 1)]) //we calculate the sqrt(size) steps needed to find smaller elements than the one we search for
               	i++;
            
           	right = mid - (i - 1) * sqrt(size); //and use the number of steps to calculate our new boundaries
           	left = mid - i * sqrt(size); //right and left
       	}
       	mid = left + ((right - left + 1) * ((key -  A[left]) / (A[right] - A[left]))); //and calculate the new middle with the new left and right boundaries
       	counter++; //having a counter counting the times we repeat the process
       	
       	if (counter > n) //so we know when to stop if our element is not found
       		break;
    }
    
	if(key == A[mid]) //if found 
        return mid; //return the position to which we found our element
    else
	    return -1; //else return -1
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
	int Array[n], key, pos, choice;
	double time;
	clock_t start, end; //using two clock_t variables to get the starting and the ending time of the algorithm
	
	array_fill(Array);
	
	printf("\nArray: \n");
	array_print(Array);
	
	printf("Enter element to search for: ");
	scanf("%d", &key);
	
	printf("\nPlease press the corresponding number of the method of searching you would like to use: \n");
	printf("1:\tLinear Search.\n");
	printf("2:\tBinary Search.\n");
	printf("3:\tInterpolation Search.\n");
	printf("4:\tBinary Interpolation Search.\n");
	scanf("%d", &choice);
	
	while((choice < 1) || (choice > 4))
	{
		printf("\nThe answer you have given is not valid! Please press a proper number: ");
		scanf("%d", &choice);	
	}
	
	switch(choice)
	{
		case 1:
			start = clock(); //setting the starting time right before the function's call
			pos = linear_search(Array, n, key);
			end = clock(); //and the time once the function has finished
		break;
		
		case 2:
			quick_sort(Array, 0, n-1); //the search functions bellow require for the array to be sorted in order to work
			printf("\nArray sorted: \n");
			array_print(Array);
			start = clock();
			pos = binary_search(Array, 0, n-1, key);
			end = clock();	
		break;
		
		case 3:
			quick_sort(Array, 0, n-1);
			printf("\nArray sorted: \n");
			array_print(Array);
			start = clock();
			pos = interpolation_search(Array, 0, n-1, key);
			end = clock();
		break;
		
		case 4:
			quick_sort(Array, 0, n-1);
			printf("\nArray sorted: \n");
			array_print(Array);
			start = clock();
			pos = BIS(Array, 1, n, key);
			end = clock();
		break;	
	}
		
	time = (double) (end - start) / CLOCKS_PER_SEC; //measuring wall clock time by dividing with the constant CLOCKS_PER_SEC
	
	if (pos == -1)
  		printf("\nElement %d not found\n", key); //if the returned integer is -1, the element is not found
 	else
  		printf("\nElement %d found at position %d\n", key, pos + 1); //else, we print the position the element was found
	
	printf("Time needed: %lf seconds", time);  //printing the time
	
 	return 0;	
}
