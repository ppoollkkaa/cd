#include <stdio.h>
#include <string.h>


char stack[100];
char input[100];


int top = -1;
int inputPosition = 0;


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
    /* E + E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }


    /* E * E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top = top - 2;
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


    /* i -> E */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }


    return 0;
}


int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%s", input);


    strcat(input, "$");


    printf("\nStack\t\tInput\t\tAction\n");


    top++;
    stack[top] = '$';


    while (input[inputPosition] != '$')
    {
        /* SHIFT */
        top++;
        stack[top] = input[inputPosition];
        inputPosition++;


        displayStack();
        printf("\t\t%s\t\tShift\n", input + inputPosition);


        /* REDUCE */
        while (reduce())
        {
            displayStack();
            printf("\t\t%s\t\tReduce\n", input + inputPosition);
        }
    }


    /* Perform remaining reductions */
    while (reduce())
    {
        displayStack();
        printf("\t\t$\t\tReduce\n");
    }


    if (top == 1 && stack[0] == '$' && stack[1] == 'E')
    {
        printf("\nExpression Accepted\n");
    }
    else
    {
        printf("\nExpression Rejected\n");
    }


    return 0;
}





