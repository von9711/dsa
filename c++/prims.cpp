#include <iostream>
#include <vector>
#include <chrono>
#include<list>
#include <unordered_map>
#include<queue>
using namespace std;
using namespace std::chrono;

typedef pair<int,int> pr;
typedef list<pr> li;

vector<pr> mstPrim(vector<li> &g, int r = 0);
void printMst(vector<pr> mst);

int main()
{
    ios::sync_with_stdio(false);
    vector<li> g(9);
    int u,v,w;
    cout<<"\nEnter source, destination & weight\n";
    for(int i = 0; i < 14; ++i) {
        cin>>u>>v>>w;
        g[u].push_back(make_pair(w, v));
        g[v].push_back(make_pair(w, u));
    }

    auto start = high_resolution_clock::now();

    vector<pr> mst = mstPrim(g, 0);
    cout<<"\nmst: \n";
    printMst(mst);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<pr> mstPrim(vector<li> &g, int r)    {
    priority_queue<pr,vector<pr>,greater<pr>> q;
    vector<bool> marked(g.size(),false);    //to mark the visited vertex
    vector<pr> mst(g.size(),make_pair(INT32_MAX,-1)); // store mst and minCost
    int minCost = 0;
    q.push(make_pair(0,r));
    pr p;
    while(!q.empty()) {
        p = q.top();
        q.pop();
        int u = p.second;
        if(marked[u])   // can be removed, you can also
            continue;   // calulate minCost from mst
        minCost += p.first;
        marked[u] = true;
        for(auto itr = g[u].begin(); itr != g[u].end(); ++itr) {
            int w = itr->first, v = itr->second;
            if(!marked[v] && w < mst[v].first) {
                q.push(make_pair(w,v));
                mst[v].first = w;
                mst[v].second = u;
            }
        }
    }
    cout<<"\nMin cost: "<<minCost;
    return mst;
}

void printMst(vector<pr> mst) {
    //int sum = 0;
    for(int i = 1; i < mst.size(); ++i) {
        cout<<mst[i].second<<" -> "<<i<<", ";
        //sum += mst[i].first; //finding minCost from mst
    }
    ///cout<<"\nmin: "<<sum<<"\n";
}