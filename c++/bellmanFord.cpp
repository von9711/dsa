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
typedef vector<li> graph;

vector<pr> bellmanFord(graph &g, int s);
void printGraph(graph &g);
void printPath(vector<pr> &path, int u, int v);
void printAllPath(vector<pr> &path, int s);
bool isNegCycleExist(graph &g, vector<pr> &path);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e, n, w;
    cout << "Enter no. of vertices: ";
    cin >> n;
    graph g(n);
    cout << "Enter no. of edges: ";
    cin >> e;
    cout << "\nEnter source, destination & weight\n";
    for (int i = 0; i < e; ++i)
    {
        cin >> u >> v >> w;
        g[u].push_back(make_pair(w, v));
        //g[v].push_back(u);
    }
    int s;
    cout << "\nEnter the source: ";
    cin >> s;

    auto start = high_resolution_clock::now();

    vector<pr> path = bellmanFord(g, s);
    if(!isNegCycleExist(g,path))
        printAllPath(path, s);
    else
        cout<<"\nNegative cycle exist, no solution\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<pr> bellmanFord(graph &g, int s) {
    vector<pr> path(g.size(),make_pair(INT32_MAX,-1));
    int n = g.size();
    path[s].first = 0;
    for(int i = 0; i < g.size() - 1; ++i) {
        for(int u = 0; u < g.size(); ++u) {
            long uw = path[u].first;
            for(auto e : g[u]) {
                int v = e.second;
                long w = path[v].first;
                if(w > uw + e.first) {
                    path[v].first = uw + e.first;
                    path[v].second = u;
                }
            }
        }
    }
    return path;
}

bool isNegCycleExist(graph &g, vector<pr> &path) {
    for (int u = 0; u < g.size(); ++u)
    {
        long uw = path[u].first;
        for (auto e : g[u])
        {
            int v = e.second;
            long w = path[e.second].first;
            if (w > uw + e.first)
                return true;
        }
    }
    return false;
}

void printAllPath(vector<pr> &path, int s)
{
    cout << "\nAll paths\n";
    for (int i = 0; i < path.size(); ++i)
        cout << s << " -> " << i << " cost: " << path[i].first << "\n";
}

void printPath(vector<pr> &path, int u, int v)
{
    if (u == v)
    {
        cout << u;
        return;
    }
    printPath(path, u, path[v].second);
    cout << " -> " << v;
}

void printGraph(graph &g)
{
    for (int i = 0; i < g.size(); ++i)
    {
        cout << i << " : ";
        for (auto v : g[i])
            cout << v.second << ", ";
        cout << "\n";
    }
}
