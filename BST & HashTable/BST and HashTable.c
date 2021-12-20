#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define m 19

typedef struct BSTnode
{
	char AM[10];
	char name[100];
	char surname[100];
	float degree;
	struct BSTnode *left, *right;
}BSTstudent;

typedef struct HashTablenode 
{
	char AM[10];
	char name[100];
	char surname[100];
	float degree;
	struct HashTablenode *next;
}HashTablestudent;

typedef struct hash 
{
	struct HashTablenode *head;
	int count;
}hash;

hash *hashTable = NULL;

void BSTinOrder(BSTstudent *root) //A1
{
	if (root == NULL)
		return;
	
	BSTinOrder(root->left);
	printf("%s %s %s %.2f\n", root->AM, root->name, root->surname, root->degree);
	BSTinOrder(root->right);		
};

BSTstudent *BSTnewNode(char a[], char n[], char s[], float d) 
{ 
   	BSTstudent *temp =  (BSTstudent *)malloc(sizeof(BSTstudent));
   	
    strcpy(temp->AM, a);
    strcpy(temp->name, n);
    strcpy(temp->surname, s);
    temp->degree = d;
    temp->left = temp->right = NULL; 
    return temp; 
};

HashTablestudent *HashTablenewNode(char a[], char n[], char s[], float d) 
{ 
   	HashTablestudent *temp =  (HashTablestudent *)malloc(sizeof(HashTablestudent));
   	
    strcpy(temp->AM, a);
    strcpy(temp->name, n);
    strcpy(temp->surname, s);
    temp->degree = d;
    temp->next = NULL;
    
    return temp; 
};

BSTstudent* BSTInsertWithAM(BSTstudent *node, char temp_AM[], char temp_name[], char temp_surname[], float temp_degree) //Insert with AM
{	
    /* If the tree is empty, return a new node */
    if (node == NULL) 
		return BSTnewNode(temp_AM, temp_name, temp_surname, temp_degree); 
  
    /* Otherwise, recur down the tree */
    if (strcmp(temp_AM, node->AM) < 0) 
        node->left  = BSTInsertWithAM(node->left, temp_AM, temp_name, temp_surname, temp_degree); 
    else if (strcmp(temp_AM, node->AM) > 0) 
        node->right = BSTInsertWithAM(node->right, temp_AM, temp_name, temp_surname, temp_degree);    
  
    /* return the (unchanged) node pointer */
    return node; 
};

BSTstudent* BSTInsertWithDegree(BSTstudent *node, char temp_AM[], char temp_name[], char temp_surname[], float temp_degree) //Insert with Grade 
{	
    /* If the tree is empty, return a new node */
    if (node == NULL) 
		return BSTnewNode(temp_AM, temp_name, temp_surname, temp_degree); 
  
    /* Otherwise, recur down the tree */
    if (temp_degree <= node->degree) 
        node->left  = BSTInsertWithDegree(node->left, temp_AM, temp_name, temp_surname, temp_degree); 
    else if (temp_degree > node->degree) 
        node->right = BSTInsertWithDegree(node->right, temp_AM, temp_name, temp_surname, temp_degree);    
  
    /* return the (unchanged) node pointer */
    return node; 
};

void HashTableInsert(char a[], char n[], char s[], float d) 
{
	int hashIndex, h = 0;
	HashTablestudent *newnode = HashTablenewNode(a, n, s, d);
	
	/* Finding the sum of the ASCII values of each character os the AM*/
	for (int i = 0; a[i] != '\0'; i++)
	    h = (h + (unsigned char)a[i]);
	
	/* hashIndex is equal to the sum of the ASCII values of the AM mod the number of elements in the table*/    
	hashIndex = h % m;
	
	/* head of list for the bucket with index "hashIndex" */
	if (!hashTable[hashIndex].head) 
	{
		hashTable[hashIndex].head = newnode;
		hashTable[hashIndex].count = 1;
		return;
	}
	
	// adding new node to the list 
	newnode->next = (hashTable[hashIndex].head);
	
	// update the head of the list and no of nodes in the current bucket
	hashTable[hashIndex].head = newnode;
	hashTable[hashIndex].count++;
	
	return;
};

