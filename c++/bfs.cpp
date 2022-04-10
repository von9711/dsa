#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std;
using namespace std::chrono;

enum Color {WHITE,GREY,BLACK};
typedef list<int> li;
typedef pair<int,int> pr;

vector<pr> bfs(vector<li> &g, int s);
void printLevel(vector<pr> path);
void printPath(vector<pr> path, int s, int v);

int main()
{
    ios::sync_with_stdio(false);
    vector<li> g(8);
    int u, v, w;
    /*g[0].push_back(make_pair(-3,1));
    g[0].push_back(make_pair(4, 2));
    g[1].push_back(make_pair(-3, 0));
    g[1].push_back(make_pair(-5,2));
    g[1].push_back(make_pair(-2, 3));
    g[2].push_back(make_pair(4, 0));
    g[2].push_back(make_pair(-5, 1));
    g[2].push_back(make_pair(6, 3));
    g[3].push_back(make_pair(-2, 1));
    g[3].push_back(make_pair(6, 2));*/
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < 8; ++i)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    vector<pr> path = bfs(g,2);
    printLevel(path);
    cout<<"\nPath from 2 -> 6\n";
    printPath(path,2,6);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<pr> bfs(vector<li> &g, int s)
{
    vector<pr> path(g.size(),make_pair(-1,-1));
    queue<char> q;
    vector<Color> color(g.size(),WHITE);
    q.push(s);
    path[s].first = 0;
    color[s] = GREY;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        color[u] = BLACK;
        for(auto itr = g[u].begin(); itr != g[u].end(); ++itr) {
            if(color[*itr] == WHITE) {
                q.push(*itr);
                color[*itr] = GREY;
                path[*itr].first = path[u].first + 1;
                path[*itr].second = u;
            }
        }
    }
    return path;
}

void printLevel(vector<pr> path)
{
    cout<<"\vvertex : level\n";
    for(int i = 0; i < path.size(); ++i) {
        cout<<i<<"  :   "<<path[i].first<<"\n";
    }
}

void printPath(vector<pr> path,int s,int v) {
    if(v == s)
        cout<<s;
    else if(v == -1)
        cout<<"\nno path exist\n";
    else { 
        printPath(path,s,path[v].second);
        cout<<" -> "<<v;
    }
}