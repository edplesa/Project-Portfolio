#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef Tree
#define Tree

typedef struct TreeNode {
	char* val;
	struct TreeNode* left;
	struct TreeNode* right;
}node;

node* newNode(char* c);
int size(node* root);
void printPreorder(node* r);
void printInorder(node* r);
void printPostorder(node* r);
void clearTree(node* root);
int maxDepth(node* root);
node* parseExpression(char e[]);
int evalExpression(node* root);

#endif
