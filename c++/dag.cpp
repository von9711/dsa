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

vector<pr> DAG(graph &g, int s);
void dfsVisit(graph &g, vector<bool> &visited, list<int> &path, int u);
list<int> topoSort(graph &g);
void printGraph(graph &g);
void printPath(vector<pr> &path, int u, int v);
void printAllPath(vector<pr> &path, int s);

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
    cout << "Enter the source: ";
    cin >> s;

    auto start = high_resolution_clock::now();

    vector<pr> path = DAG(g,s);
    printAllPath(path,s);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<pr> DAG(graph &g,int s) {
    list<int> path = topoSort(g);
    vector<pr> shortPath(g.size(),make_pair(INT32_MAX,-1));
    shortPath[s].first = 0;

    auto itr = path.begin();
    for(; itr != path.end(); ++itr) {
        if(*itr == s)
            break;
    }
    for(; itr != path.end(); ++itr) {
        int uw = shortPath[*itr].first;
        for(auto v : g[*itr]) {
            int w = shortPath[v.second].first;
            if(w > uw + v.first) {
                shortPath[v.second].first = uw + v.first;
                shortPath[v.second].second = *itr;
            }
        }
    }
    return shortPath;
}

list<int> topoSort(graph &g)
{
    vector<bool> visited(g.size(),false);
    list<int> path;
    for(int i = 0; i < g.size(); ++i) {
        if(!visited[i])
            dfsVisit(g,visited,path,i);
    }
    return path;
}

void dfsVisit(graph &g, vector<bool> &visited, list<int> &path, int u) {
    visited[u] = true;
    for(auto v : g[u]) {
        if(!visited[v.second])
            dfsVisit(g,visited,path,v.second);
    }
    path.push_front(u);
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