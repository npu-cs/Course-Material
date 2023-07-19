#include <iostream>
#include <stack>
#include <limits>

using namespace std;

const int MAXSIZE = 100;

struct Graph
{
    int Vnum;
    int arc[MAXSIZE][MAXSIZE];
};

struct Dij
{
    bool visited[MAXSIZE];
    int length[MAXSIZE];
};

void init(Graph &G, Dij &D)
{
    cin >> G.Vnum;
    for (int i = 0; i < G.Vnum; i++)
    {
        for (int j = 0; j < G.Vnum; j++)
        {
            cin >> G.arc[i][j];
        }
    }
    for (int i = 0; i < G.Vnum; i++)
    {
        D.visited[i] = false;
        D.length[i] = G.arc[0][i];
    }
    D.visited[0] = true;
}

bool is_finished(const Graph &G, const Dij &D)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        if (!D.visited[i])
        {
            return false;
        }
    }
    return true;
}

int find_minlength_V(const Graph &G, const Dij &D)
{
    int min = numeric_limits<int>::max();
    int min_V;
    for (int i = 0; i < G.Vnum; i++)
    {
        if (!D.visited[i] && D.length[i] < min)
        {
            min = D.length[i];
            min_V = i;
        }
    }
    return min_V;
}

void update_arc_V(Graph &G, Dij &D, int v)
{
    D.visited[v] = true;
    for (int i = 0; i < G.Vnum; i++)
    {
        if (!D.visited[i] && D.length[v] + G.arc[i][v] < D.length[i])
        {
            D.length[i] = D.length[v] + G.arc[i][v];
        }
    }
}

void calculate_minlength_for_each_V(Graph &G, Dij &D)
{
    while (!is_finished(G, D))
    {
        int v = find_minlength_V(G, D);
        update_arc_V(G, D, v);
    }
}

stack<int> find_path(Graph &G, Dij &D)
{
    int start, end;
    cin >> start >> end;
    stack<int> S;
    S.push(end);
    while (end != start)
    {
        for (int i = 0; i < G.Vnum; i++)
        {
            if (G.arc[i][end] != numeric_limits<int>::max() && D.length[i] < D.length[end] && D.length[i] + G.arc[i][end] == D.length[end])
            {
                S.push(i);
                end = i;
            }
        }
    }
    return S;
}

void print_path(stack<int> &S)
{
    while (!S.empty())
    {
        cout << S.top() << endl;
        S.pop();
    }
}

int main()
{
    Graph G;
    Dij D;
    init(G, D);
    calculate_minlength_for_each_V(G, D);
    stack<int> path = find_path(G, D);
    print_path(path);
    return 0;
}
