#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

void build(vector<int>& seg, int node, int l, int r);
int getSum(vector<int>& seg, int node, int sl, int sr, int l, int r);
void update(vector<int>& seg, int node, int sl,int sr, int pos, int diff);
vector<int> arr;

int main() {
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    string inp;
    getline(cin,inp);
    istringstream str(inp);
    int num;
    while(str>>num)
        arr.push_back(num);

    int n = arr.size();
    vector<int> seg(2*n - 1);
    build(seg,0,0,n-1);
    for(int i : seg)
        cout<<i<<" ";
    cout<<"\nsum 1-5: "<<getSum(seg,0,0,n-1,1,5);
    int diff = 14 - arr[3];
    arr[3] += diff;
    cout<<"\nupdate pos-3 to 14";
    update(seg,0,0,5,3,diff);
    cout << "\nsum 1-5: " << getSum(seg, 0, 0, n - 1, 1, 5);
    return 0;
}

void build(vector<int>& seg, int node, int l, int r) {
    if(l == r)
        seg[node] = arr[l];
    else {
        int mid = (l + r) / 2;
        build(seg,2*node+1,l,mid);
        build(seg,2*node+2,mid+1,r);
        seg[node] = seg[2*node+1] + seg[2*node+2];
    }
}

int getSum(vector<int>& seg, int node, int sl, int sr, int l, int r) {
    if(l <= sl and r >= sr)
        return seg[node];
    if(l > sr or r < sl)
        return 0;
    int mid = (sl+sr) / 2;
    return getSum(seg,2*node+1,sl,mid,l,r) + getSum(seg, 2*node+2,mid+1,sr,l,r);  
}

void update(vector<int> &seg, int node, int sl, int sr, int pos, int diff) {
    if(sl > pos or sr < pos)
        return;
    seg[node] += diff;
    if(sl != sr) {
        int mid = (sl+sr) / 2;
        update(seg,2*node+1,sl,mid,pos,diff);
        update(seg,2*node+2,mid+1,sr,pos,diff);
    }
}