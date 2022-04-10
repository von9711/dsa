#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include<queue>
#include<unordered_map>
using namespace std;
using namespace std::chrono;

struct Node
{
    char c;
    int freq;
    Node* left;
    Node* right;
    Node() {
        left = right = nullptr;
    }
    Node(char c,int f) {
        this->c = c;
        freq = f;
        left = right = nullptr;
    }
};
struct Compare {
    bool operator()(Node *x,Node *y) {
        return x->freq > y->freq;
    }
};

Node* huffmanCode(vector<Node*> &C);
void printTree(Node* root, string str);
void storeCodes(Node *root, string str, unordered_map<char, string> &codes);
string decode(Node* root,string &str); 

int main()
{
    vector<Node*> C;
    /*C.push_back(new Node('G', 2));
    C.push_back(new Node('e', 4));
    C.push_back(new Node('k', 2));
    C.push_back(new Node('s', 1));
    C.push_back(new Node('f', 1));
    C.push_back(new Node('o', 1));
    C.push_back(new Node('r', 1));**/
    C.push_back(new Node('a', 1));
    C.push_back(new Node('b', 1));
    C.push_back(new Node('c', 2));
    C.push_back(new Node('d', 3));
    C.push_back(new Node('e', 5));
    C.push_back(new Node('f', 8));
    C.push_back(new Node('g', 13));
    C.push_back(new Node('h', 21));

    auto start = high_resolution_clock::now();

    Node* root = huffmanCode(C);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nExecution time: " << duration.count() << " us\n";

    string str;
    printTree(root, str);
    /*
    string data = "GeeksforGeeks", encodedStr;
    unordered_map<char,string> codes;
    storeCodes(root,str,codes);
    for(char i : data)
        encodedStr += codes[i];
    cout<<"\nEncoded string: "<<encodedStr<<"\n";
    cout<<"\nDecoded string: "<<decode(root,encodedStr)<<"\n";
    */
    return 0;
}

void printQ(priority_queue<Node*, vector<Node*>, Compare> Q) {
    while(!Q.empty()) {
        cout<<Q.top()->c<<" ";
        Q.pop();
    }
    cout<<"\n";
}

Node *huffmanCode(vector<Node *> &C)
{
    int n = C.size();
    priority_queue<Node*,vector<Node*>,Compare> Q(C.begin(),C.end());
    for(int i = 0; i < n-1; ++i) {
        Node* x = Q.top();
        Q.pop();
        Node* y = Q.top();
        Q.pop();
        Node *z = new Node(' ', x->freq + y->freq);
        z->left = x;
        z->right = y;
        Q.push(z);
    }
    return Q.top();
}

void printTree(Node* root, string str) {
    if(root->left == nullptr && root->right == nullptr) {
        cout<<root->c<<" : "<<str<<"\n";
        return;
    }
    printTree(root->left,str+'0');
    printTree(root->right,str+'1');
}

void storeCodes(Node *root, string str, unordered_map<char, string> &codes)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        codes[root->c] = str;
        return;
    }
    storeCodes(root->left, str + '0', codes);
    storeCodes(root->right, str + '1', codes);
}

string decode(Node* root, string & str) {
    Node* temp = root;
    string decodeStr = "";
    for(int i = 0; i < str.length(); ++i) {
        if(str[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
        
        if(temp->left == nullptr && temp->right == nullptr) {
            decodeStr += temp->c;
            temp = root;
        }
    }
    return decodeStr;
}