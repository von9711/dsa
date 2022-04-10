#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Fenwick {
    int* bit;
    int len;
public:
    Fenwick() {}
    Fenwick(vector<int>& arr) {
        len = arr.size() + 1;
        bit = new int[len]();
        for(int i = 1; i < len; i++) {
            int k = i + (i&-i);
            bit[i] += arr[i-1];
            if(k < len)
                bit[k] += bit[i]; 
        }
    }
    void update(int x, int val) {
        while(x < len) {
            bit[x] += val;
            x += x & -x;
        }
    }
    int getSum(int x) {
        int sum = 0;
        while(x > 0) {
            sum += bit[x];
            x -= x & -x;
        }
        return sum;
    }
    int rangeSum(int l, int r) {
        return getSum(r) - getSum(l-1);
    }
    void display() {
        cout<<"\nbit array: \n";
        for(int i = 0; i < len; i++)
            cout<<bit[i]<<" ";
        cout<<"\n";
    }
};

int main() {
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);

    string inp;
    getline(cin, inp);
    istringstream str(inp);
    int num;
    vector<int> arr;
    while (str >> num)
        arr.push_back(num);

    cout<<"\narray: ";
    for(int i : arr)
        cout<<i<<" ";
    Fenwick tree(arr);
    tree.display();
    cout<<"\nsum: "<<tree.getSum(11);
    cout<<"\nsum 5-11: "<<tree.rangeSum(5, 11);
    return 0;
}