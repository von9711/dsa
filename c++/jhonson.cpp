//Strongly Conected componenets
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

vector<vector<int>> johnson(graph &g);
vector<int> dijkstra(graph &g, int s);
vector<int> bellmanFord(graph &g,int s);
void reweighting(graph &g, vector<int> vw);
void printGraph(graph &g);
void printPath(vector<pr> &path, int u, int v);
void printAllPath(vector<vector<int>> &path);

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

    auto start = high_resolution_clock::now();

    vector<vector<int>> path = johnson(g);
    printAllPath(path);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<vector<int>> johnson(graph &g) {
    graph g1(g);
    li l;
    int n = g.size();
    for(int i = 0; i < n; ++i)
        l.push_back(make_pair(0,i));
    g1.push_back(l);
    vector<int> vertexWeight = bellmanFord(g1,n);
    reweighting(g1,vertexWeight);
    g1.pop_back();
    vertexWeight.pop_back();
    vector<vector<int>> path(n);
    for(int i = 0; i < n; ++i) {
        vector<int> w = dijkstra(g1,i);
        for(int j = 0; j < n; ++j)
            w[j] = w[j] + vertexWeight[j] - vertexWeight[i];
        path[i] = w;
    }
    return path;
}

vector<int> bellmanFord(graph &g, int s) {
    vector<int> vw(g.size(),INT32_MAX);
    vw[s] = 0;
    for(int k = 0; k < g.size() - 1; ++k) {
        for(int i = 0; i < g.size(); ++i) {
            for(auto edge : g[i]) {
                long w = edge.first; 
                int v = edge.second;
                if(vw[v] > vw[i] + w)
                    vw[v] = vw[i] + w;
            }
        }
    }
    return vw;
}

void reweighting(graph &g, vector<int> vw) {
    for(int i = 0; i < g.size(); ++i) {
        for(auto itr = g[i].begin(); itr != g[i].end(); ++itr)
            itr->first = itr->first + vw[i] - vw[itr->second];
    }
}

vector<int> dijkstra(graph &g, int s)
{
    priority_queue<pr, vector<pr>, greater<pr>> q;
    vector<bool> visited(g.size(), false);
    //vector<pr> path(g.size(), make_pair(INT32_MAX, -1));
    vector<int> path(g.size(),INT32_MAX);
    q.push(make_pair(0, s));
    path[s] = 0;
    while (!q.empty())
    {
        pr p = q.top();
        q.pop();
        int u = p.second, uvw = path[u];
        visited[u] = true;
        for (auto edge : g[u])
        {
            int w = edge.first, v = edge.second;
            if (!visited[v] && path[v] > w + uvw)
            {
                path[v] = w + uvw;
                //path[v].second = u;
                q.push(edge);
            }
        }
    }
    return path;
}

void printAllPath(vector<vector<int>> &path)
{
    cout << "\nAll paths\n";
    for(auto u : path) {
        for(auto v : u)
            cout<<v<<" ";
        cout<<"\n";
    }
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
    cout<<"\nGraph\n";
    for (int i = 0; i < g.size(); ++i)
    {
        cout << i << " : ";
        for (auto v : g[i])
            cout << v.second << ", "<<v.first<<"; ";
        cout << "\n";
    }
}