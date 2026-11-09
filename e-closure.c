#include <stdio.h>
#define MAX 10

int graph[MAX][MAX];
int trans[MAX][MAX][MAX];
int visited[MAX];
int n, m;

void dfs(int v)
{
    visited[v] = 1;
    printf("q%d ", v);

    for (int i = 0; i < n; i++)
    {
        if (graph[v][i] && !visited[i])
            dfs(i);
    }
}

int main()
{
    int e, t, u, v;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    for (int i = 0; i < e; i++)
    {
        scanf("%d%d", &u, &v);
        graph[u][v] = 1;
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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){


            visited[j] = 0; //set all states to unvisited before doing nexta
	   }

        printf("E-Closure(q%d): ", i);
        dfs(i);
        printf("\n");
    }

    return 0;
}
