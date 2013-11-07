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

//Prog#: 6.3
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
// Program must be compiled with the "-std=c99" option. For example:
// gcc -Wall -std=c99 prog6.2.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct Deque
{
	int key;
	struct Deque* left;
	struct Deque* right;
}*head,*tail;
typedef struct Deque node;

//Prototypes
void AddDQ(node* p, int x);
void DeleteDQ(node* p);
void PrintDQ(node* p);

int main()
{
	//Initialize our deque
	node myHead;
	node myTail;
	myHead.left = NULL;
	myHead.right = &myTail;
	myTail.right = NULL;
	myTail.left = &myHead;

	//Do some stuff
	//AddDQ(&myHead,10);
	AddDQ(&myHead,55);
	AddDQ(&myTail,99);
	AddDQ(&myTail,77);
	AddDQ(&myHead,33);

	//Print the DQ both ways
	printf("Before deletion: \n");
	printf("From Head: \n");
	PrintDQ(&myHead);
	printf("From Tail: \n");
	PrintDQ(&myTail);

	//Delete
	DeleteDQ(&myHead);
	DeleteDQ(&myTail);

	//Print after deletions
	printf("\nAfter deletions: \n");
	printf("From Head: \n");
	PrintDQ(&myHead);
	printf("From Tail: \n");
	PrintDQ(&myTail);


	return 0;
}

void AddDQ(node* p, int x)
{
	node* newNode = malloc(sizeof(node));
	newNode->key = x;

	if (p->left == NULL){ //If Head
		newNode->right = p->right;
		newNode->left = p;
		p->right->left = newNode;
		p->right = newNode;
	} else if (p->right == NULL){ //If tail
		newNode->left = p->left;
		newNode->right = p;
		p->left->right = newNode;
		p->left = newNode;
	} else { //if Not head or tail (this shouldn't happen).
		printf("Error. Non-end node passed to enqueue. This could be fatal.\n");
	}

	return;
}

void DeleteDQ(node* p)
{
	node* old;
	if (p->left == NULL){ //If head
		if (p->right->right != NULL){//Don't delete the tail
			old = p->right;
			p->right = p->right->right;
			old->right->left = p;
		}else
			printf("Tail deletion attempted\n");
	}else if (p->right == NULL){ //If tail
		if (p->left->left != NULL){//Don't delete the head
			old = p->left;
			p->left = p->left->left;
			old->left->right = p;
		}else
			printf("Head deletion attempted\n");
	}
	return;
}

void PrintDQ(node* p)
{
	node* current;
	if (p->left == NULL){//If head
		current = p->right;
		while (current->right != NULL){
			printf("Key: %i\n", current->key);
			current = current->right;
		}
	} else if (p->right == NULL){//if tail
		current = p->left;
		while (current->left != NULL){
			printf("Key: %i\n", current->key);
			current = current->left;
		}
	} else
		printf("Non end node passed to print function. ");
return;
}
