#include <stdio.h>
#include <string.h>
#include <ctype.h>


char prod[20][20];
char first[10][20], follow[10][20];
char nonterm[10];
int n, nt = 0;


int isNonTerminal(char c)
{
    return c >= 'A' && c <= 'Z';
}


void add(char set[], char c)
{
    int i;


    for (i = 0; set[i] != '\0'; i++)
        if (set[i] == c)
            return;


    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
}


int getIndex(char c)
{
    int i;


    for (i = 0; i < nt; i++)
        if (nonterm[i] == c)
            return i;


    return -1;
}


void findFirst(int index)
{
    int p, j;
    char lhs, c;
    int nullable;


    lhs = nonterm[index];


    for (p = 0; p < n; p++)
    {
        if (prod[p][0] != lhs)
            continue;


        j = 2;
        nullable = 1;


        while (prod[p][j] != '\0' && nullable)
        {
            c = prod[p][j];


            if (c == '#')
            {
                add(first[index], '#');
                nullable = 0;
            }
            else if (!isNonTerminal(c))
            {
                add(first[index], c);
                nullable = 0;
            }
            else
            {
                int k = getIndex(c);
                if (k == -1)
                {
                    nullable = 0;
                    break;
                }


                findFirst(k);


                int hasEpsilon = 0;
                int x;


                for (x = 0; first[k][x] != '\0'; x++)
                {
                    if (first[k][x] == '#')
                        hasEpsilon = 1;
                    else
                        add(first[index], first[k][x]);
                }


                if (hasEpsilon)
                    j++;
                else
                    nullable = 0;
            }
        }


        if (nullable)
            add(first[index], '#');
    }
}


void findFollow(int index)
{
    int p, j, k, x;
    char lhs, c;


    lhs = nonterm[index];


    if (index == 0)
        add(follow[index], '$');


    for (p = 0; p < n; p++)
    {
        for (j = 2; prod[p][j] != '\0'; j++)
        {
            if (prod[p][j] != lhs)
                continue;


            int nullable = 1;
            int pos = j + 1;


            while (prod[p][pos] != '\0' && nullable)
            {
                c = prod[p][pos];


                if (!isNonTerminal(c))
                {
                    if (c != '#')
                        add(follow[index], c);


                    nullable = 0;
                }
                else
                {
                    k = getIndex(c);
                    if (k == -1)
                    {
                        nullable = 0;
                        break;
                    }


                    findFirst(k);


                    int hasEpsilon = 0;


                    for (x = 0; first[k][x] != '\0'; x++)
                    {
                        if (first[k][x] == '#')
                            hasEpsilon = 1;
                        else
                            add(follow[index], first[k][x]);
                    }


                    if (hasEpsilon)
                        pos++;
                    else
                        nullable = 0;
                }
            }


            if (prod[p][pos] == '\0' || nullable)
            {
                int a = getIndex(prod[p][0]);


                if (a != index)
                {
                    findFollow(a);


                    for (x = 0; follow[a][x] != '\0'; x++)
                        add(follow[index], follow[a][x]);
                }
            }
        }
    }
}


int main()
{
    int i, j;


    printf("Enter number of productions: ");
    scanf("%d", &n);


    printf("Enter productions (use # for epsilon):\n");


    for (i = 0; i < n; i++)
    {
        scanf("%s", prod[i]);


        char c = prod[i][0];
        int found = 0;


        for (j = 0; j < nt; j++)
            if (nonterm[j] == c)
                found = 1;


        if (!found)
            nonterm[nt++] = c;
    }


    for (i = 0; i < nt; i++)
        findFirst(i);


    for (i = 0; i < nt; i++)
        findFollow(i);


    printf("\nFIRST sets:\n");


    for (i = 0; i < nt; i++)
        printf("FIRST(%c) = {%s}\n", nonterm[i], first[i]);


    printf("\nFOLLOW sets:\n");


    for (i = 0; i < nt; i++)
        printf("FOLLOW(%c) = {%s}\n", nonterm[i], follow[i]);


    return 0;
}


