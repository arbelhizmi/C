
/*
Exercise 3.a

The program resolve the knapsack problem (the fraction problem)
It gets from the user weight (positive integers), and value as chars (letters a - j), and ask the user for the
knapsack size. It create linked list which contain all the items the user typed (item is: value - cher, weight - int).
it merge the items in the list, according to the the integer value of the char values the user typed.
It shows what the greedy algorithm use to take into the knapsack, and what the fraction of it
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
void insertNewHead(struct Node **head, Item1 item);

struct Node* SortedMerge(struct Node *a, struct Node *b);
void FrontBackSplit(struct Node *source, struct Node **frontRef, struct Node **backRef);
void MergeSort(struct Node **headRef);
void printList(struct Node *node);
char* charsToNumbers(char *string);	

void greedy(struct Node **head, int knapsackWeight);
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
		insertNewHead(&head, temp);
		numOfItems++;

		ptr3 = charsToNumbers(temp.value);
		printf("value as num is: %s\n", ptr3);
		printf("\n");
		
	}//END OF WHILE

	
	printf("Please entere the weight of knapsack: ");
	scanf("%d", &knapsackWeight);
	MergeSort(&head);
	greedy(&head, knapsackWeight);		//using the Greedy algorithm
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

//Using insertNewHead is better than insertAtEnd because i dont need to run with a loop every time 
//i insert new node
void insertNewHead(struct Node** head, Item1 item) { 
	struct Node* newNode = createNewNode(item);
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	newNode->next = *head;
	*head = newNode;
}

void MergeSort(struct Node** head)
{
	struct Node* temp = *head;
	struct Node* a;
	struct Node* b;

	/* Base case -- length 0 or 1 */
	if ((temp == NULL) || (temp->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(temp, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*head = SortedMerge(a, b);
}

struct Node* SortedMerge(struct Node *a, struct Node *b)
{
	struct Node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (((double)atoi(charsToNumbers(a->item.value)) / (double)a->item.weight) >= ((double)atoi(charsToNumbers(b->item.value)) / (double)b->item.weight))
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy. */

void FrontBackSplit(struct Node *source, struct Node **frontRef, struct Node **backRef)
{
	struct Node* fast;
	struct Node* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

void printList(struct Node* node)
{
	while (node != NULL)
	{
		printf("%d ", node->item.weight);
		node = node->next;
	}
}

/*The Greedy algorithm calulate the weight that the knapsack can contain, and take the item with the highest value
and take more of it as it can and add to the knapsack
*/
void greedy(struct Node **head, int knapsackWeight) {
	struct Node* temp = *head;
	int curr = 0;
	double sum = 0;
	double fraction = 0;
	double currSum = 0;
	while (temp != NULL) {
		if (temp->item.weight <= knapsackWeight) {
			curr = temp->item.weight;
			sum += atoi(charsToNumbers(temp->item.value));
			currSum = (double)(atoi(charsToNumbers(temp->item.value)));
			knapsackWeight -= curr;
			temp = temp->next;
			printf("Added to the knapsack: %g, with fraction of: 1, Remain space is: %d\n", currSum, knapsackWeight);
		}
		 else if (temp->item.weight > knapsackWeight) {
			curr = temp->item.weight;
			fraction = ((double)knapsackWeight / (double)curr);
			sum += ((double)(atoi(charsToNumbers(temp->item.value)) / (double)curr) * (double)knapsackWeight);
			printf("Added to the knapsack: %d, with fraction of: %f, Remain space is: 0\n", atoi(charsToNumbers(temp->item.value)), fraction);
			break;
		}
		 else {
			break;
		}
		
	}
	printf("Maximum value greedy solution: %g", sum);

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