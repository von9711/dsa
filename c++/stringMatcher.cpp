//String matching
#include <iostream>
#include <string>
#include <chrono>
#include<cmath>
#include<fstream>
#include<vector>
using namespace std;
using namespace std::chrono;

void naiveStringMatcher(string t,string p);
void knuthMorrisPratt(string t, string p);
vector<int> computePrefix(string p);
void rabinKarp(string t, string p, int d, int q);
void zAlgo(string t,string p);

int main()
{
    string filename, text, pattern;

    /*cout<<"Enter file name: ";
    getline(cin,filename);
    ifstream inf(filename,ios::binary);
    getline(inf,text);
    inf.close();
    cout<<"\nEnter pattern: ";
    getline(cin, pattern);*/

    freopen("input", "r", stdin);
    getline(cin,text);
    getline(cin,pattern);

    freopen("output.txt","w",stdout);

    auto start = high_resolution_clock::now();

    naiveStringMatcher(text, pattern);
    //rabinKarp(text, pattern, 10, INT32_MAX);
    //knuthMorrisPratt(text, pattern);
    //zAlgo(text, pattern);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nExecution time: " << duration.count() << " us\n";

    return 0;
}

void naiveStringMatcher(string t, string p) {
    int n = t.length();
    int m = p.length();
    cout<<"\nshift: ";
    for(int s = 0; s < n - m + 1; ++s) {
        if(p == t.substr(s,m))
            cout<<s<<" "; 
    }
}

void rabinKarp(string t, string p,int d,int q) {
    int m = p.length();
    int n = t.length();
    int h = int(pow(d,m-1)) % q;
    int pnum = 0, tnum = 0;
    for(int i = 0; i < m; ++i) {
        pnum = (p[i] + pnum * 10) % q;
        tnum = (t[i] + tnum * 10) % q;
    }
    cout<<"\nshift: ";
    for(int s = 0; s < n - m + 1; ++s) {
        if(pnum == tnum) {
            if(p == t.substr(s,m))
                cout<<s<<" ";
        }
        tnum = (10 * (tnum - t[s]*h) + t[s+m]) % q;
    }
}

void knuthMorrisPratt(string t,string p) {
    int n = t.length();
    int m = p.length();
    vector<int> lps = computePrefix(p);
    int k = -1;
    cout<<"\nShift: ";
    for(int i = 0; i < n; ++i) {
        while(k > -1 && t[i] != p[k+1])
            k = lps[k];
        if(p[k+1] == t[i])
            ++k;
        if(k == m-1) {
            cout<<i - m +1<<" ";
            k = lps[k];
        }
    }
}

vector<int> computePrefix(string p) {
    int k = -1, len = p.length();
    vector<int> lps(len);
    lps[0] = k;
    for(int i = 1; i < len; ++i) {
        while(k > -1 && p[i] != p[k+1])
            k = lps[k];
        if(p[i] == p[k+1])
            ++k;
        lps[i] = k;
    }
    return lps;
}

void zAlgo(string t,string p) {
    string total = p + "$" + t;
    int n = total.length();
    int l = 0, r = 0;
    vector<int> zValues(n);
    for(int i = 1; i < n; ++i) {
        if(i > r) {
            l = r = i;
            while(r < n and total[r] == total[r-l])
                ++r;
            zValues[i] = r - l;
            --r;
        }
        else {
            int idx = i - l;
            if(i + zValues[idx] <= r)
                zValues[i] = zValues[idx];
            else {
                l = i;
                while(r < n and total[r] == total[r-l])
                    ++r;
                zValues[i] = r - l;
                --r;
            }
        }
    }
    int m = p.length();
    cout<<"shift: ";
    for(int i = 1; i < n; ++i) {
        if(zValues[i] == m)
            cout<<i - m - 1<<" "; 
    }
}