
/*
Exercise 3.b
The program would get integers, and values as chars, and would build linked list with this values
after the user type -1, the program would ask for a size of knapsack, and would solve the knapsack problem, 
using the dynamic algorithm with linked lists. the program would print the 2D array and the max sum it would calulate
the program use pointers 2D arrays and linked lists
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE_OF_VALUE_IN_STRUCT 255

typedef struct
{
	char *value;
	int weight;
} Item1;

struct Node {
	Item1 item;
	struct Node* next;
	struct Node* prev;
};

struct Node* createNewNode(Item1 item);
void insertAtTail(struct Node **head, Item1 item);

void printList(struct Node *node);
char* charsToNumbers(char *string);

void dynamicProgramming(struct Node **head, int knapsackWeight, int numOfItems);
void freeList(struct Node **head);

int main()
{
	int sizeOfInput = 0, numOfItems = 0;	//all the variables 
	int sizeAfterRealloc = 10;
	int char_array_size = 0;
	int weight = 0;
	int scan, scan1;
	int p;
	char *ptr2, *ptr3;
	int knapsackWeight;
	char arrInput[SIZE_OF_VALUE_IN_STRUCT];
	struct Node* head = NULL;
	Item1 temp;
	while (1)
	{
		printf("Please Insert weight: ");
		scan = scanf("%d", &weight);	//scan and validation for the scan
		if (scan != 1) {
			printf("Error in scan! please type an integer");
			return 1;
		}

		if (weight == -1) {
			break;
		}

		if (weight < 0) {
			printf("Only positive weights can be typed\n");
			return 1;
		}

		temp.weight = weight;
		//assigning the weight variable to the weight value only after validation

		printf("Please insert Valuse as chars: ");
		scan1 = scanf("%s", arrInput);
		if (scan1 != 1) {
			printf("Error in scan!");
			//printf("%d", scan);
			return 1;
		}

		char_array_size = strlen(arrInput);
		for (p = 0; arrInput[p] != '\0'; p++) {
			if (arrInput[p] < 'a' || arrInput[p] > 'j') {
				printf("One letter or more is not between a to j\n");
				return 1;
			}
		}
		//after the input was typed, allocating dynamic array 
		//in the exact the size of user input, plus another spot for the \0

		ptr2 = (char*)malloc((char_array_size + 1) * sizeof(char));
		if (ptr2 == NULL) {
			printf("Error in allocation!\n");
			return 1;
		}

		//copying the arrInput into the pointer, and then asignning it 
		//into the value
		strncpy(ptr2, arrInput, (char_array_size + 1));
		temp.value = ptr2;

		/*if (head == NULL) {
			head = createNewNode(temp);
		}*/
		insertAtTail(&head, temp);
		numOfItems++;

		ptr3 = charsToNumbers(temp.value);
		printf("value as num is: %s\n", ptr3);
		printf("\n");

	}//END OF WHILE

	while (head->prev != NULL) {
		head = head->prev;
	}
	printf("Please entere the weight of knapsack: ");
	scanf("%d", &knapsackWeight);
	dynamicProgramming(&head, knapsackWeight, numOfItems);
	freeList(&head);		//free the memory of the list
	return 0;
}

//the function recieve string, which contain the input
//from the user, and then allocating precise dynamic array
//according to the user input size

char* charsToNumbers(char *string) {
	int i;
	int counter = 0;
	char *str = (char*)malloc((strlen(string) + 1) * sizeof(char));
	if (str == NULL) {
		printf("Error in allocation!\n");
		exit(1);
	}
	for (i = 0; string[i] != '\0'; i++) {
		if (string[i] != 'a' || counter > 0) {
			str[counter] = (char)((int)string[i] - 49);
			counter++;
		}
	}

	if (counter == 0) {
		str[counter] = '0';
		counter++;
	}
	str[counter] = '\0';

	return str;

}


struct Node* createNewNode(Item1 item) {		//creating new Node of Item1
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->item = item;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//the function would add a new Node 
//to the tail of the list
void insertAtTail(struct Node **head, Item1 item) { 
	struct Node* temp = *head;
	struct Node* newNode = createNewNode(item);
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}


void printList(struct Node* node)
{
	while (node != NULL)
	{
		printf("%d ", node->item.weight);
		node = node->next;
	}
}

/*the function recieve pointer to pointer, the knapsack size and the number of items.
It would build the 2D array, which is the table from the dynamic programming algorithm
*/
void dynamicProgramming(struct Node **head, int knapsackWeight, int numOfItems) {
	struct Node* temp = *head;
	int i, j, n;
	int sum = 0;
	
	int** table;
	table = (int**)malloc((numOfItems + 1) * sizeof(int*)); //the cols would be num of items's size + 1
	assert(table != NULL);

	for (n = 0; n < numOfItems + 1; n++) {
		table[n] = (int*)malloc((knapsackWeight + 1) * sizeof(int)); //the rows would be the size of knapsack + 1
		assert(table[n] != NULL);
	}

	for (i = 0; i < numOfItems + 1; i++) {	//setting first row and the first column
		table[i][0] = 0;
	}

	for (j = 0; j < knapsackWeight + 1; j++) {
		table[0][j] = 0;
	}

	for (i = 1; i < numOfItems + 1; i++)
	{
		for (j = 1; j < knapsackWeight + 1; j++) {
			if ((j - (temp->item.weight)) < 0) { //checking if j - w(i) is < 0 -> error
				table[i][j] = table[i - 1][j];
			}
			else {
				if (table[i - 1][j] < (table[i - 1][j - (temp->item.weight)] + atoi(charsToNumbers(temp->item.value)))) {
					table[i][j] = table[i - 1][j - (temp->item.weight)] + atoi(charsToNumbers(temp->item.value));
				}
				else {
					table[i][j] = table[i - 1][j];
				}
			}
		}
		if (temp->next != NULL) { //moving the temp to the next link in the list if different from NULL
			temp = temp->next;
		}
	}

	for (i = 0; i <= numOfItems; i++) {		//printing the 2D array
		printf("Row %d: ", i);
		for (j = 0; j <= knapsackWeight - 1; j++) {
			printf("%d,", table[i][j]);
		}
		printf("%d\n", table[i][j]);
		
	}
	printf("\n");
	printf("\n");
	sum = table[i - 1][j];
	printf("Max value Knapsack (solved with DP): %d", sum);

	for (i = 0; i < numOfItems; i++) { //freeing the cells of table
		free(table[i]);
	}
	free(table); //free table

}

//free all the memory the linked list use
void freeList(struct Node **head) {
	struct Node* temp = *head;
	if (*head == NULL) {
		return;
	}
	while (*head != NULL) {
		*head = (*head)->next; //moving the *head pointer to the next node
		free(temp->item.value); //freeing the value inside the temp, which is the *head prev
		free(temp);				//freeing temp itself
		temp = *head;			//moving temp to the next node
	}
}
}
