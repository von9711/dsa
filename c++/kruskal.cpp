#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>
#include <queue>
#include<algorithm>
using namespace std;
using namespace std::chrono;

typedef pair<int, int> pr;
typedef pair<int, pr> edge;
typedef vector<edge> graph;
struct Set {
    int parent;
    int rank;
    Set() {}
    Set(int p,int r) {
        parent = p;
        rank = r;
    }
};
class Forest {
    vector<Set> set;
public:
    Forest(int n) {
        for (int i = 0; i < n; ++i)
            set.push_back(Set(i,0));
    }
    int findSet(int v);
    void unionSet(int u, int v);
};

list<edge> mstKruskal(graph &g);
void printMST(list<edge> &mst);

int main()
{
    ios::sync_with_stdio(false);
    int u, v, e, w;
    graph g;
    cout << "Enter no. of edges: ";
    cin >> e;
    cout << "\nEnter source, destination & weight\n";
    for (int i = 0; i < e; ++i)
    {
        cin >> u >> v >> w;
        g.push_back(make_pair(w, make_pair(u,v)));
    }

    auto start = high_resolution_clock::now();

    list<edge> mst = mstKruskal(g);
    cout << "\nmst: \n";
    printMST(mst);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

list<edge> mstKruskal(graph &g) {
    Forest dSet(g.size());
    list<edge> mst;
    sort(g.begin(),g.end());
    for(auto e : g) {
        if(dSet.findSet(e.second.first) != dSet.findSet(e.second.second)) {
            mst.push_back(e);
            dSet.unionSet(e.second.first, e.second.second);
        }
    }
    return mst;
}

void printMST(list<edge> &mst) {
    long minCost = 0;
    for(auto edge : mst) {
        minCost += edge.first;
        cout<<edge.second.first<<" -> "<<edge.second.second<<", ";
    }
    cout<<"\nMinimum cost: "<<minCost<<"\n";
}

int Forest::findSet(int v) {
    if (set[v].parent != v)
        set[v].parent = findSet(set[v].parent);
    return set[v].parent;
}

void Forest::unionSet(int u, int v) {
    int rootU = findSet(u);
    int rootV = findSet(v);
    if(set[rootU].rank > set[rootV].rank)
        set[rootV].parent = rootU;
    else {
        set[rootU].parent = rootV;
        if (set[rootV].rank == set[rootU].rank)
            ++set[rootV].rank;
    }
}