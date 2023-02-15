/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>
#include "StackClass.h"
#include "TokenClass.h"

// Enumarated Type specifying all of the Tokens

void printCommands()
{
    printf("The commands for this program are:\n\n");
    printf("q - to quit the program\n");
    printf("? - to list the accepted commands\n");
    printf("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

class TokenReader
{
private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;


public:

    // initialize the TokenReader class to read from Standard Input
    TokenReader()
    {
        // set to read from Standard Input
        inputline[0] = '\0';
        pos = 0;
        needline = true;
    }

    // Force the next getNextToken to read in a line of input
    void clearToEoln()
    {
        needline = true;
    }

    // Return the next Token from the input line
    Token getNextToken()
    {
        char* endCheck;

        //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

        // get a new line of input from user
        if (needline)
        {
            endCheck = fgets(inputline, 300, stdin);

            if (endCheck == NULL)
            {
                printf("Error in reading");
                Token t(EOFILE);
                return t;
            }

            for (int i = 0; i < strlen(inputline); i++)
                if ('\n' == inputline[i])
                    inputline[i] = ' ';
            strcat(inputline, " ");    // add a space at end to help deal with digit calculation
            needline = false;
            pos = 0;
        }

        // skip over any white space characters in the beginning of the input
        while (pos < strlen(inputline) && isspace(inputline[pos]))
        {
            pos++;
        }

        // check for the end of the current line of input
        if (pos >= strlen(inputline))
        { // at end of line
            needline = true;
            Token t(EOLN);
            return t;
        }

        // Get the next character from the input line
        char ch = inputline[pos]; pos++;

        // check if 'q' or 'Q' was entered ==> QUIT Token
        if ('q' == ch || 'Q' == ch)
        {
            return Token(QUIT);
        }

        // check if "?" was entered ==> HELP Token
        if ('?' == ch)
        {
            return Token(HELP);
        }

        // check for Operator values of: + - * / ( )  ==> OPERATOR Token
        if (('+' == ch) || ('-' == ch) || ('*' == ch) ||
            ('/' == ch) || ('%' == ch) || ('(' == ch) || (')' == ch))
        {
            Token t;
            t.setToOperator(ch);
            return t;
        }

        // check for a number  ==> VALUE Token
        if (isdigit(ch))
        {
            int number = int(ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
            ch = inputline[pos]; pos++;
            while (isdigit(ch))
            {
                number = number * 10 + int(ch) - int('0');
                ch = inputline[pos]; pos++;
            }
            pos--; // since number calcuation check one character after the last digit
            Token t;
            t.setToValue(number);
            return t;
        }

        // Input in not valid if code get to this part ==> ERROR Token
        return Token(ERROR);
    }

};


/**************************************************************/
/*                                                            */
/*  The Code above this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

void processExpression(Token inputToken, TokenReader* tr);

int main(int argc, char* argv[])
{
    /***************************************************************/


    Token inputToken;
    TokenReader tr;

    printf("Starting Expression Evaluation Program\n\n");
    printf("Enter Expression: ");


    inputToken = tr.getNextToken();

    while (inputToken.equalsType(QUIT) == false)
    {
        /* check first Token on Line of input */
        if (inputToken.equalsType(HELP))
        {
            printCommands();
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(ERROR))
        {
            printf("Invalid Input - For a list of valid commands, type ?\n");
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(EOLN))
        {
            printf("Blank Line - Do Nothing\n");
            /* blank line - do nothing */
        }
        else
        {
            processExpression(inputToken, &tr);
        }

        printf("\nEnter Expression: ");
        inputToken = tr.getNextToken();
    }

    printf("Quitting Program\n");
    return 0;
}

int eval(int x, char op, int y) {
    if (op == '+')
        return x + y;
    else if (op == '-')
        return x - y;
    else if (op == '*')
        return x * y;
    else if (op == '/')
        return x / y;
    else
        return x % y;
}


void popAndEval(Stack &operators, Stack &values) {
    char op = operators.top();
    operators.pop();
    int v2 = values.top();
    values.pop();
    int v1 = values.top();
    values.pop();
    int v3 = eval(v1, op, v2);
    values.push(v3);
}

void processExpression(Token inputToken, TokenReader* tr)
{
    /**********************************************/
    /* Declare both stack pointers here      */
    Stack operators;
    Stack values;

    /* Loop until the expression reaches its End */
    while (inputToken.equalsType(EOLN) == false)
    {
        /* The expression contain a VALUE */
        if (inputToken.equalsType(VALUE))
        {
            values.push(inputToken.getValue());
        }

        /* The expression contains an OPERATOR */
        else if (inputToken.equalsType(OPERATOR))
        {
            if (inputToken.getOperator() == '(') {
                operators.push(inputToken.getOperator());
            }
            
            if (inputToken.getOperator() == '+' || inputToken.getOperator() == '-') {
                while (operators.isEmpty() == false && (operators.top() == '+' || operators.top() == '-' || operators.top() == '*' || operators.top() == '/' || operators.top() == '%')) {
                    popAndEval(operators, values);
                }
                operators.push(inputToken.getOperator());
            }

            if (inputToken.getOperator() == '*' || inputToken.getOperator() == '/' || inputToken.getOperator() == '%') {
                while (operators.isEmpty() == false && (operators.top() == '*' || operators.top() == '/' || operators.top() == '%')) {
                    popAndEval(operators, values);
                }
                operators.push(inputToken.getOperator());
            }

            if (inputToken.getOperator() == ')') {
                while (operators.isEmpty() == false && operators.top() != '(') {
                    popAndEval(operators, values);
                }
                if (operators.isEmpty() == true) {
                    printf("Invalid Expression.\n");
                }
                else {
                    operators.pop();
                }
            }
        }

        /* get next token from input */
        inputToken = tr->getNextToken();
    }

    /* The expression has reached its end */
    if (inputToken.equalsType(EOLN)) {
        while (operators.isEmpty() == false) {
            popAndEval(operators, values);            
        }
        int answer = values.top();        
        values.pop();
        if (values.isEmpty() == false) {
            printf("Invalid Expression.\n");
        }
        else {
        	printf("\nExpression result: %d\n", answer);
        }
    }
    // add code to perform this operation here
    operators.reset();
    values.reset();

    printf("\n");
}
