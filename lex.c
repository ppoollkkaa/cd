
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char str[]){
    char keywords[6][10] = {
        "int", "char", "float", "if", "else", "return"
    };

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    char ch, str[50];
    int i;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("File not found");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        if (isalpha(ch))
        {
            i = 0;
            str[i++] = ch;

            while (isalnum(ch = fgetc(fp)))
                str[i++] = ch;

            str[i] = '\0';

            if (isKeyword(str))
                printf("Keyword : %s\n", str);
            else
                printf("Identifier : %s\n", str);

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        else if (isdigit(ch))
        {
            printf("Number : %c", ch);

            while (isdigit(ch = fgetc(fp)))
                printf("%c", ch);

            printf("\n");

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        else
        {
            printf("Operator/Special Symbol : %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
