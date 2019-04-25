/*
Exercise 3.c
The program would create linked list out of chars the user type, and would ask for a jumping size, k.
the program would delete from the list one char every k steps. 
then, the program would print the list after the deletion, 
separate with '->' between them. the program use linked list and works with 
a struck that have filed of char, and a field of node (next) - one way list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node {
	char letter;
	struct node * next;
} Node;

Node* head = NULL;



Node* createNewNode(char x);
void insertAtEnd(char y);
void printList(Node* head);
void freeList();
Node* buildString();
Node* removeInJumps(Node *head, int k);

int main()
{
	int k;
	buildString();
	printf("Please the delation spaced (k)\n");
	scanf("%d", &k);
	printList(head);
	printf("\n");
	removeInJumps(head, k);
	printList(head);
	freeList();
	return 0;
}

//creating a new node, with a given char. returns a pointer to the new node
Node* createNewNode(char x) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->letter = x;
	newNode->next = NULL;
	return newNode;
}

//inserting new node to the end of the list, with a given char
void insertAtEnd(char y) {
	Node* temp = head;
	Node* newNode = createNewNode(y);
	if (head == NULL) {
		head = newNode;
		return;
	}
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;

}

//printing the list. receive a pointer to the head of the list
void printList(Node* head) {
	Node* temp = head;
	while (temp != NULL) {
		printf("%c->", temp->letter);
		temp = temp->next;
	}
	printf("\n");
}

//freeing the list and its links. using two nodes, which used as current and prev
//
void freeList() {
	Node* temp = head;
	Node* prev = head;
	if (head == NULL) {
		return;
	}
	while (temp != NULL) {
		prev = temp;
		temp = temp->next;
		free(prev);
	}
}

//The funcion would get chars from the user until \n would be typed
//and would return a pointer to the head of the list
Node* buildString() {
	Node* temp = head;
	char c;
	printf("Please insert a list of chars:\n");
	while ((c = getchar()) != '\n') {
		insertAtEnd(c);
	}
	return head;
}
/*the function would receive a node to the head of the list, and int k, which would be the
deletion frequency (every k steps to delete 1 link from the list).
in the function i created two nodes, which i can use as prev and next nodes.
after the function delete the cells in the list every k steps, it would return a pointer to the head of the list
*/
Node* removeInJumps(Node *head, int k) {
	if (k == 0) {
		return head;
	}
	Node* temp = head->next;
	Node* prev = head;
	int count = 1; 
	int boolFlag = 0;
	while (prev != NULL) {
		prev = prev->next;
		count++;
	}
	if (k > count) {
		return head;
	}
	count = 1;
	prev = head;
	temp = head->next;
	while (1) {
		while (count < k && temp != NULL) {
			prev = temp;
			temp = temp->next;
			count++;
		}
		if (temp == NULL && boolFlag == 1) {
			prev->next = temp;
			return head;
		}
		if (temp == NULL && boolFlag == 0) {
			prev->next = NULL;
			return head;
		}
		Node* toFree = temp;
		temp = temp->next;
		prev->next = toFree->next;
		free(toFree);
		count = 0;
		boolFlag = 1;
	}
	return head;
}