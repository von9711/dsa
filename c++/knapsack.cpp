#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <vector>
#include<algorithm>
using namespace std;
using namespace std::chrono;

typedef pair<int,int> item;

vector<int> knapsackDP(vector<item> &items, int w);
float knapsackGP(vector<item> &items, int w);

int main()
{
    vector<item> items{{10,60},{20,100},{30,120}};
    auto start = high_resolution_clock::now();

    vector<int> A = knapsackDP(items,50);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout <<"\nItems: ";
    for(int i = A.size()-1 ; i > 0; i -= items[A[i]-1].first/10)
        cout << A[i] << ", ";

    cout << "\nExecution time: " << duration.count() << " us\n";

    start = high_resolution_clock::now();

    float max = knapsackGP(items, 50);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout<<"\nmax: "<<max;

    cout << "\nExecution time: " << duration.count() << " us\n";

    return 0;
}

//  0|1 knapsack -> dynamic programming
vector<int> knapsackDP(vector<item> &items, int w)  {
    int n = items.size() + 1;
    int m = w/10 + 1;
    vector<int> bag(m, 0);
    vector<vector<int>> cost(n,vector<int>(m, 0));
    for(int i = 1; i < n; ++i) {
        for(int j = 1 ; j < m; ++j) {
            if(items[i-1].first > j*10)
                cost[i][j] = cost[i-1][j];
            else {
                int l = cost[i-1][j-(items[i-1].first)/10] + items[i-1].second;
                if(cost[i-1][j] < l) {
                    bag[j] = i;
                    cost[i][j] = l;
                }
                else
                    cost[i][j] = cost[i-1][j];
            }
        }
    }
    cout<<"max: "<<cost[n-1][m-1];
    return bag;
}

bool compare(item i1, item i2)  {
    return (i1.second / i1.first) > (i2.second / i2.first);
}

// 0|1 knapsack fractional -> greedy programming
float knapsackGP(vector<item> &items, int w) {
    int cost = 0, i = 0;
    sort(items.begin(),items.end(),compare);

    while(w > 0 && i < items.size()) {
        if(w > items[i].first)
            cost += items[i].second;
        else
            cost += (w * items[i].second) / items[i].first;
        w -= items[i].first;
        ++i;
    }
    return cost;
}