#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;
using namespace std::chrono;

string lps(string &text);
string manacher(string &text);

int main()
{
    string filename, text;

    /*cout << "Enter file name: ";
    getline(cin, filename);
    ifstream inf(filename, ios::binary);
    getline(inf, text);
    inf.close();*/

    freopen("input.txt", "r", stdin);
    getline(cin,text);

    //freopen("output.txt", "w", stdout);

    auto start = high_resolution_clock::now();

    string palindrome = manacher(text);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout<<"Longest palidrome substring: "<<palindrome;
    cout<<"\nLength: "<<palindrome.length();

    cout << "\nExecution time: " << duration.count() << " us\n";

    return 0;
}

//using dynamic programming O(n^2)
string lps(string &text) {
    int n = text.length();
    vector<vector<bool>> table(n,vector<bool>(n));
    int pLength = 0;
    string palindrome;

    for(int i = 0; i < n; ++i)
        table[i][i] = true;

    pLength = 1;

    for(int i = 0; i < n; ++i) {
        if(text[i] == text[i+1]) {
            table[i][i+1] = true;
            if(text.substr(i,2).length() > pLength) {
                pLength = 2;
                palindrome = text.substr(i,2);
            }
        }
        else
            table[i][i+1] = false;
    }

    for(int k = 2; k < n; ++k) {
        for(int  i = 0; i < n; ++i) {
            int j = i + k;
            if(text[i] == text[j] and table[i+1][j-1]) {
                if(text.substr(i,k+1).length() > pLength) {
                    palindrome = text.substr(i,k+1);
                    pLength = palindrome.length();
                }
                table[i][j] = true;
            }
            else
                table[i][j] = false;
        }
    }
    return palindrome;
}

//insertig '#' between characters 
string preProcess(string &text) {
    string str = "#";
    for(int i = 0; i < text.length(); ++i)
        str = str + text[i] + "#";
    return str;
}

//O(n)
string manacher(string &text) {
    string str = preProcess(text);
    int n = str.length();
    int c = 0, r = 0;
    int p[n];
    for (int i = 0; i < n; ++i)
    {
        int mirror = 2*c - i;
        if(i < r)
            p[i] = min(p[mirror],r-i);
        else
            p[i] = 0;
        
        int k = 1 + p[i];
        while(i+k < n and i-k >= 0 and str[i+k] == str[i-k]) {
            ++p[i];
            ++k;
        }
        if (i + p[i] > r)
        {
            c = i;
            r = i + p[i];
        }
    }
    int pos = 0, len = 0;
    for(int i = 0; i < n; ++i) {
        if(p[i] > len) {
            pos = i;
            len = p[i];
        }
    }
    pos = (pos - len + 1) / 2;
    return text.substr(pos,len); 
}