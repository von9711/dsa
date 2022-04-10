#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <stack>
using namespace std;
using namespace std::chrono;

enum Color
{
    WHITE,
    GREY,
    BLACK
};
typedef list<int> li;
typedef pair<int, int> pr;

list<pr> dfs(vector<li> &g);
void dfsVisit(vector<li> &g, vector<pr> &time, vector<bool> &visited,
                vector<int> &parent, list<pr> &bridge, int &clk, int u);
void printBridge(list<pr> &bridge);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e, n;
    cout << "Enter no. of vertices: ";
    cin >> n;
    vector<li> g(n);
    cout << "Enter no. of edges: ";
    cin >> e;
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < e; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        //g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    list<pr> bridge = dfs(g);
    printBridge(bridge);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

list<pr> dfs(vector<li> &g)
{
    vector<pr> time(g.size(), make_pair(0, INT32_MAX));
    vector<bool> visited(g.size(), false);
    vector<int> parent(g.size(), -1);
    list<pr> bridge;
    int clk = 0;
    for (int i = 0; i < g.size(); ++i)
    {
        if (visited[i] == false)
            dfsVisit(g, time, visited, parent, bridge, clk, i);
    }
    return bridge;
}

void dfsVisit(vector<li> &g, vector<pr> &time, vector<bool> &visited,
                vector<int> &parent, list<pr> &bridge, int &clk, int u)
{

    time[u].first = time[u].second = ++clk;
    visited[u] = true;
    int child = 0;
    for (auto v : g[u])
    {
        if (visited[v] == false)
        {
            ++child;
            parent[v] = u;
            dfsVisit(g, time, visited, parent, bridge, clk, v);
            time[u].second = min(time[u].second, time[v].second);

            if (time[u].first < time[v].second)
                bridge.push_front(make_pair(u, v));
        }

        else if (parent[u] != v)
            time[u].second = min(time[u].second, time[v].first);
    }
}

void printBridge(list<pr> &bridge)
{
    cout << "\nBridges: ";
    for (pr edge : bridge)
        cout << edge.first << " - " << edge.second << ", ";
    cout << "\n";
}