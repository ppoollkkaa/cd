#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char instruction[30];
    char operation[10];

    printf("Enter number of instructions: ");
    scanf("%d", &n);

    printf("Enter the intermediate code:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%29s", instruction);

        switch (instruction[3])
        {
            case '+':
                strcpy(operation, "ADD");
                break;

            case '-':
                strcpy(operation, "SUB");
                break;

            case '*':
                strcpy(operation, "MUL");
                break;

            case '/':
                strcpy(operation, "DIV");
                break;

            default:
                printf("Invalid operator\n");
                return 1;
        }

        printf("\nMOV %c, R%d", instruction[2], i);
        printf("\n%s %c, R%d", operation, instruction[4], i);
        printf("\nMOV R%d, %c\n", i, instruction[0]);
    }

    return 0;
}
