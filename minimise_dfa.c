#include <stdio.h>
#define MAX 10

int main()
{
    int n, m;
    int trans[MAX][MAX];
    int final[MAX] = {0};
    int marked[MAX][MAX] = {0};
    int class[MAX];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("\nEnter transitions:\n");

    for (int i = 0; i < n; i++)
    {
        printf("q%d: ", i);

        for (int j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);
    }

    int f;

    printf("\nEnter number of final states: ");
    scanf("%d", &f);

    printf("Enter final states: ");

    for (int i = 0; i < f; i++)
    {
        int state;
        scanf("%d", &state);
        final[state] = 1;
    }

    // Step 1: Mark final and non-final pairs
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (final[i] != final[j])
                marked[i][j] = 1;
        }
    }

    // Step 2: Repeatedly mark distinguishable pairs
    int changed;

    do
    {
        changed = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (marked[i][j])
                    continue;

                for (int symbol = 0; symbol < m; symbol++)
                {
                    int p = trans[i][symbol];
                    int q = trans[j][symbol];

                    if (p > q)
                    {
                        int temp = p;
                        p = q;
                        q = temp;
                    }

                    if (p != q && marked[p][q])
                    {
                        marked[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }

    } while (changed);

    // Step 3: Create equivalence classes
    for (int i = 0; i < n; i++)
        class[i] = -1;

    int classCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (class[i] != -1)
            continue;

        class[i] = classCount;

        for (int j = i + 1; j < n; j++)
        {
            if (!marked[i][j])
                class[j] = classCount;
        }

        classCount++;
    }

    // Print equivalent states
    printf("\nEquivalent States:\n");

    for (int c = 0; c < classCount; c++)
    {
        printf("D%d = { ", c);

        for (int i = 0; i < n; i++)
        {
            if (class[i] == c)
                printf("q%d ", i);
        }

        printf("}\n");
    }

    // Print minimized DFA
    printf("\nMinimized DFA:\n");
    printf("State\t");

    for (int symbol = 0; symbol < m; symbol++)
        printf("%d\t", symbol);

    printf("\n");

    for (int c = 0; c < classCount; c++)
    {
        int representative = -1;

        for (int i = 0; i < n; i++)
        {
            if (class[i] == c)
            {
                representative = i;
                break;
            }
        }

        printf("D%d\t", c);

        for (int symbol = 0; symbol < m; symbol++)
            printf("D%d\t", class[trans[representative][symbol]]);

        printf("\n");
    }

    printf("\nStart State: D%d\n", class[0]);

    printf("Final States: ");

    for (int c = 0; c < classCount; c++)
    {
        for (int i = 0; i < n; i++)
        {
            if (class[i] == c && final[i])
            {
                printf("D%d ", c);
                break;
            }
        }
    }

    printf("\n");

    return 0;
}