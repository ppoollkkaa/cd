#include <stdio.h>
#define MAX 10

int n, m;

int trans[MAX][MAX][MAX];

int dfa[MAX][MAX];
int dfaCount = 1;

// Check whether subset already exists
int exists(int result[])
{
    for (int i = 0; i < dfaCount; i++)
    {
        int same = 1;

        for (int j = 0; j < n; j++)
        {
            if (dfa[i][j] != result[j])
            {
                same = 0;
                break;
            }
        }

        if (same)
            return i;
    }

    return -1;
}

int main()
{
    int t, u, v;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    for (int j = 0; j < m; j++)
    {
        printf("\nEnter number of transitions for input symbol %d: ", j);
        scanf("%d", &t);

        for (int i = 0; i < t; i++)
        {
            scanf("%d%d", &u, &v);
            trans[j][u][v] = 1;
        }
    }

    // Start DFA state = {q0}
    dfa[0][0] = 1;

    // Process every DFA state
    for (int state = 0; state < dfaCount; state++)
    {
        printf("\nD%d = { ", state);

        for (int i = 0; i < n; i++)
        {
            if (dfa[state][i])
                printf("q%d ", i);
        }

        printf("}\n");

        for (int symbol = 0; symbol < m; symbol++)
        {
            int result[MAX] = {0};

            // Take every NFA state in current DFA state
            for (int i = 0; i < n; i++)
            {
                if (dfa[state][i])
                {
                    // Follow input symbol
                    for (int j = 0; j < n; j++)
                    {
                        if (trans[symbol][i][j])
                            result[j] = 1;
                    }
                }
            }

            printf("On %d -> { ", symbol);

            int printed = 0;

            for (int i = 0; i < n; i++)
            {
                if (result[i])
                {
                    printf("q%d ", i);
                    printed = 1;
                }
            }

            if (!printed)
                printf("NULL");

            printf("}\n");

            // Add new DFA state if not already present
            if (exists(result) == -1)
            {
                for (int i = 0; i < n; i++)
                    dfa[dfaCount][i] = result[i];

                dfaCount++;
            }
        }
    }

    // Print DFA transition table
    printf("\nDFA Transition Table\n");

    printf("State\t");

    for (int symbol = 0; symbol < m; symbol++)
        printf("%d\t", symbol);

    printf("\n");

    for (int state = 0; state < dfaCount; state++)
    {
        printf("D%d { ", state);

        for (int i = 0; i < n; i++)
        {
            if (dfa[state][i])
                printf("q%d ", i);
        }

        printf("}\t");

        for (int symbol = 0; symbol < m; symbol++)
        {
            int result[MAX] = {0};

            for (int i = 0; i < n; i++)
            {
                if (dfa[state][i])
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (trans[symbol][i][j])
                            result[j] = 1;
                    }
                }
            }

            int destination = exists(result);

            printf("D%d\t", destination);
        }

        printf("\n");
    }

    return 0;
}