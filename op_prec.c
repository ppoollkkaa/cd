#include <stdio.h>
#include <string.h>


char stack[100];
char input[100];


int top = -1;
int inputPosition = 0;


/* Precedence table: +, -, *, /, (, ), i, $ */
char table[8][8] = {
    {'>', '>', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '<', '<', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '<', '>'},
    {'<', '<', '<', '<', '<', '=', '<', ' '},
    {'>', '>', '>', '>', ' ', '>', ' ', '>'},
    {'>', '>', '>', '>', ' ', '>', ' ', '>'},
    {'<', '<', '<', '<', '<', ' ', '<', ' '}
};


int findIndex(char symbol)
{
    switch (symbol)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case 'i': return 6;
        case '$': return 7;
        default: return -1;
    }
}


void displayStack()
{
    int i;


    for (i = 0; i <= top; i++)
    {
        printf("%c", stack[i]);
    }
}


int reduce()
{
    /* i -> E */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }


    /* (E) -> E */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }


    /* E+E, E-E, E*E, E/E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top] == 'E' &&
        (stack[top - 1] == '+' ||
         stack[top - 1] == '-' ||
         stack[top - 1] == '*' ||
         stack[top - 1] == '/'))
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }


    return 0;
}


int main()
{
    char stackSymbol;
    char inputSymbol;


    int i;
    int row;
    int column;
    int error = 0;


    printf("Enter expression (use i for identifier): ");
    scanf("%98s", input);


    strcat(input, "$");


    printf("\nStack\t\tInput\t\tAction\n");


    /* Initialize stack */
    top = top + 1;
    stack[top] = '$';


    /* Process input until $ is reached */
    while (input[inputPosition] != '$')
    {
        /* Find the topmost terminal */
        i = top;


        while (i >= 0 && stack[i] == 'E')
        {
            i = i - 1;
        }


        if (i < 0)
        {
            error = 1;
            break;
        }


        stackSymbol = stack[i];
        inputSymbol = input[inputPosition];


        row = findIndex(stackSymbol);
        column = findIndex(inputSymbol);


        if (row == -1 || column == -1)
        {
            error = 1;
            break;
        }


        /* Check precedence table */


        if (table[row][column] == '<' ||
            table[row][column] == '=')
        {
            /* SHIFT */
            top = top + 1;
            stack[top] = inputSymbol;
            inputPosition = inputPosition + 1;


            displayStack();
            printf("\t\t%s\t\tShift\n",
                   input + inputPosition);
        }
        else if (table[row][column] == '>')
        {
            /* REDUCE */
            if (reduce())
            {
                displayStack();
                printf("\t\t%s\t\tReduce\n",
                       input + inputPosition);
            }
            else
            {
                error = 1;
                break;
            }
        }
        else
        {
            error = 1;
            break;
        }
    }


    /* Perform remaining reductions */
    while (error == 0)
    {
        /* Find the topmost terminal */
        i = top;


        while (i >= 0 && stack[i] == 'E')
        {
            i = i - 1;
        }


        if (i < 0)
        {
            error = 1;
            break;
        }


        stackSymbol = stack[i];


        row = findIndex(stackSymbol);
        column = findIndex('$');


        if (row == -1 || column == -1)
        {
            error = 1;
            break;
        }


        /* Reduce only when the table says > */
        if (table[row][column] == '>')
        {
            if (reduce())
            {
                displayStack();
                printf("\t\t$\t\tReduce\n");
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            break;
        }
    }


    /* Check acceptance */
    if (error == 0 &&
        top == 1 &&
        stack[0] == '$' &&
        stack[1] == 'E' &&
        input[inputPosition] == '$')
    {
        printf("\nExpression Accepted\n");
    }
    else
    {
        printf("\nExpression Rejected\n");
    }


    return 0;
}

