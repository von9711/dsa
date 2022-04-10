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

vector<int> dfs(vector<li> &g);
void dfsVisit(vector<li> &g, vector<Color> &color, vector<int> &parent, int s, int &backEdge, list<int> &topSort);
void dfsTraversal(vector<li> &g, int s);
void printParent(vector<int> &parent);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, w,e;
    vector<li> g(9);
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
    cout<<"Enter no. of edges: ";
    cin>>e;
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < e; ++i)
    {
        cin >> u >> v;
        g[u].push_back(v);
        //g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    vector<int> parent = dfs(g);
    //dfsTraversal(g, 0);
    printParent(parent);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<int> dfs(vector<li> &g)   {
    vector<int> parent(g.size(), -1);
    vector<Color> color(g.size(), WHITE);
    int component = 0,backEdge = 0;
    list<int> topSort;
    for(int i = 0; i < g.size(); ++i) {
        if(color[i] == WHITE) {
            dfsVisit(g,color,parent,i,backEdge,topSort);
            ++component;
        }
    }
    if(backEdge)
        cout<<"Graph has cycle\n";
    for(auto itr : topSort)
        cout<<itr<<" -> ";
    cout<<"\nComponent: "<<component<<"\n";
    return parent;
}

void dfsVisit(vector<li> &g, vector<Color> &color, vector<int> &parent, int s,int &backEdge,list<int> &topSort) {
    color[s] = GREY;
    for(auto itr = g[s].begin(); itr != g[s].end(); ++itr) {
        if(color[*itr] == WHITE) {
            parent[*itr] = s;
            dfsVisit(g,color,parent,*itr,backEdge,topSort);
        }
        else if(color[*itr] == GREY)
            ++backEdge;
    }
    topSort.push_front(s);
    color[s] = BLACK;
}

void dfsTraversal(vector<li> &g,int s) {
    vector<bool> visited(g.size(),false);
    stack<int> stk;
    stk.push(s);
    visited[s] = true;
    cout<<"\nTraversal: \n";
    while(!stk.empty()) {
        int u = stk.top();
        stk.pop();
        for(auto itr = g[u].begin(); itr != g[u].end(); ++itr) {
            if(!visited[*itr]) {
                stk.push(*itr);
                visited[*itr] = true;
            }
        }
        cout<<u<<" -> ";
    }
}

void printParent(vector<int> &parent) {
    cout<<"\nvertex : parent\n";
    for(int i = 0; i < parent.size(); ++i)
        cout<<i<<"  :   "<<parent[i]<<"\n";
}
