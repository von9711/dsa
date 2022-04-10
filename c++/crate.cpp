#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

vector<vector<int>> bottomUpCrate(vector<vector<int>> &c);
void printCrateDistribuion(vector<vector<int>> &cost,int stage, int crate);

    int main()
{
    ios::sync_with_stdio(false);
    vector<vector<int>> c{ {0,0,0,0,0},
                           {0,4,2,6,2},
                           {0,6,4,8,3},
                           {0,7,6,8,4},
                           {0,7,8,8,4},
                           {0,7,9,8,4},
                           {0,7,10,8,}   };

    auto start = high_resolution_clock::now();

    vector<vector<int>> cost = bottomUpCrate(c);
    cout<<"\nCrate per store: ";
    printCrateDistribuion(cost,cost[0].size() - 1,cost.size()-1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<vector<int>> bottomUpCrate(vector<vector<int>> &c)
{
    int n = c.size(), m = c[0].size();
    vector<vector<int>> cost(n,vector<int>(m,0));
    vector<vector<int>> store(n,vector<int>(m,0));
    for(int i = 1; i < n; ++i) {
        cost[i][1]  =  c[i][1];
        store[i][1] = i;
    }
        
    for(int i = 2; i < m; ++i) {
        for(int j = 1; j < n; ++j) {
            int max = 0;
            for(int k = 0; k <= j; ++k) {
                max = c[k][i] + cost[j - k][i - 1];
                if(max > cost[j][i]) {
                    cost[j][i] = max;
                    store[j][i] = k;
                }
            }
        }
    }
    cout << "max profit: " << cost[n-1][m-1];
    return store;
}

void printCrateDistribuion(vector<vector<int>> &cost,int stage,int crate) {
    if(stage == 0)
        return;
    printCrateDistribuion(cost,stage-1,crate - cost[crate][stage]);
    cout<<stage<<" -> "<<cost[crate][stage]<<", ";
}