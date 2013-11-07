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
// gcc -Wall -std=c99 prog6.3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct Node{
	int key;
	struct Node* left;
	struct Node* right;
};
typedef struct Node node;

void insertNode(node* root, node* newNode);
void preorder(node* root);
void inorder(node* root);
void postorder(node* root);
void deleteTree(node* root); //Frees the root!

int main()
{	
	//Declarations
	int maxNodes = 7;
	//Declare initial root
	node* myRoot = malloc(sizeof(node));
	myRoot->right = myRoot->left = NULL;

	//Get values and put in tree
	printf("Enter value: ");
	scanf("%i", &(myRoot->key));

	for (int i = 0; i < (maxNodes-1); i++){
		node* newNode = malloc(sizeof(node));
		newNode->right = newNode->left = NULL;
		printf("Enter value: ");
		scanf("%i", &(newNode->key));
		insertNode(myRoot, newNode);
	}
	
	//Print the tree
	printf("Pre-order:\n");
	preorder(myRoot);
	printf("In-order:\n");
	inorder(myRoot);
	printf("Post-order:\n");
	postorder(myRoot);

	return 0;
}

void insertNode(node* root, node* newNode)
{
	int found = 0;
	node* current = root;
	while (!found){
		if (newNode->key < current->key){
			if (current->left == NULL){
				current->left = newNode;
				found = 1;
			}else
				current = current->left;
		}else{
			if (current->right == NULL){
				current->right = newNode;
				found = 1;
			}else
				current = current->right;
		}
	}
	//node has been found and inserted
	return;
}

void preorder(node* root)
{
	if (root != NULL){
		printf("%i\n",root->key);
		preorder(root->left);
		preorder(root->right);
	}
	return;
}

void inorder(node* root)
{
	if (root != NULL){
		inorder(root->left);
		printf("%i\n",root->key);
		inorder(root->right);
	}
	return;
}

void postorder(node* root)
{
	if (root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%i\n",root->key);
	}
	return;
}

void deleteTree(node* root)
{
	if (root != NULL){
		deleteTree(root->right);
		deleteTree(root->left);
		free(root);
		root = NULL;
	};
	return;
}

