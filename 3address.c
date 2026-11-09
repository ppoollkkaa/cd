#include <stdio.h>
#include <ctype.h>

char stack[50];
char operands[50][10];

int top = -1;
int opTop = -1;
int temp = 1;

struct Quadruple {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
};

struct Quadruple quad[50];
int qTop = -1;


int precedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}


char pop()
{
    char ch = stack[top];
    top--;
    return ch;
}

// Generate three-address code for one operation
void generate(char op)
{
    if (op == '=') {
        qTop++;

        quad[qTop].op = op;
        sprintf(quad[qTop].arg1, "%s", operands[opTop]);
        sprintf(quad[qTop].arg2, "-");
        sprintf(quad[qTop].result, "%s", operands[opTop - 1]);

        printf("%s = %s\n",
               operands[opTop - 1], operands[opTop]);

        opTop--;
        return;
    }

    qTop++;

    quad[qTop].op = op;

    sprintf(quad[qTop].arg1, "%s", operands[opTop - 1]);
    sprintf(quad[qTop].arg2, "%s", operands[opTop]);
    sprintf(quad[qTop].result, "t%d", temp);

    printf("t%d = %s %c %s\n",
           temp, operands[opTop - 1], op, operands[opTop]);

    sprintf(operands[opTop - 1], "t%d", temp);

    temp++;
    opTop--;
}

void printQuadruples()
{
    printf("\nQuadruple Table:\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; i <= qTop; i++)
    {
        printf("%c\t%s\t%s\t%s\n",
               quad[i].op,
               quad[i].arg1,
               quad[i].arg2,
               quad[i].result);
    }
}

int main()
{
    char expr[100];
    int i;
    char ch, op;

    printf("Enter expression: ");
    scanf("%99s", expr);

    printf("\nThree Address Code:\n");

    for (i = 0; expr[i] != '\0'; i++)
    {
        ch = expr[i];

        // If the character is an operand
        if (isalnum(ch))
        {
            opTop++;
            operands[opTop][0] = ch;
            operands[opTop][1] = '\0';
        }

        // If opening parenthesis
        else if (ch == '(')
        {
            top++;
            stack[top] = ch;
        }

        // If closing parenthesis
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                op = stack[top];
                top--;
                generate(op);
            }

            if (top != -1)
                top--;
        }

        // If operator
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch))
            {
                op = stack[top];
                top--;
                generate(op);
            }

            top++;
            stack[top] = ch;
        }
    }

    // Process remaining operators
    while (top != -1)
    {
        op = stack[top];
        top--;
        generate(op);
    }

    printQuadruples();

    return 0;
}