BSTstudent* BSTReadStudentsWithAM(FILE *fp, BSTstudent *st)
{	
	int i;
	char temp_AM[10];
	char temp_name[20];
	char temp_surname[20];
	float temp_degree;
	
	for (i = 0; i <m; i++)
	{
		fscanf(fp, "%s %s %s %f", temp_AM, temp_name, temp_surname, &temp_degree); // Read the students from the file
		st = BSTInsertWithAM(st, temp_AM, temp_name, temp_surname, temp_degree); // Insert them in the BST
	}
	
	return st;
};

BSTstudent* BSTReadStudentsWithDegree(FILE *fp, BSTstudent *st)
{	
	int i;
	char temp_AM[10];
	char temp_name[20];
	char temp_surname[20];
	float temp_degree;
	
	for (i = 0; i < m; i++)
	{
		fscanf(fp, "%s %s %s %f", temp_AM, temp_name, temp_surname, &temp_degree); // Read the students from the file
		st = BSTInsertWithDegree(st, temp_AM, temp_name, temp_surname, temp_degree); // Insert them in the BST
	}
	
	return st;
};

BSTstudent* BSTSearch(BSTstudent *node, char key[]) //A2
{ 
    // Base Cases: node is null or key is present at node 
    if ((node == NULL) || (strcmp(node->AM, key) == 0)) 
       return node; 
     
    // Key is greater than node's key 
    if (strcmp(node->AM, key) < 0) 
       return BSTSearch(node->right, key);
    // Key is smaller than node's key 
  	else if (strcmp(node->AM, key) > 0)
    	return BSTSearch(node->left, key);
    else return NULL;
};

BSTstudent* BSTChange(BSTstudent *node, char key[], char n[], char s[], float d) //A3
{
	// Find the student whose details we want to change
	BSTstudent* temp = BSTSearch(node, key);
	// Assign the new details to the student
    strcpy(temp->name, n);
    strcpy(temp->surname, s);
    temp->degree = d;
    
    return temp;
};

BSTstudent* Min(BSTstudent* node) //B1
{ 
    BSTstudent* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
};

BSTstudent* Max(BSTstudent* node) //B2
{ 
    BSTstudent* current = node; 
  
    // loop down to find the rightmost leaf 
    while (current && current->right != NULL) 
        current = current->right; 
  
    return current; 
};

BSTstudent* BSTDelete(BSTstudent* node, char key[]) //A4
{
	BSTstudent *temp;
    // base case 
    if (node == NULL)
		return node; 
  
    // If the key to be deleted is smaller than the node's key, 
    // then it lies in left subtree 
    if (strcmp(node->AM, key) > 0) 
        node->left = BSTDelete(node->left, key); 
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (strcmp(node->AM, key) < 0) 
        node->right = BSTDelete(node->right, key); 
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        // node with only one child or no child 
        if (node->left == NULL) 
        { 
            temp = node->right; 
            free(node); 
            return temp; 
        } 
        else if (node->right == NULL) 
        { 
            temp = node->left; 
            free(node); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        temp = Min(node->right); 
  
        // Copy the inorder successor's content to this node 
		strcpy(node->AM, temp->AM); 
  
        // Delete the inorder successor 
        node->right = BSTDelete(node->right, temp->AM); 
    }
    
    return node; 
};

void HashTableReadStudents(FILE *fp)
{	
	int i;
	char temp_AM[10];
	char temp_name[20];
	char temp_surname[20];
	float temp_degree;
	
	for (i = 0; i < m; i++)
	{
		fscanf(fp, "%s %s %s %f", temp_AM, temp_name, temp_surname, &temp_degree); // Read the students from the file
		HashTableInsert(temp_AM, temp_name, temp_surname, temp_degree); // Insert them in the Hash Table
	}
	
	return;
};

