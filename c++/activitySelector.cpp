//Greedy activity selector
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include<vector>
using namespace std;
using namespace std::chrono;

vector<int> activitySelector(vector<pair<int,int>> &activity);

int main()
{
    vector<pair<int,int>> activity{{0,0},{1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{8,11},{8,12},{2,14},{12,16}};
    auto start = high_resolution_clock::now();

    vector<int> A = activitySelector(activity);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Size: " << A.size() << "\nActivites: ";
    for(int i : A)
        cout<<i<<", ";

    cout << "\nExecution time: " << duration.count() << " us\n";

    return 0;
}

vector<int> activitySelector(vector<pair<int,int>> &activity) {
    int k = 1;
    vector<int> A{1};
    for(int i = 2; i < activity.size(); ++i) {
        if(activity[i].first >= activity[k].second) {
            A.push_back(i);
            k = i;
        }
    }
    return A;
}
