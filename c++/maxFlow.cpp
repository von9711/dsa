//max flow edmond's karp
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
typedef vector<vector<pr>> graph;

int maxFlowKarp(graph &g,int s,int t);
int maxFlowDinic(graph &g, int s, int t);
bool bfsDinic(vector<vector<int>> &g, vector<int> &lvl, int s, int t);
int dfsDinic(vector<vector<int>> &rg,vector<int> &lvl, int s,int t, int flow);
bool bfsKarp(vector<vector<int>> &g, vector<int> &prnt, int s, int t);
void printGraph(graph &g);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e, n, w;
    cout << "Enter no. of vertices: ";
    cin >> n;
    graph g(n, vector<pr>(n));
    cout << "Enter capacity in adjacency matrix\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j) {
            int c;
            cin >> c;
            g[i][j].first = 0;
            g[i][j].second = c;
        }
    }

    auto start = high_resolution_clock::now();

    cout<<"\nMax Flow: "<<maxFlowDinic(g,0,g.size()-1)<<"\n";
    //printGraph(g);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

int maxFlowDinic(graph &g, int s, int t) {
    vector<vector<int>> rg(g.size(), vector<int>(g.size()));
    vector<int> lvl(g.size());
    int maxFlow = 0;

    for (int u = 0; u < g.size(); ++u)
    {
        for (int v = 0; v < g.size(); ++v)
            rg[u][v] = g[u][v].second;
    }

    while(bfsDinic(rg,lvl,s,t)) {
        while(int flow = dfsDinic(rg,lvl,s,t,INT32_MAX))
            maxFlow += flow;
    }
    return maxFlow;
}

int dfsDinic(vector<vector<int>> &rg,vector<int> &lvl, int s,int t, int flow) {
    if(s == t)
        return flow;
    for(int i = 0; i < rg.size(); ++i) {
        if(lvl[i] == lvl[s] + 1 && rg[s][i] > 0) {
            int cflow = min(flow,rg[s][i]);
            int tflow = dfsDinic(rg,lvl,i,t,cflow);
            if(tflow > 0) {
                rg[s][i] -= tflow;
                rg[i][s] += tflow;
                return tflow;
            }
        }
    }
    return 0;
}

bool bfsDinic(vector<vector<int>> &g, vector<int> &lvl, int s, int t)
{
    vector<bool> visited(g.size());
    queue<int> q;
    q.push(s);
    lvl[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for (int v = 0; v < g.size(); ++v)
        {
            if (!visited[v] && g[u][v] > 0)
            {
                q.push(v);
                lvl[v] = lvl[u] + 1;
                if (v == t)
                    return true;
            }
        }
    }
    return visited[t];
}

int maxFlowKarp(graph &g, int s, int t)
{
    vector<vector<int>> rg(g.size(),vector<int>(g.size()));
    vector<int> prnt(g.size());
    int maxFlow = 0;

    for(int u = 0; u < g.size(); ++u) {
        for(int v = 0; v < g.size(); ++v)
            rg[u][v] = g[u][v].second;
    }

    while(bfsKarp(rg,prnt,s,t)) {
        int rc = INT32_MAX;
        for (int v = t; v != s; v = prnt[v]) {
            int u = prnt[v];
            rc = min(rc,rg[u][v]);
        }

        for (int v = t; v != s; v = prnt[v]) {
            int u = prnt[v];
            if(g[u][v].second)
                g[u][v].first += rc;
            else
                g[v][u].first -= rc;
            rg[u][v] -= rc;
            rg[v][u] += rc;
        }
        maxFlow += rc;
    }

    return maxFlow;
}

bool bfsKarp(vector<vector<int>> &g, vector<int> &prnt, int s, int t)
{
    vector<bool> visited(g.size());
    queue<int> q;
    q.push(s);
    prnt[s] = -1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for(int v = 0; v < g.size(); ++v) {
            if(!visited[v] && g[u][v] > 0) {
                q.push(v);
                prnt[v]= u;
                if(v == t)
                    return true;
            }
        }
    }
    return visited[t];
}

void printGraph(graph &g)
{
    cout << "\nGraph\n";
    for (int u = 0; u < g.size(); ++u)
    {
        cout << u << " : ";
        for (auto v : g[u])
            cout << v.first << "|" << v.second << ";  ";
        cout << "\n";
    }
}