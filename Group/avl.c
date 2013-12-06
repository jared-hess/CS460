#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* find height of the tree */
int height(struct avl_node *node)
{
	int ht = -1; /* this is the height of a null pointer */
	int left_height;
	int right_height;
	int max;

	if(node != NULL)
	{
		left_height = height(node->left); /* recursively call "height" for left subtree */
		right_height = height(node->right); /* recursively call "height" for right subtree */
		max = (left_height > right_height)?left_height : right_height; /* max of left and right */
		ht = 1 + max; /* height is zero for single node */
	}
	return ht;		
}

/* find difference in height between left and right subtrees */
int difference(struct avl_node *node)
{
	int left;
	int right;
	int difference;

	left = height(node->left); /* get height of left subtree */
	right = height(node->right); /* get height of right subtree */
	difference = left - right; /* difference will determine if rotation is needed */

	return difference;
}

/* left rotation */
struct avl_node* left(struct avl_node *node)
{
	struct avl_node *pt;

	pt = node->right;
	node->right = pt->left;
	pt->left = node;
	
	return pt;
}

/* right rotation */
struct avl_node* right(struct avl_node *node)
{
	struct avl_node *pt;

	pt = node->left;
	node->left = pt->right;
	pt->right = node;

	return pt;
}

/* right-left rotation */
struct avl_node* right_left(struct avl_node *node)
{
	struct avl_node *pt;

	pt = node->right;
	node->right = right(pt); /* right rotation for left-biased subtree */

	return left(node); /* left rotation for right imbalance */
}

/* left-right rotation */
struct avl_node* left_right(struct avl_node *node)
{
	struct avl_node *pt;

	pt = node->left;
	node->left = left(pt); /* left rotation for right-biased subtree */

	return right(node); /* right rotation for left imbalance */
}

/* balance the tree */
struct avl_node* balance(struct avl_node *node)
{
	int diff;

	diff = difference(node); /* get height difference of left and right subtrees */
	if(diff > 1) /* tree is imbalanced to the left */
	{
		if(difference(node->left) > 0)
			node = right(node); /* single right rotation fixes it */
		else
			node = left_right(node); /* negative balance: left-right rotation fixes it */
	}
	else if(diff < -1) /* tree is imbalanced to the right */
	{
		if(difference(node->right) > 0)
			node = right_left(node); /* positive balance: right-left rotation fixes it */
		else
			node = left(node); /* single left rotation fixes it */
	}

	return node;
}

/* insert a key */
struct avl_node* insert(struct avl_node *root, int key)
{
	if(root == NULL) /* create new node, populate key, set null pointers */
	{
		root = malloc(sizeof(struct avl_node));
		root->key = key;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if(key < root->key) /* insert to the left and balance */
	{
		root->left = insert(root->left, key);
		root = balance(root);
	}
	else if(key > root->key) /* insert to the right and balance */
	{
		root->right = insert(root->right, key);
		root = balance(root);
	}

	return root;
}

/* print the tree inorder */
void printInorder(struct avl_node *node)
{
	if (node == NULL)
		return;
	/* process left node */
	printInorder(node->left);
	/* process root */
	printf("%d ", node->key);
	/* process right node */
	printInorder(node->right);
}

/* print the tree postorder */
void printPostorder(struct avl_node *node)
{
	if (node == NULL)
		return;
	/* process the left node */
	printPostorder(node->left);
	/* process the right node */
	printPostorder(node->right);
	/* process the root */
	printf("%d ", node->key);
}

/* print the tree preorder */
void printPreorder(struct avl_node *node)
{
	if (node == NULL)
		return;
	/* process the root */
	printf("%d ", node->key);
	/* process the left node */
	printPreorder(node->left);
	/* process the right node */
	printPreorder(node->right);
}
