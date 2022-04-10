#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

vector<vector<int>> bottomUpMatrixChainOrder(vector<int> dim);
vector<vector<int>> matrixOrderChain(vector<int> &dim);
int matrixOrderChainLookup(vector<int> &dim, vector<vector<int>> &m, vector<vector<int>> &s, int i, int j); 
void printOptimalOrder(vector<vector<int>> &s, int i, int j);

int main()
{
    ios::sync_with_stdio(false);
    vector<int> dim{30,35,15,5,10,20,25};

    auto start = high_resolution_clock::now();

    vector<vector<int>> s = matrixOrderChain(dim);
    printOptimalOrder(s,1,dim.size()-1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " ms\n";
    return 0;
}

vector<vector<int>> bottomUpMatrixChainOrder(vector<int> dim)   {
    int n = dim.size(),j,q,min;
    vector<vector<int>> m(n, vector<int>(n)), s(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        m[i][i] = 0;
    
    for(int l = 1; l < n - 1; ++l) {
        for(int i = 1; i < n - l; ++i) {
            j = i + l;
            min = INT32_MAX;
            for(int k = i; k < j; ++k) {
                q = m[i][k] + m[k+1][j] + dim[i-1]*dim[k]*dim[j];
                if(q < min) {
                    min = q;
                    s[i][j] = k;
                }
            }
            m[i][j] = min;
        }
    }
    cout<<"\nMin. Cost: "<<m[1][n-1]<<"\n";
    return s;
}

void printOptimalOrder(vector<vector<int>> &s,int i,int j) {
    if(i ==j)
        cout<<"A"<<i;
    else {
        cout<<"(";
        printOptimalOrder(s,i,s[i][j]);
        printOptimalOrder(s,s[i][j] + 1,j);
        cout<<")";
    }
}

vector<vector<int>> matrixOrderChain(vector<int> &dim) {
    int n = dim.size();
    vector<vector<int>> m(n, vector<int>(n)), s(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j)
            m[i][j] = INT32_MAX;
    }
    cout << "\nMin. Cost: " << matrixOrderChainLookup(dim,m,s,1,n-1) << "\n";
    return s;
}

int matrixOrderChainLookup(vector<int> &dim, vector<vector<int>> &m, vector<vector<int>> &s,int i,int j) {
    if(i == j)
        return 0;
    if(m[i][j] < INT32_MAX)
        return m[i][j];
    for(int k = i; k < j; ++k) {
        int q = matrixOrderChainLookup(dim,m,s,i,k) + matrixOrderChainLookup(dim,m,s,k+1,j) + dim[i-1]*dim[k]*dim[j];
        if(q < m[i][j]) {
            m[i][j] = q;
            s[i][j] = k;
        }
    }
    return m[i][j];
}