#include <iostream>
#include <chrono>
#include <list>
#include <unordered_map>
#include<limits>
using namespace std;
using namespace std::chrono;

enum Color
{
    WHITE,
    GREY,
    BLACK
};
typedef list<string> li;
typedef pair<int, int> pr;

li dfs(unordered_map<string, li> &g);
void dfsVisit(unordered_map<string, li> &g, unordered_map<string, Color> &color, string s, li &topSor);
void printOrder(li &order);
void printGraph(unordered_map<string, li> &g);

int main()
{
    ios::sync_with_stdio(false);
    int n = 9, e = 9;
    string u,v;
    unordered_map<string,li> g;
    cout << "Enter no. of vertices: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"\nEnter Vertices: \n";
    for(int i = 0; i < n; ++i) {
        getline(cin,u);
        g[u];
    }
    cout << "\nEnter no. of edges: ";
    cin >> e;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter source & destination\n";
    for (int i = 0; i < e; ++i)
    {
        getline(cin, u);
        getline(cin, v);
        g[u].push_back(v);
        //g[v].push_back(u);
    }

    auto start = high_resolution_clock::now();

    li order = dfs(g);
    printGraph(g);
    printOrder(order);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

li dfs(unordered_map<string, li> &g)
{
    unordered_map<string,Color> color;
    for(auto str : g)
        color[str.first] = WHITE;
    li topSort;
    for (auto str : g)
    {
        if (color[str.first] == WHITE)
            dfsVisit(g, color, str.first, topSort);
    }
    return topSort;
}

void dfsVisit(unordered_map<string, li> &g, unordered_map<string, Color> &color, string s, li &topSort)
{
    color[s] = GREY;
    for (auto itr = g[s].begin(); itr != g[s].end(); ++itr)
    {
        if (color[*itr] == WHITE)
            dfsVisit(g, color, *itr, topSort);
    }
    topSort.push_front(s);
    color[s] = BLACK;
}



void printOrder(li &order)
{
    cout << "\nOrder: \n";
    for (auto str : order)
        cout <<str<<" -> ";
}

void printGraph(unordered_map<string, li> &g) {
    cout<<"\nGraph: \n";
    for(auto str : g) {
        cout << str.first;
        for(auto vertex : str.second)
            cout << " -> " << vertex;
        cout<<"\n";
    }
}
