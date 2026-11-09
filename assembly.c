#include <stdio.h>
#include <string.h>

int main(){
    char line[100];
    char a[20], b[20], c[20], op[5], label[20];
    int n;

    printf("Enter number of instructions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC:\n");

    for (int i = 0; i < n; i++)
    {
        fgets(line, sizeof(line), stdin);

        // Conditional jump
        if (sscanf(line, "if %19s %4s %19s goto %19s",
                   a, op, b, label) == 4)
        {
            printf("MOV AX,%s\n", a);
            printf("CMP AX,%s\n", b);

            if (strcmp(op, "<") == 0)
                printf("JL %s\n", label);
            else if (strcmp(op, ">") == 0)
                printf("JG %s\n", label);
            else if (strcmp(op, "==") == 0)
                printf("JE %s\n", label);
            else if (strcmp(op, "!=") == 0)
                printf("JNE %s\n", label);
            else if (strcmp(op, "<=") == 0)
                printf("JLE %s\n", label);
            else if (strcmp(op, ">=") == 0)
                printf("JGE %s\n", label);
        }

        // Unconditional jump
        else if (sscanf(line, "goto %19s", label) == 1)
        {
            printf("JMP %s\n", label);
        }

        // Arithmetic operation
        else if (sscanf(line, "%19s = %19s %4s %19s", a, b, op, c) == 4)
        {
            printf("MOV AX,%s\n", b);
            printf("MOV BX,%s\n", c);

            if (strcmp(op, "+") == 0)
                printf("ADD AX,BX\n");
            else if (strcmp(op, "-") == 0)
                printf("SUB AX,BX\n");
            else if (strcmp(op, "*") == 0)
                printf("MUL BX\n");
            else if (strcmp(op, "/") == 0)
            {
                printf("XOR DX,DX\n");
                printf("DIV BX\n");
            }

            printf("MOV %s,AX\n", a);
        }

        // Simple assignment
        else if (sscanf(line, "%19s = %19s", a, b) == 2)
        {
            printf("MOV AX,%s\n", b);
            printf("MOV %s,AX\n", a);
        }

        // Label
        else if (sscanf(line, "%19[^:]:", label) == 1)
        {
            printf("%s:\n", label);
        }
    }

    return 0;
}
