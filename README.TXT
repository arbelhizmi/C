Exercise 3                            ==========================================================
CREATED BY: Arbel Hizmi 

Program description:
In "Exercise 3" we have three different programs: ex3a, ex3b, ex3c

Ex3a –The program resolve the knapsack problem (the fraction problem)
It gets from the user weight (positive integers), and value as chars (letters a - j), and ask the user for the
knapsack size. It create linked list which contain all the items the user typed (item is: value - cher, weight - int).
it merge the items in the list, according to the the integer value of the char values the user typed.
It shows what the greedy algorithm use to take into the knapsack, and what the fraction of it.

Ex3b – The program would get integers, and values as chars, and would build linked list with this values
after the user type -1, the program would ask for a size of knapsack, and would solve the knapsack problem, 
using the dynamic algorithm with linked lists. the program would print the 2D array and the max sum it would calulate
the program use pointers 2D arrays and linked lists

Ex3c - The program would create linked list out of chars the user type, and would ask for a jumping size, k.
the program would delete from the list one char every k steps. 
then, the program would print the list after the deletion, 
separate with '->' between them. the program use linked list and works with 
a struck that have filed of char, and a field of node (next) - one way list

Program files: 
Ex3a.c – source code of ex3a
Ex3b.c – source code of ex3b
Ex3c.c - source code of ex3c

Compile and running: 
In Visual Studio IDE
To compile: Ctrl + shift + b 
To run: Ctrl + f5 

Input: 
Ex3a – numbers and chars untul user type -1 and then integer for knapsack
Ex3b – numbers and chars untul user type -1 and then integer for knapsack
Ex3c - chars which would function as the list cells. integer wich would be the deletion frequency

Output:
Ex3a –  the amount of items, the value as numbers of chars, and the weight, and the size of the knapsack, the sum which added to the knapsack, the fraction, and the remain space and the maximus greedy solution value
Ex3b –  the amount of items, the value as numbers of chars, and the weight, and the size of the knapsack, the table that we need to feel using the dynamic programming algorithm nad the max value in the knapsack.
Ex3c - print the list after the deletion
