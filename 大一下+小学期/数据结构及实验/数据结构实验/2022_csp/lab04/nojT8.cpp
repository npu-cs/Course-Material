#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAXSIZE = 100;
const int INF = 10000;

int ans[MAXSIZE] = {0};

struct Graph
{
    int data[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    int Vnum, Anum;
};

struct dijkstra
{
    bool visited[MAXSIZE];
    int length[MAXSIZE];
};

void initGraph(Graph &G)
{
    cin >> G.Vnum;
    for (int i = 0; i < G.Vnum; i++)
    {
        for (int j = 0; j < G.Vnum; j++)
        {
            cin >> G.arc[i][j];
        }
    }
}

void initDij(Graph &G, dijkstra &D)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        D.visited[i] = false;
        D.length[i] = INF;
    }
    D.visited[0] = true;
    D.length[0] = 0;
    for (int i = 0; i < G.Vnum; i++)
    {
        if (G.arc[0][i] != 10000)
        {
            D.length[i] = G.arc[0][i];
        }
    }
}

int searchMinLengthV(Graph &G, dijkstra &D)
{
    int min = 10000;
    int r;
    for (int i = 0; i < G.Vnum; i++)
    {
        if (!D.visited[i] && D.length[i] < min)
        {
            min = D.length[i];
            r = i;
        }
    }
    D.visited[r] = true;
    return r;
}

bool judgeFinished(Graph &G, dijkstra &D)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        if (!D.visited[i])
            return false;
    }
    return true;
}

int min(int a, int b)
{
    return a > b ? b : a;
}

void updateArcV(int V0, Graph &G, dijkstra &D)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        if (G.arc[V0][i] != 10000 && !D.visited[i])
        {
            D.length[i] = min(D.length[i], D.length[V0] + G.arc[V0][i]);
        }
    }
}

void findMinPath(Graph &G, dijkstra &D)
{
    initDij(G, D);
    for (int i = 0; i < G.Vnum - 1; i++)
    {
        int t = searchMinLengthV(G, D);
        if (judgeFinished(G, D))
            return;
        updateArcV(t, G, D);
    }
}

void printPath(Graph &G, dijkstra &D)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        cout << D.length[i] << endl;
    }
}

int main()
{
    Graph G;
    dijkstra D;
    initGraph(G);
    int ans[MAXSIZE] = {0};
    findMinPath(G, D);
    printPath(G, D);
    return 0;
}
