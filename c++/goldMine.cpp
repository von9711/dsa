#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

int bottomUpGoldMine(vector<vector<int>> &mat);

    int main()
{
    ios::sync_with_stdio(false);
    vector<vector<int>> mat{{1, 3, 1, 5},
                            {2, 2, 4, 1},
                            {5, 0, 2, 3},
                            {0, 6, 1, 2}};

    auto start = high_resolution_clock::now();

    cout<<"Max gold: "<<bottomUpGoldMine(mat);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

int bottomUpGoldMine(vector<vector<int>> &mat) {
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> gold(n+1,vector<int>(m));
    for(int i = 0; i < n; ++i)
        gold[i][0] = mat[i][0];
    for(int i = 0; i < m; ++i)
        gold[n][i] = 0;

    for(int j = 1; j < m; ++j) {
        for(int i  = 0; i < n; ++i) {
            int a = max(gold[i + 1][j - 1], gold[i][j - 1]);
            if (i - 1 >= 0)
                a = max(gold[i-1][j-1],a);
            gold[i][j] = a + mat[i][j]; 
        }
    }

    int max = gold[0][m-1];
    for(int i = 1; i < n; ++i) {
        if(max < gold[i][m-1])
            max = gold[i][m-1];
    }
    return max;
}