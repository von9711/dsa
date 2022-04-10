#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

int coinChange(vector<int> &coins, int total);

    int main()
{
    ios::sync_with_stdio(false);
    vector<int> coins{2,5,3,6};
    int total = 10;
    auto start = high_resolution_clock::now();

    cout<<"Num of ways: "<<coinChange(coins,total);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

int coinChange(vector<int> &coins,int total) {
    vector<int> num_of_ways(total+1,0);
    num_of_ways[0] = 1;
    for(int i = 0; i < coins.size(); ++i) {
        for(int j = coins[i]; j <= total; ++j)
            num_of_ways[j] += num_of_ways[j - coins[i]];
    }
    return num_of_ways[total];
}