void Print() 
{
	HashTablestudent *myNode;
	int i;
	
	printf("AM\t Name\tSurname\t Grade\n");
	printf("------------------------------------------\n");
	
	for (i = 0; i < m; i++) 
	{
	    if (hashTable[i].count == 0)
	        continue;
	        
		myNode = hashTable[i].head;
	    if (!myNode)
	        continue;
        
	    while (myNode != NULL) 
		{
	        printf("%s %s %s %.2f\n", myNode->AM, myNode->name, myNode->surname, myNode->degree);
	        myNode = myNode->next;
	    }
	}

    return;
};

void HashTableSearch(char a[]) //C1
{
    int hashIndex, h = 0, flag = 0;
    HashTablestudent *temp;	    
    
    /* Finding the sum of the ASCII values of each character os the AM*/
	for (int i = 0; a[i] != '\0'; i++)
	    h = (h + (unsigned char)a[i]);
	
	/* hashIndex is equal to the sum of the ASCII values of the AM mod the number of elements in the table*/    
	hashIndex = h % m;
    
	temp = hashTable[hashIndex].head;
	if (!temp) 
	{
	    printf("Search element unavailable in hash table\n");
	    return;
	}
	
	while (temp != NULL) 
	{
	    if (strcmp(temp->AM, a) == 0) 
		{
	        printf("Student AM  : %s\n", temp->AM);
	        printf("Name        : %s\n", temp->name);
	        printf("Surname     : %s\n", temp->surname);
	        printf("Grade       : %f\n", temp->degree);
	        flag = 1;
	        break;
	    }
	    
        temp = temp->next;
	}
	
	if (!flag)
	    printf("Search element unavailable in hash table\n");
	
	return;
}

void HashTableChange(char a[], char n[], char s[], float d) //C2
{
	// Find the student whose details we want to change
	int hashIndex, h = 0, flag = 0;
    HashTablestudent *temp;	    
    
    /* Finding the sum of the ASCII values of each character os the AM*/
	for (int i = 0; a[i] != '\0'; i++)
	    h = (h + (unsigned char)a[i]);
	
	/* hashIndex is equal to the sum of the ASCII values of the AM mod the number of elements in the table*/    
	hashIndex = h % m;
	
	temp = hashTable[hashIndex].head;
	if (!temp) 
	{
	    printf("Search element unavailable in hash table\n");
	    return;
	}
	
	while (temp != NULL) 
	{
	    if (strcmp(temp->AM, a) == 0) 
		{
			// Assign the new details to the student
	        strcpy(temp->name, n);
    		strcpy(temp->surname, s);
    		temp->degree = d;
	        flag = 1;
	        
	        break;
	    }
	    
        temp = temp->next;
	}
	
	if (!flag)
	    printf("Search element unavailable in hash table\n");
	
    return;
};

void HashTableDelete(char a[]) //C3
{
	/* find the bucket using hash index */
	int hashIndex, h = 0, flag = 0;
	HashTablestudent *temp, *myNode;
	
	/* Finding the sum of the ASCII values of each character os the AM*/
	for (int i = 0; a[i] != '\0'; i++)
	    h = (h + (unsigned char)a[i]);
	
	/* hashIndex is equal to the sum of the ASCII values of the AM mod the number of elements in the table*/    
	hashIndex = h % m;
	
	/* get the list head from current bucket */
	myNode = hashTable[hashIndex].head;
	if (!myNode) 
	{
		printf("Given data is not present in hash Table!!\n");
		return;
	}
	
	temp = myNode;
	while (myNode != NULL) 
	{
		/* delete the node with given AM */
		if (strcmp(myNode->AM, a) == 0) 
		{
			flag = 1;
		
			if (myNode == hashTable[hashIndex].head)
				hashTable[hashIndex].head = myNode->next;
			else
				temp->next = myNode->next;

			hashTable[hashIndex].count--;
			free(myNode);
			break;
		}
	
		temp = myNode;
		myNode = myNode->next;
	}
	
	if (flag)
		printf("Data deleted successfully from Hash Table.\n");
	else
	    printf("Given data is not present in hash Table.\n");
	return;
};

