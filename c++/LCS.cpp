#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

vector<vector<char>> LCS(string &s1, string &s2);
vector<vector<int>> LCSLength(string &s1, string &s2); 
void printLCS(vector<vector<char>> &b, string &s, int i, int j);
void printOneLCS(vector<vector<int>> &b, string s, int i, int j);

    int main()
{
    ios::sync_with_stdio(false);
    string s1 = "hbcfgmnapq";
    string s2 = "cbhgrsfnmq";

    auto start = high_resolution_clock::now();

    //vector<vector<char>> b = LCS(s1,s2);
    vector<vector<int>> s = LCSLength(s1, s2);
    //printLCS(s,s1,s.size()-1,s[0].size()-1);
    printOneLCS(s, s1, s.size() - 1, s[0].size() - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " ms\n";
    return 0;
}

vector<vector<char>> LCS(string &s1, string &s2) {
    s1  = '0' + s1;
    s2 = '0' + s2;
    int row = s1.length(), col = s2.length();
    vector<vector<int>> c(row, vector<int>(col));
    vector<vector<char>> b(row, vector<char>(col));
    for(int i = 0; i < row; ++i)
        c[i][0] = 0;
    for(int i = 0; i < col; ++i)
        c[0][i] = 0;
    
    for(int i = 1; i < row; ++i) {
        for(int j = 1; j < col; ++j) {
            if(s1[i] == s2[j]) {
                b[i][j] = 'q';
                c[i][j] = 1 + c[i-1][j-1];
            }
            else if(c[i-1][j] >= c[i][j-1]) {
                b[i][j] = 'w';
                c[i][j] = c[i-1][j];
            }
            else {
                b[i][j] = ' ';
                c[i][j] = c[i][j-1];
            }
        }
    }
    cout<<"\nLength of LCS: "<<c[row-1][col-1]<<"\n";
    return b;
}

vector<vector<int>> LCSLength(string &s1, string &s2)   {
    s1 = '0' + s1;
    s2 = '0' + s2;
    int row = s1.length(), col = s2.length();
    vector<vector<int>> c(row, vector<int>(col));
    for (int i = 0; i < row; ++i)
        c[i][0] = 0;
    for (int i = 0; i < col; ++i)
        c[0][i] = 0;

    for (int i = 1; i < row; ++i)
    {
        for (int j = 1; j < col; ++j)
        {
            if (s1[i] == s2[j])
                c[i][j] = 1 + c[i - 1][j - 1];
            else
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
        }
    }
    cout << "\nLength of LCS: " << c[row - 1][col - 1] << "\n";
    return c;
}

void printLCS(vector<vector<char>> &b,string &s,int i,int j) {
    if(i == 0 || j == 0)
        return;
    if(b[i][j] == 'q') {
        printLCS(b,s,i-1,j-1);
        cout<<s[i]<<" ";
    }
    else if(b[i][j] == 'w')
        printLCS(b,s,i-1,j);
    else
        printLCS(b,s,i,j-1);
}

void printOneLCS(vector<vector<int>> &b,string s,int i,int j)   {
    if(i == 0 || j == 0)
        return;
    if(b[i][j] != b[i-1][j] && b[i][j] != b[i][j-1]) {
        printOneLCS(b,s,i-1,j-1);
        cout<<s[i]<<" ";
    }
    else if(b[i][j] == b[i-1][j])
        printOneLCS(b,s,i-1,j);
    else
        printOneLCS(b,s,i,j-1);
}
