#include <stdio.h>
#define MAX 10

int n, m;

int epsilon[MAX][MAX];
int trans[MAX][MAX][MAX];
int closure[MAX][MAX];
int visited[MAX];

void dfs(int start, int v)
{
    visited[v] = 1;
    closure[start][v] = 1;

    for (int i = 0; i < n; i++)
    {
        if (epsilon[v][i] && !visited[i])
            dfs(start, i);
    }
}

int main()
{
    int e, t, u, v;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    printf("Enter epsilon transitions:\n");

    for (int i = 0; i < e; i++)
    {
        scanf("%d%d", &u, &v);
        epsilon[u][v] = 1;
    }

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    for (int j = 0; j < m; j++)
    {
        printf("Enter number of transitions for input symbol %d: ", j + 1);
        scanf("%d", &t);

        for (int i = 0; i < t; i++)
        {
            scanf("%d%d", &u, &v);
            trans[j][u][v] = 1;
        }
    }

    // Find epsilon closure of every state
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            visited[j] = 0;

        dfs(i, i);
    }

    // Construct equivalent NFA
    printf("\nEquivalent NFA Transition Table\n");

    for (int state = 0; state < n; state++)
    {
        printf("\nq%d:\n", state);

        for (int symbol = 0; symbol < m; symbol++)
        {
            int result[MAX] = {0};

            // Take every state in epsilon closure
            for (int i = 0; i < n; i++)
            {
                if (closure[state][i])
                {
                    // Follow input transition
                    for (int j = 0; j < n; j++)
                    {
                        if (trans[symbol][i][j])
                        {
                            // Take epsilon closure of reached state
                            for (int k = 0; k < n; k++)
                            {
                                if (closure[j][k])
                                    result[k] = 1;
                            }
                        }
                    }
                }
            }

            printf("%d -> ", symbol + 1);

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

            printf("\n");
        }
    }

    return 0;
}