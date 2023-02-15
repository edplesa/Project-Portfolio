#include "stack.h"

//
//  init: initilize stack to null
//
void init(struct stack** head)
{
    head = NULL;
}


//
//	size: returns size of stack
//
int sizeStack(struct stack* head)
{
	struct stack* cur;
	cur = head;
	
	int count = 0;
	if(cur != NULL)
	{
		while(cur != NULL)
		{
			count++;
			cur = cur->next;
		}
	}
	else
	{
		return 0;
	}
	return count;
}

//
//  push: given an instance of a stack and a character: this function will push
//  the given coordinate onto the top of the stack. 
//
void push(node* datax, struct stack** head) {

    struct stack* temp = (struct stack*)malloc(sizeof(struct stack));

    temp->treeNode = datax;   

    temp->next = *head;

    (*head) = temp;
}


//
//  returns 1 if the stack is empty, otherwise returns 0
//
int isEmpty(struct stack* head)
{
    return head == NULL ? 1 : 0;
}


//
//  top: given an instance of a stack: this function will return the
//  pointer found at the top of the stack.
//
void top(struct stack* head, node** first) {

    struct stack* cur = head;

    if (cur != NULL)
    {        
        *first = cur->treeNode;        
    }    
}


//
//  pop: given an instance of a stack: this function will pop(remove) the top
//  coordinate of the stack.
//
void pop(struct stack** head) {
    if (*head != NULL)
    {
        struct stack* temp = *head;
        *head = (*head)->next;

        free(temp);
    }
}

//
//  reset: given a stack: this function will free all memory in use and reset
//  the stack to its initial values;
//
//
void reset(struct stack** head)
{
    while (*head != NULL) {
        struct stack* tempPtr = *head;
        *head = (*head)->next;
        free(tempPtr);
    }
}
