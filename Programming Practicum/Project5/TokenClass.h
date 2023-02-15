#pragma once
using namespace std;


enum TokenType {
    ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};


// Class to hold the Token information
class Token
{
private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

public:

    // Default to initialize to the ERROR TokenType
    Token()
    {
        type = ERROR;
        op = '$';
        val = -999;
    }

    // Initialize to a specific TokenType
    Token(TokenType t)
    {
        type = t;
        op = '$';
        val = -999;
    }

    // Set to a specific TokenType
    void setToType(TokenType t)
    {
        type = t;
        op = '$';
        val = -999;
    }

    // Set to a OPERATOR TokenType with specific operator value
    void setToOperator(char c)
    {
        type = OPERATOR;
        op = c;
        val = -999;
    }

    // Set to a VALUE TokenType with a specific numeric value
    void setToValue(int v)
    {
        type = VALUE;
        op = '$';
        val = v;
    }

    // return true if the Current Token is of the given TokenType
    bool equalsType(TokenType t)
    {
        if (type == t)
            return true;
        else
            return false;
    }

    // return true if the Current Token is of the OPERATOR TokenType
    //     and contains the given operator character
    bool equalsOperator(char c)
    {
        if (type == OPERATOR && op == c)
            return true;
        else
            return false;
    }

    // Return the Operator for the current Token
    //   verify the current Token is of the OPERATOR TokenType
    char getOperator()
    {
        if (type == OPERATOR)
            return op;
        else
            return '$';   // using $ to indicate an error value
    }

    // Return the Value for the current Token
    //   verify the current token is of the value TokenType
    int getValue()
    {
        if (type == VALUE)
            return val;
        else
            return -999;  // using -999 to indicate an error value
    }
};
