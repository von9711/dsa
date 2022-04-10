//Strongly Conected componenets
#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <stack>
using namespace std;
using namespace std::chrono;

typedef list<int> li;
typedef vector<li> graph;

stack<int> dfs(graph &g);
void dfsVisit(graph &g, vector<bool> &visited, stack<int> &stk, int u);
void dfsVisit(graph &g, vector<bool> &visited, int u, li &l);
graph transposeGraph(graph &g);
vector<li> SCC(graph &g);
vector<li> findComponent(graph &g, stack<int> &stk);
void printComponent(vector<li> &component);
void printGraph(graph &g);

int main()
{
    ios::sync_with_stdio(false);
    freopen("output","w",stdout);
    int u, v, e, n;
    cout << "Enter no. of vertices: ";
    cin >> n;
    graph g(n);
    cout << "Enter no. of edges: ";
    cin >> e;
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < e; ++i)
    {
        cin >> u >> v;
        g[u].push_back(v);
        //g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    vector<li> component = SCC(g);
    printComponent(component);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<li> SCC(graph &g)
{
    vector<li> component;
    stack<int> stk = dfs(g);
    graph g1 = transposeGraph(g);
    return findComponent(g1, stk);
}

stack<int> dfs(graph &g)
{
    vector<bool> visited(g.size(), false);
    stack<int> stk;
    int clk = 0;
    for (int i = 0; i < g.size(); ++i)
    {
        if (visited[i] == false)
            dfsVisit(g, visited, stk, i);
    }
    return stk;
}

void dfsVisit(graph &g, vector<bool> &visited, stack<int> &stk, int u)
{
    visited[u] = true;
    for (auto v : g[u])
    {
        if (!visited[v])
            dfsVisit(g, visited, stk, v);
    }
    stk.push(u);
}

graph transposeGraph(graph &g)
{
    graph g1(g.size());
    for (int i = 0; i < g.size(); ++i)
    {
        for (auto v : g[i])
            g1[v].push_back(i);
    }
    return g1;
}

vector<li> findComponent(graph &g, stack<int> &stk)
{
    vector<li> component;
    vector<bool> visited(g.size(), false);
    while (!stk.empty())
    {
        int u = stk.top();
        stk.pop();
        if (!visited[u]) {
            li l;
            dfsVisit(g, visited, u, l);
            component.push_back(l);
        }
    }
    return component;
}

void dfsVisit(graph &g, vector<bool> &visited, int u, li &l)
{
    visited[u] = true;
    l.push_back(u);
    for (auto v : g[u])
    {
        if (!visited[v])
            dfsVisit(g, visited, v, l);
    }
}

void printComponent(vector<li> &component)
{
    for (int i = 0; i < component.size(); ++i)
    {
        cout << "\n"
             << i + 1 << " component: ";
        for (auto v : component[i])
            cout << v << " -> ";
    }
}

void printGraph(graph &g) {
    for(int i = 0; i < g.size(); ++i) {
        cout<<i<<" : ";
        for(auto v : g[i])
            cout<<v<<", ";
        cout<<"\n";
    }
}
