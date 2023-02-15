//
//  Code by Edward Plesa, Spring 2021, CS211, Project 2 "Balanced Symbol Checker
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct StackStruct
{
    char* darr; /* pointer to dynamic array  */
    int size;  /* amount of space allocated */
    int inUse; /* top of stack indicator
              - counts how many values are on the stack   */
} Stack;


//
//  init: given an instance of a stack: this function will initialize the
//  stack with an initial size of 4, a dynamically allocated array of chars,
//  and 0 elements of the array being used.
//
void init(Stack* s)
{
    s->size = 4;
    s->darr = (char*)malloc(sizeof(char) * s->size);
    s->inUse = 0;
}


//
//  growArray: given an instance of a stack: this function will 
//  grow the array by a size of 4 each time it is called. If debugMode
//  is == 1 then the function will print out debugging information when
//  called.
//
void growArray(Stack* s, int debugMode)
{
    int oldSize = s->size;

    char* temp = s->darr;
    s->darr = (char*)malloc((s->size + 4) * sizeof(char));
    for (int i = 0; i < s->size; i++)
    {
        s->darr[i] = temp[i];
    }
    free(temp);
    s->size = s->size + 4;

    if (debugMode == 1)
    {
        printf("Stack size increased from %d to %d, a total of %d values were copied\n", oldSize, s->size, s->inUse);
    }

}


//
//  push: given an instance of a stack and a character: this function will push
//  the given value onto the top of the stack and increment the inUse counter
//  by one. If there is not enough space in the stack, then we dynamically 
//  grow the stack by 4 each time. If debugMode is == 1 then the function
//  will print out debugging information when called.
//
void push(Stack* s, char val, int debugMode)
{   
    /* check if enough space currently on stack and grow if needed */
    if (s->size == s->inUse)
    {
        growArray(s, debugMode);
    }
        
    /* add val onto stack */
    s->darr[s->inUse] = val;
    s->inUse = s->inUse + 1;

    if (debugMode == 1)
    {
        printf("Character %c was pushed into the stack\n", val);
    }
}


//
//  isEmpty: given an instance of a stack: this function will check if the
//  stack is empty and return true if it is, and false if it is not empty.
//
int isEmpty(Stack* s)
{
    if (s->inUse == 0)
        return TRUE;
    else
        return FALSE;
}


//
//  top: given an instance of a stack: this function will return the
//  value found at the top of the stack.
//
char top(Stack* s)
{
    return (s->darr[s->inUse - 1]);
}


//
//  pop: given an instance of a stack: this function will pop(remove) the top
//  value of the stack. If debugMode is == 1 then the function will print out
//  debugging information when called.
//
void pop(Stack* s, int debugMode)
{
    if (debugMode == 1)
    {
        printf("Character %c was popped from the stack\n", top(s));
    }
    s->inUse = s->inUse - 1;
}


//
//  reset: given a stack: this function will free all memory in use and reset
//  the stack to its initial values;
//
//
void reset(Stack* s)
{
    free(s->darr);
    s->inUse = 0;
    s->size = 4;
}

//
//  pairFound: given two char's: this function will check if the symbols are matching pairs.
//  If they are then we can return true, otherwise the two symbols are different so we 
//  return false;
//
int pairFound(char first, char second)
{
    if (first == '(' && second == ')')
    {
        return TRUE;
    }
    else if (first == '{' && second == '}')
    {
        return TRUE;
    }
    else if (first == '[' && second == ']')
    {
        return TRUE;
    }
    else if (first == '<' && second == '>')
    {
        return TRUE;
    }

    return FALSE;
}


//
//  opposite: given a symbol character: this function will either return the opening
//  or the closing symbol which matches the input symbol.
//
char opposite(char c)
{
    if (c == '(')
    {
        return ')';
    }
    else if (c == '{')
    {
        return '}';
    }
    else if (c == '[')
    {
        return ']';
    }
    else if (c == '<')
    {
        return '>';
    }
    else if (c == ')')
    {
        return '(';
    }
    else if (c == '}')
    {
        return '{';
    }
    else if (c == ']')
    {
        return '[';
    }
    else if (c == '>')
    {
        return '<';
    }
}

void checkerAlgorithm(char str[], int debugMode)
{
    int i = 0;
    Stack s;  //  create instance of stack
    init(&s); //  initialize our stack

    while (str[i])
    {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[' || str[i] == '<')  //  if we found an opening symbol: push it onto the stack
        {
            push(&s, str[i], debugMode);
        }


        if (str[i] == ')' || str[i] == '}' || str[i] == ']' || str[i] == '>')  //  if we find a closing symbol: continue onto each case:
        {
            if (isEmpty(&s))  //  case 1: if we find the stack is empty: then we are missing an opening symbol so we return false;
            {
                printf("Unbalanced expression. Error 2: missing an opening symbol\n");
                printf("%s\n", str);
                printf("%*c", i, ' ');
                printf("^ missing %c\n", opposite(str[i]));
                reset(&s);
                return;
            }
            else if (pairFound(top(&s), str[i]) == FALSE)  //  case 2: if we find that the pair in the stack aren't matching: then our closing symbol is wrong.
            {
                printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
                printf("%s\n", str);
                printf("%*c", i, ' ');
                printf("^ expecting %c\n", opposite(top(&s)));
                reset(&s);
                return;
            }
            else  //  if we made it this far: then our symbols are correct and the stack isn't empty so we can pop the opening symbol from the stack.
            {
                pop(&s, debugMode);
            }            
        }

        i++;
    }

    if (isEmpty(&s))  //  if we made it this fair and the stack is empty: then the stack is popped of all pairs of symbol meaning the expression is balanced.
    {
        printf("%s\n", str);
        printf("Expression is balanced\n");        
        reset(&s);
        return;
    }
    else  //  otherwise the stack isnt empty so a opening symbol still remains with no pair.
    {
        printf("Unbalanced expression. Error 3: missing a closing symbol\n");
        printf("%s\n", str);
        printf("%*c", i, ' ');
        printf("^ missing %c\n", opposite(top(&s)));
        reset(&s);
        return;
    }
}

int main(int argc, char** argv)
{
    char input[301];


    char flag[] = "-d";

    int debugMode = FALSE;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(flag, argv[i]) == 0) //  check for the -d flag from the command line
        {
            debugMode = TRUE;
        }
    }

    printf("\n");

    /* set up an infinite loop */
    while (1)
    {        
        /* get line of input from standard input */
        printf("Enter input to check or q to quit\n");
        fgets(input, 300, stdin);

        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0))
            break;

        /* run the algorithm to determine is input is balanced */
        checkerAlgorithm(input, debugMode);
        printf("\n");
    }    
    printf("\nGoodbye\n");
    return 0;
}
