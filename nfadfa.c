
#include <stdio.h>
#include <string.h>

#define MAX 10

int main()
{
    int n, m;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    int trans[MAX][MAX];

    printf("Enter NFA transition table (bitmask values):\n");
    printf("Example: If A->{A,C}, enter 5 (101 in binary).\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &trans[i][j]);
        }
    }

    // Stores all DFA states.
    // Each DFA state is represented by a bitmask.
    int dfaStates[100];

    int front = 0;
    int rear = 0;

    // Initial DFA state = {A}
    // Binary 001 = decimal 1
    dfaStates[rear++] = 1;

    printf("\nEquivalent DFA:\n");

    // Process every discovered DFA state using BFS
    while (front < rear)
    {
        // Get the next DFA state from the queue
        int current = dfaStates[front++];

        // Print the current DFA state
        printf("{ ");

        for (int i = 0; i < n; i++)
        {
            // Check whether NFA state i is present
            // in the current DFA state
            if (current & (1 << i))
            {
                printf("%c", 'A' + i);
            }
        }

        printf("}");

        // Find transitions for every input symbol
        for (int s = 0; s < m; s++)
        {
            // Stores the set of NFA states reached
            int next = 0;

            // Check every NFA state in current DFA state
            for (int i = 0; i < n; i++)
            {
                if (current & (1 << i))
                {
                    // Combine transitions using bitwise OR
                    next |= trans[i][s];
                }
            }

            // Print the resulting DFA transition
            printf("\n --%c--> { ", s);

            for (int i = 0; i < n; i++)
            {
                if (next & (1 << i))
                {
                    printf("%c ", 'A' + i);
                }
            }

            printf("}");

            // Check whether this DFA state was already discovered
            int found = 0;

            for (int i = 0; i < rear; i++)
            {
                if (dfaStates[i] == next)
                {
                    found = 1;
                    break;
                }
            }

            // If new, add it to the queue for processing
            if (!found)
            {
                dfaStates[rear++] = next;
            }
        }

        printf("\n");
    }

    return 0;
}
