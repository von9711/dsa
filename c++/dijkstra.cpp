//Strongly Conected componenets
#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;
using namespace std::chrono;

typedef pair<int,int> pr;
typedef list<pr> li;
typedef vector<li> graph;

vector<pr> dikstra(graph &g, int s);
void printGraph(graph &g);
void printPath(vector<pr> &path, int u, int v);
void printAllPath(vector<pr> &path);

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
    for (int i = 0; i < e; ++i) {
        cin >> u >> v >> w;
        g[u].push_back(make_pair(w,v));
        //g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    vector<pr> path = dikstra(g,0);
    printAllPath(path);
    cout<<"\nPath from 0 to 2\nMin cost: "<<path[2].first<<"\n";
    printPath(path,0,2);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<pr> dikstra(graph &g, int s) {
    priority_queue<pr,vector<pr>,greater<pr>> q;
    vector<bool> visited(g.size(),false); 
    vector<pr> path(g.size(),make_pair(INT32_MAX,-1));
    q.push(make_pair(0,s));
    path[s].first = 0;
    while(!q.empty()) {
        pr p = q.top();
        q.pop();
        int u = p.second, uvw = path[u].first;
        visited[u] = true;
        for(auto edge : g[u]) {
            int w = edge.first, v = edge.second;
            if(!visited[v] && path[v].first > w + uvw) {
                path[v].first = w + uvw;
                path[v].second = u;
                q.push(edge);
            }
        }
    }
    return path;
}

void printAllPath(vector<pr> &path) {
    cout<<"\nAll paths\n";
    for(int i = 0; i < path.size(); ++i)
        cout << "0 -> " <<i<< " cost: " << path[i].first<< "\n";
}

void printPath(vector<pr> &path, int u, int v) {
    if(u == v) {
        cout<<u;
        return;
    }
    printPath(path,u,path[v].second);
    cout<<" -> "<< v;
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