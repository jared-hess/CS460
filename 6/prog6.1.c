/*
The proceeding code was authored by:

   d88b d8888b. db   db d88888b .d8888. .d8888.
   `8P' 88  `8D 88   88 88'     88'  YP 88'  YP
    88  88   88 88ooo88 88ooooo `8bo.   `8bo.
    88  88   88 88~~~88 88~~~~~   `Y8b.   `Y8b.
db. 88  88  .8D 88   88 88.     db   8D db   8D
Y8888P  Y8888D' YP   YP Y88888P `8888Y' `8888Y'

Created for the fulfillment of the requirements for CS460 and should hereafter be considered to be released to the public domain under the terms of the GNU GPL version 3.
*/

//Prog#:
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
// Program must be compiled with the "-std=c99" option. For example:
// gcc -Wall -std=c99 prog6.1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct linked_list
{
	int key;
	struct linked_list *next;
};
typedef struct linked_list node;

//Function prototypes
node* insertSSLL(node *head, int x);
//I've modified the following functions because there is no reason for them to return anything
//node* printSSLL(node *head);
void printSSLL(node* head);
//mine
void freeSSLL(node* head);

int main ()
{
	//time stuff
	srand (time(NULL)); //initialize rand seed
	
	int maxNodes = 1000;
	printf("Creating list...\n");
	node head;
	head.next = NULL;
	printf("List created!\n");

	printf("Inserting nodes...\n");	
	for (int i=0; i<maxNodes; i++){
		int testKey = rand() % 1000;
		printf("Inserting %i, node %i of %i...\n",testKey, i, maxNodes);
		insertSSLL(&head, testKey);
		printf("Insert successful!\n");
	}
	printf("Insert complete!\n");
	printf("Printing list...\n");
	printSSLL(&head);
	printf("Print complete!\n");
	printf("Freeing...\n");
	freeSSLL(&head);
	printf("Free successful!\n");
	printf("Terminating program.\n");
	return 0;
}

node* insertSSLL(node* head, int x)
{
	//Create our node based on our key
	node* myNode = malloc(sizeof(node));
	myNode->key = x;

	node* current = head; //start at the head.
	int found = 0;

	//We started at the head, but since we only care about the value of next node, it won't matter that the head key is garbage.
	while (!found){
		if (current->next != NULL){//If there is stuff left
			if (myNode->key > current->next->key)//if our key is bigger than the next guy, go to the next
				current = current->next;
			else{ //our key belongs after current
				found = 1;
				myNode->next = current->next;
				current->next = myNode;
			}//if	
		}else{//We are at the end!
			myNode->next = NULL;
			found = 1;
			current->next = myNode;
		}//if
	}//while
	return myNode;
}

void printSSLL(node* head){
	node* current = head->next;

	while (current != NULL){
		printf("%i\n",current->key);
		current = current->next;
	}
	return;
}

void freeSSLL(node* head)
{
	node* current = head->next;
	while (current != NULL){
		node* previous = current;
		current = current->next;
		free(previous);
	}
	return;
}
