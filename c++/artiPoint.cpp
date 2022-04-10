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

list<int> dfs(vector<li> &g);
void dfsVisit(vector<li> &g, vector<pr> &time, vector<bool> &visited,
                vector<int> &parent, list<int> &artiPoint, int &clk, int u);
void printArtiPoints(list<int> &artiPoint);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e;
    vector<li> g(6);
    cout << "Enter no. of edges: ";
    cin >> e;
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < e; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    list<int> artiPoint = dfs(g);
    printArtiPoints(artiPoint);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

list<int> dfs(vector<li> &g)  {
    vector<pr> time(g.size(), make_pair(0,INT32_MAX));
    vector<bool> visited(g.size(), false);
    vector<int> parent(g.size(),-1);
    list<int> artiPoint;
    int clk = 0;
    for(int i = 0; i < g.size(); ++i) {
        if(visited[i] == false)
            dfsVisit(g, time, visited, parent, artiPoint, clk, i);
    }
    return artiPoint;
}

void dfsVisit(vector<li> &g, vector<pr> &time, vector<bool> &visited,
                vector<int> &parent,list<int> &artiPoint, int &clk, int u)  {
    
   time[u].first = time[u].second = ++clk;
   visited[u] = true;
   int child = 0;
   for (auto v : g[u]) {
       if (visited[v] == false) {
           ++child;
           parent[v] = u;
           dfsVisit(g, time, visited, parent, artiPoint, clk, v);
           time[u].second = min(time[u].second, time[v].second);

            if (parent[u] == -1 && child > 1)
                artiPoint.push_front(u);

            if (parent[u] != -1 && time[u].first <= time[v].second)
                artiPoint.push_front(u);
       }

       else if (parent[u] != v)
            time[u].second = min(time[u].second, time[v].first);
   } 
}

void printArtiPoints(list<int> &artiPoint) {
    cout<<"\nArticulation Points: ";
    for(int vertex : artiPoint)
        cout<<vertex<<", ";
    cout<<"\n";
}