int main()
{
	FILE *fp = fopen("Students.txt", "r"); // Open the file in reading mode
	BSTstudent *root = NULL;
	BSTstudent *node = NULL;
	int i, choice1, choice2, choice3;
	char temp_AM[10];
	char temp_name[20];
	char temp_surname[20];
	float temp_degree;
	
	if (fp == NULL) // If the pointer is returned NULL there was a problem opening the file
   	{
    	perror("Error while opening the file.\n");
      	exit(EXIT_FAILURE);
   	}
	
	printf("Please press the corresponding number of the way you would like to load the file: \n");
	printf("1.\tBinary Search Tree.\n");
	printf("2.\tChained Hash Table.\n");
	printf("Choice: ");
	scanf("%d", &choice1);
	
	while((choice1 < 1) || (choice1 > 2))
	{
		printf("\nThe answer you have given is not valid! Please press a proper number: ");
		scanf("%d", &choice1);	
	}
	
	if (choice1 == 1)
	{
		printf("Please press the corresponding number of the way you would like to categorize the students: \n");
		printf("1.\tAM.\n");
		printf("2.\tGrade.\n");
		printf("Choice: ");
		scanf("%d", &choice2);
		
		while((choice2 < 1) || (choice2 > 2))
		{
			printf("\nThe answer you have given is not valid! Please press a proper number: ");
			scanf("%d", &choice2);	
		}
	}
		
	switch(choice1)
	{
		case 1:
			switch(choice2)
			{
				case 1:
					root = BSTReadStudentsWithAM(fp, root); // Create the BST
					
					printf("Please press the corresponding number of the action you would like to do: \n");
					printf("1:\tPrint the BST InOrder Traversal.\n");
					printf("2:\tSearch a student.\n");
					printf("3:\tChange the details of a student.\n");
					printf("4:\tDelete a student.\n");
					printf("5:\tExit the application.\n");
					printf("Choice: ");
					scanf("%d", &choice3);
	
					while((choice3 < 1) || (choice3 > 5))
					{
						printf("\nThe answer you have given is not valid! Please press a proper number: ");
						scanf("%d", &choice3);	
					}
						
					do
					{
						switch(choice3)
						{
							case 1:
								printf("AM\t Name\tSurname\t Grade\n");
								printf("------------------------------------------\n");
								BSTinOrder(root); // Printing the BST inOrder traversal	
							break;
				
							case 2:
								printf("Enter the AM of the student you wish to search for: ");
								scanf("%s", &temp_AM);
								node = BSTSearch(root, temp_AM);
								printf("%s %s %s %.2f\n", node->AM, node->name, node->surname, node->degree);
							break;
			
							case 3:
								printf("Enter the AM of the student whose details you wish to change: ");
								scanf("%s", &temp_AM);
								printf("AM\t Name\tSurname\t Grade\n");
								printf("------------------------------------------\n");
								node = BSTSearch(root, temp_AM); // Find the node which is going to be changed
								printf("%s %s %s %.2f\n", node->AM, node->name, node->surname, node->degree);
								printf("Enter the new name for the student: "); //Get the new details
								scanf("%s", &temp_name);
								printf("Enter the new surname for the student: ");
								scanf("%s", &temp_surname);
								printf("Enter the new degree for the student: ");
								scanf("%f", &temp_degree);
								BSTChange(node, temp_AM, temp_name, temp_surname, temp_degree); // Send the node and the new details to the function
							break;
			
							case 4:
								printf("Enter the AM of the student you wish to delete: ");
								scanf("%s", &temp_AM);
								printf("AM\t Name\tSurname\t Grade\n");
								printf("------------------------------------------\n");
								node = BSTSearch(root, temp_AM); // Find the node which is going to be deleted
								printf("%s %s %s %.2f\n", node->AM, node->name, node->surname, node->degree);
								root = BSTDelete(root, temp_AM); // Delete node
							break;
			
							case 5: break;
						}
						
						if (choice3 == 5)
							break;
		
						printf("Would you like something else: ");
						scanf("%d", &choice3);
		
						while((choice3 < 1) || (choice3 > 5))
						{
							printf("\nThe answer you have given is not valid! Please press a proper number: ");
							scanf("%d", &choice3);	
						}
					}while(choice3 != 5);					
				break;
						
				case 2:
					root = BSTReadStudentsWithDegree(fp, root); // Create the BST
					
					printf("Please press the corresponding number of the action you would like to do: \n");
					printf("1:\tFind the students with the lowest grades.\n");
					printf("2:\tFind the students with the highest grades.\n");
					printf("3:\tExit the application.\n");
					printf("Choice: ");
					scanf("%d", &choice3);
	
					while((choice3 < 1) || (choice3 > 3))
					{
						printf("\nThe answer you have given is not valid! Please press a proper number: ");
						scanf("%d", &choice3);	
					}
					
					do
					{
						switch(choice3)
						{
							case 1:
								printf("Information of the student with the lowest grade\n");
								printf("AM\t Name\tSurname\t Grade\n");
								printf("------------------------------------------\n");
				
								node = Min(root); // Finding the student with the min degree
								printf("%s %s %s %.2f\n", node->AM, node->name, node->surname, node->degree);	
							break;
				
							case 2:
								printf("Information of the student with the highest grade\n");
								printf("AM\t Name\tSurname\t Grade\n");
								printf("------------------------------------------\n");
				
								node = Max(root); // Finding the student with the max degree
								printf("%s %s %s %.2f\n", node->AM, node->name, node->surname, node->degree);
							break;
			
							case 3: break;
						}
						
						if (choice3 == 3)
							break;
		
						printf("\nWould you like something else: ");
						scanf("%d", &choice3);
		
						while((choice3 < 1) || (choice3 > 3))
						{
							printf("\nThe answer you have given is not valid! Please press a proper number: ");
							scanf("%d", &choice3);	
						}
					}while(choice3 != 3);
				break;
				}
			break;
			
			case 2:
				hashTable = (hash *) calloc(m, sizeof(hash)); 
	
				HashTableReadStudents(fp);
				
				printf("Please press the corresponding number of the action you would like to do: \n");
				printf("1:\tPrint the informations of the students.\n");
				printf("2:\tSearch a student.\n");
				printf("3:\tChange the details of a student.\n");
				printf("4:\tDelete a student.\n");
				printf("5:\tExit the application.\n");
				printf("Choice: ");
				scanf("%d", &choice3);
				
				while((choice3 < 1) || (choice3 > 5))
				{
					printf("\nThe answer you have given is not valid! Please press a proper number: ");
					scanf("%d", &choice3);	
				}
				
				do
				{
					switch(choice3)
					{
						case 1:
							Print(); // Printing the contents of the Hash Table	
						break;
			
						case 2:
							printf("Enter the AM of the student you wish to search for: ");
							scanf("%s", &temp_AM); //Getting the AM of the student 
							HashTableSearch(temp_AM);	   //and sending it to the function
						break;
				
						case 3:
							printf("Enter the AM of the student whose details you wish to change: ");
							scanf("%s", &temp_AM);
							HashTableSearch(temp_AM); // Find the node which is going to be changed
							printf("Enter the new name for the student: "); //Get the new details
							scanf("%s", &temp_name);
							printf("Enter the new surname for the student: ");
							scanf("%s", &temp_surname);
							printf("Enter the new degree for the student: ");
							scanf("%f", &temp_degree);
							HashTableChange(temp_AM, temp_name, temp_surname, temp_degree); // Send the new details to the function
						break;
			
						case 4:
							printf("Enter the AM of the student you wish to delete: ");
							scanf("%s", &temp_AM);
							HashTableSearch(temp_AM); // Find the node which is going to be deleted
							HashTableDelete(temp_AM); // Delete node
						break;
			
						case 5: break;
					}
					if (choice3 == 5)
						break;
		
					printf("\nWould you like something else: ");
					scanf("%d", &choice3);
		
					while((choice3 < 1) || (choice3 > 5))
					{
						printf("\nThe answer you have given is not valid! Please press a proper number: ");
						scanf("%d", &choice3);	
					}
				}while(choice3 != 5);
			break;
	}
	
	printf("\nThank you for using our application!\n");
   	fclose(fp); // Close the file
   	return 0;
}
