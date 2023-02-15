#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#ifndef stack_h
#define stack_h

struct stack {
    node* treeNode;    
    struct stack* next;
};

void init(struct stack** head);
int sizeStack(struct stack* head);
void push(node* datax, struct stack** head);
int isEmpty(struct stack* head);
void top(struct stack* head, node** first);
void pop(struct stack** head);
void reset(struct stack** head);

#endif
