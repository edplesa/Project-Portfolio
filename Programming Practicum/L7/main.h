#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct TreeNode {
	int val; 
	struct TreeNode *left; 
	struct TreeNode *right; 
}node; 

node* newNode(int key);
int size(node* root);
void printPreorder(node* r);
void printInorder(node* r);
void clearTree(node* root);
int maxDepth (node* root);
node* insertBST(node* root, int key);
