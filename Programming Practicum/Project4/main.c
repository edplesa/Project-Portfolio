#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void printCommands()
{
    printf("The commands for this program are:\n\n");
    printf("q - to quit the program\n");
    printf("? - to list the accepted commands\n");
    printf("or any postfix mathematical expression using operators of *, /, +, -\n");
}


int main(int argc, char const* argv[])
{


    char input[300];

    /* set up an infinite loop */
    while (1)
    {


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
        /* check if user enter ? to see command list */
        else if (strcmp(input, "?") == 0)
            printCommands();

        /* user enters an expression */
        else {
            printf("%s\n", input);

            node* tree = parseExpression(input);
            
            if (tree == NULL)
            {
            	printf("Invalid expression. Enter a valid postfix expression \n");            	
            }           
            else
            {
            	printf("Infix notation: ");
		        printInorder(tree);
		        printf("\n");
		        
		        printf("Prefix notation: ");
		        printPreorder(tree);
		        printf("\n");
		        
		        printf("Postfix notation: ");
		        printPostorder(tree);
		        printf("\n");
		        
		        printf("Expression result: ");
		        printf("%d\n", evalExpression(tree));
		        
		        printf("\n");
		        
		        
            } 
            clearTree(tree);
            

        }        
    }
	

	
    printf("\nGoodbye\n");

    return 0;

}




