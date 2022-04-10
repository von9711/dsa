#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

vector<int> bottomUpMulti(vector<vector<int>> &c);
void printPath(vector<int> &d,int index);

int main()
{
    ios::sync_with_stdio(false);
    vector<vector<int>> c(8,vector<int>(8,0));
    c[1][2] = 7; c[1][3] = 8; c[1][4] = 5;
    c[2][5] = 12;
    c[3][5] = 8; c[3][6] = 9;
    c[4][5] = 7; c[4][6] = 13;
    c[5][7] = 9; c[6][7] = 6;

    auto start = high_resolution_clock::now();

    vector<int> d = bottomUpMulti(c);
    cout<<"Path: ";
    printPath(d,d.size()-1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

vector<int> bottomUpMulti(vector<vector<int>> &c) {
    int n = c.size();
    vector<int> cost(n,INT32_MAX),d(n,0);
    cost[0] = cost[1] = 0;
    for(int i = 1; i < n - 1; ++i) {
        for(int j = i+1; j < n; ++j) {
            int min = c[i][j] + cost[i];
            if(c[i][j] && min < cost[j]) {
                cost[j] = min;
                d[j] = i;
            }
        }
    }
    for(int i : d)
        cout<<i<<" ";
    cout<<"\nmax profit: "<<cost[n-1]<<"\n";
    return d;
}

void printPath(vector<int> &d,int index) {
    if(!index)
        return;
    printPath(d,d[index]);
    cout<<index<<" -> ";
}