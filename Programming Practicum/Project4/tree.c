#include "tree.h"
#include "stack.h"

/*The function below will return a tree node*/
node* newNode(char* c) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->val = c;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/*The function below returns
the size (number of elements stored) of a binary
tree*/

int size(node* root) {
	if (root == NULL)
	{
		return 0;
	}

	int count = 1;

	count += size(root->left);
	count += size(root->right);
	return count;
}


/*The function below prints
a binary tree while performing an Preorder traversal.*/

void printPreorder(node* r) {
	if (r == NULL)
	{
		return;
	}

	printf(" %s ", r->val);

	printPreorder(r->left);

	printPreorder(r->right);
}


/*The function below prints
a binary tree while performing an Inorder traversal.*/

void printInorder(node* r) {
	if (r == NULL)
	{
		return;
	}
	
	if (strcmp(r->val, "+") == 0 || strcmp(r->val, "-") == 0 || strcmp(r->val, "*") == 0 
			||strcmp(r->val, "/") == 0 || strcmp(r->val, "^") == 0)
			{
				printf("(");
				
				printInorder(r->left);

				printf(" %s ", r->val);

				printInorder(r->right);
				
				printf(")");
			}
			else
			{
				printInorder(r->left);

				printf(" %s ", r->val);

				printInorder(r->right);
			}
	
}


void printPostorder(node* r)
{
	if (r == NULL)
		return;

	// first recur on left subtree 
	printPostorder(r->left);

	// then recur on right subtree 
	printPostorder(r->right);

	// now deal with the node 
	printf(" %s ", r->val);
}


/*
  The function below clears a
  binary tree.
*/

void clearTree(node* root) {
	if (root != NULL)
	{
		clearTree(root->left);
		clearTree(root->right);
		free(root);
	}
}


/*
  The function below  creates an expression tree.
*/

node* parseExpression(char e[])
{
	struct stack *st = NULL;
	init(&st);
	int sizeStack = 0;
	
	node* t = NULL;
	node* t1 = NULL;
	node* t2 = NULL;
	
	char *ptr = strtok(e , " ");
		
	// Traverse through every character of
	// input expression
	while (ptr != NULL)
	{	
		// If operator		
		if (strcmp(ptr, "+") == 0 || strcmp(ptr, "-") == 0 || strcmp(ptr, "*") == 0 
			||strcmp(ptr, "/") == 0 || strcmp(ptr, "^") == 0)
		{
		
			if (sizeStack < 2)
			{		
				reset(&st);		
				clearTree(t);
				clearTree(t1);
				clearTree(t2);			
				return NULL;
			}
						
			t = newNode(ptr);

			// Pop two top nodes
			top(st, &t1); // Store top
			pop(&st);      // Remove top
			
			 
			
			top(st, &t2);
			pop(&st);

						
			//  make them children
			t->right = t1;
			t->left = t2;

			// Add this subexpression to stack
			push(t, &st);
			sizeStack--;
		}
		else
		{
			t = newNode(ptr);
			push(t, &st);
			sizeStack++;
		}		
		ptr = strtok ( NULL, " ");
	}
	
	ptr = NULL;
	
	top(st, &t);
	pop(&st);	
	
	if (strcmp(t->val, "+") != 0 && strcmp(t->val, "-") != 0 && strcmp(t->val, "*") != 0 && strcmp(t->val, "/") != 0)
	{		
		reset(&st);
		clearTree(t);
		clearTree(t1);
		clearTree(t2);
		return NULL;
	}	
	
	
	return t;
}


int evalExpression(node* root)
{
			
	if (strcmp(root->val, "+") == 0 || strcmp(root->val, "-") == 0 || strcmp(root->val, "*") == 0 
			||strcmp(root->val, "/") == 0 || strcmp(root->val, "^") == 0)
			{
				int left = evalExpression(root->left);
				int right = evalExpression(root->right);
				if (strcmp(root->val, "+") == 0)
				{
					return left + right;
				}				
				if (strcmp(root->val, "-") == 0)
				{
					return left - right;
				}
				if (strcmp(root->val, "*") == 0)
				{
					return left * right;
				}
				if (strcmp(root->val, "/") == 0)
				{
					return left / right;
				}
				if (strcmp(root->val, "^") == 0)
				{
					return left ^ right;
				}
			}
			else			
			{
				int num = atoi(root->val);
				return num;
			}
			
}
