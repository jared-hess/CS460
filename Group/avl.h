/* interface for an AVL tree */

#ifndef AVL_H
#define AVL_H

struct avl_node{
	int key;
	struct avl_node *left;
	struct avl_node *right;
};

/* find height of the tree */
int height(struct avl_node *node);

/* find difference in height between left and right subtrees */
int difference(struct avl_node *node);

/* left rotation */
struct avl_node* left(struct avl_node *node);

/* right rotation */
struct avl_node* right(struct avl_node *node);

/* right-left rotation */
struct avl_node* right_left(struct avl_node *node);

/* left-right rotation */
struct avl_node* left_right(struct avl_node *node);

/* balance the tree */
struct avl_node* balance(struct avl_node *node);

/* insert a key */
struct avl_node* insert(struct avl_node *root, int key);

/* print the tree inorder */
void printInorder(struct avl_node *node);

/* print the tree postorder */
void printPostorder(struct avl_node *node);

/* print the tree preorder */
void printPreorder(struct avl_node *node);

#endif
