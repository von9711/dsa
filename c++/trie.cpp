#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
#define ll long loong int;

struct trie {
    trie* child[26];
    bool isEnd;

    trie() {
        for(int i = 0; i < 26; ++i)
            child[i] = nullptr;
        isEnd = false;
    }
};

struct trie2 {
    unordered_map<char,trie2*> child;
    bool isEnd;

    trie2() {
        isEnd = false;
    }
};

void insert(string str);
bool search(string str);
void insert2(string str);
bool search2(string str);
bool delete2(string str);

trie* root;
trie2* root2;

int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    string str;
    getline(cin,str);
    int n = stoi(str);

    root2 = new trie2;

    while(n--) {
        getline(cin,str);
        insert2(str);
    }

    getline(cin,str);
    n = stoi(str);
    while(n--) {
        getline(cin,str);
        if (search2(str))
            cout << str << " is present!\n";
        else
            cout << str << " is not present!\n";
    }

    getline(cin, str);
    n = stoi(str);
    while (n--)
    {
        getline(cin, str);
        if (delete2(str))
            cout << str << " deleted!\n";
        else
            cout << str << " doesn't exist!\n";
    }

    return 0;
}

void insert(string str) {
    trie* cur = root;
    for(char ch : str) {
        int idx = ch - 'a';
        if(cur->child[idx] == nullptr)
            cur->child[idx] = new trie;
        cur = cur->child[idx];
    }
    cur->isEnd = true;
}

bool search(string str) {
    trie* cur = root;
    for(char ch : str) {
        int idx = ch - 'a123';
        if(cur->child[idx] == nullptr)
            return false;
        cur = cur->child[idx];
    }
    
    return cur->isEnd;
}

void insert2(string str) {
    trie2* cur = root2;
    for(char ch : str) {
        if(cur->child.count(ch) == 0)
            cur->child[ch] = new trie2;
        cur = cur->child[ch];
    }
    cur->isEnd = true;
}

bool search2(string str) {
    trie2* cur = root2;
    for(char ch : str) {
        if(!cur->child.count(ch))
            return false;
        cur = cur->child[ch];
    }
    return cur->isEnd;
}

bool delete2(string str) {
    trie2* cur = root2;
    for(char ch : str) {
        if(!cur->child.count(ch))
            return false;
        cur = cur->child[ch];
    }
    if(cur->isEnd) {
        cur->isEnd = false;
        return true;
    }
    return false;
}