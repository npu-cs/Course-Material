#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAXSIZE = 100;
const int INF = 10000;

struct Graph
{
    int vnum;
    int arc[MAXSIZE][MAXSIZE];
    int path[MAXSIZE][MAXSIZE];
};

void init_Graph(Graph &G)
{
    cin >> G.vnum;
    for (int i = 0; i < G.vnum; i++)
    {
        for (int j = 0; j < G.vnum; j++)
        {
            cin >> G.arc[i][j];
            G.path[i][j] = -1;
        }
    }
}

void floyd(Graph &G)
{
    for (int m = 0; m < G.vnum; m++)
        for (int a = 0; a < G.vnum; a++)
            for (int b = 0; b < G.vnum; b++)
            {
                if (G.arc[a][b] > G.arc[a][m] + G.arc[m][b])
                {
                    G.arc[a][b] = G.arc[a][m] + G.arc[m][b];
                    G.path[a][b] = m;
                }
            }
}

void print_result(Graph &G)
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << G.arc[a][b] << endl;
    }
}

int main()
{
    Graph G;
    init_Graph(G);
    floyd(G);
    print_result(G);
    return 0;
}

/*
4
0 2 10 10000
2 0 7 3
10 7 0 6
10000 3 6 0
2
0 2
3 0
*/
