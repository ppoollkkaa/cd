
#include <stdio.h>
#include <ctype.h>

char stack[50];
char operands[50][10];

int top = -1;
int opTop = -1;
int temp = 1;

int precedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}

void generate(char op)
{
    if (op == '=')
    {
        printf("%s = %s\n",
               operands[opTop - 1], operands[opTop]);

        opTop--;
        return;
    }

    printf("t%d = %s %c %s\n",
           temp, operands[opTop - 1], op, operands[opTop]);

    sprintf(operands[opTop - 1], "t%d", temp);

    temp++;
    opTop--;
}

int main()
{
    char expr[100];
    char ch, op;

    printf("Enter expression: ");
    scanf("%99s", expr);

    printf("\nThree Address Code:\n");

    for (int i = 0; expr[i] != '\0'; i++)
    {
        ch = expr[i];

        if (isalnum(ch))
        {
            opTop++;
            operands[opTop][0] = ch;
            operands[opTop][1] = '\0';
        }

        else if (ch == '(')
        {
            stack[++top] = ch;
        }

        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                op = stack[top--];
                generate(op);
            }

            if (top != -1)
                top--;
        }

        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch))
            {
                op = stack[top--];
                generate(op);
            }

            stack[++top] = ch;
        }
    }

    while (top != -1)
    {
        op = stack[top--];
        generate(op);
    }

    return 0;
}
