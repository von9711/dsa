//DAG shortest path - topological sort
#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;
using namespace std::chrono;

typedef pair<int, int> pr;
typedef list<pr> li;
typedef vector<vector<int>> graph;

graph floydWarshall(graph &g);
graph transitiveGraph(graph &g);
void printGraph(graph &g);
void printPath(graph &g, int u, int v);
void printAllPath(graph &g);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e, n, w;
    cout << "Enter no. of vertices: ";
    cin >> n;
    graph g(n,vector<int>(n));
    cout<<"Enter weight in adjacency matrix\n";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            cin>>g[i][j];
    }

    auto start = high_resolution_clock::now();

    graph parent = floydWarshall(g);
    printAllPath(g);
    /*cout<<"\nPath from 0 to 2\n";
    printPath(parent,0,2);*/
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

graph floydWarshall(graph &g) {
    int n = g.size();
    graph parent(n,vector<int>(n));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(g[i][j] == 0 || g[i][j] == 9999)
                parent[i][j] = -1;
            else
                parent[i][j] = i;
        }
    }

    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                long w = g[i][j], wik = g[i][k], wij = g[k][j];
                if(i != j && w > wik + wij) {
                    g[i][j] = wik + wij;
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
    return parent;
}

graph transitiveGraph(graph &g)
{
    int n = g.size();
    graph tg(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (g[i][j] == 9999)
                tg[i][j] = 0;
            else
                tg[i][j] = 1;
        }
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                tg[i][j] = tg[i][j] || (tg[i][k] && tg[k][j]);
            }
        }
    }
    return tg;
}

void printAllPath(graph &g)
{
    cout << "\nAll paths\n";
    for (int i = 0; i < g.size(); ++i) {
        for(int j = 0; j < g.size(); ++j)
            cout << g[i][j] << " ";
        cout<<"\n";
    }
}

void printPath(graph &g, int u, int v)
{
    if(u == v)
        cout<<u;
    else if (g[u][v] == -1)
        cout<<"Path doesn't exist";
    else {
        printPath(g,u,g[u][v]);
        cout<<" -> "<<v;
    }
}

void printGraph(graph &g)
{
}
