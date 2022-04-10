//cutting rod dynamic programming
#include <iostream>
#include <vector>
#include <chrono>
#include<unordered_map>
using namespace std;
using namespace std::chrono;

int cutRodMemo(vector<int> &price,int n);
int cutRodMemoAux(vector<int> &price,int n,unordered_map<int,int> &r);
int cutRodNaive(vector<int> &price,int n);
int bottomUpCutRode(vector<int> &price,int n);
void printCutRod(vector<int> &price,int n);
vector<int> bottomUpCutRodeExtended(vector<int> &price,int n);

int main()
{
  ios::sync_with_stdio(false);
  vector<int> price{0,1,5,8,9,10,17,17,20,24,30,30,32,35,38,41,44,48,51,52,55};
  int n;
  cout<<"\nEnter the length: ";
  cin>>n;
  auto start = high_resolution_clock::now();

  printCutRod(price,n);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\nexecution time: " << duration.count() << " ms\n";
  return 0;
}

int cutRodNaive(vector<int> &price,int n) {
  if(n == 0)
    return 0;
  int q = 0;
  for(int i = 1; i <= n; ++i)
    q = max(q,price[i] + cutRodNaive(price,n-i));
  return q;
}

int cutRodMemo(vector<int> &price,int n) {
  unordered_map<int,int> r;
  return cutRodMemoAux(price,n,r);
}

int cutRodMemoAux(vector<int> &price,int n,unordered_map<int,int> &r) {
  if(n == 0)
    return 0;
  if(r.find(n) != r.end())
    return r[n];
  int q = 0;
  for(int i = 1; i <= n; ++i)
    q = max(q,price[i] + cutRodMemoAux(price,n-i,r));
  r[n] = q;
  return q;
}

int bottomUpCutRode(vector<int> &price,int n) {
  vector<int> r(n+1,0);
  for(int i = 1; i <= n; ++i) {
    int q = 0;
    for(int j = 1; j <= i; ++j)
      q = max(q,price[j] + r[i - j]);
    r[i] = q;
  }
  return r[n];
}

vector<int> bottomUpCutRodeExtended(vector<int> &price,int n) {
  vector<int> s(n+1),r(n+1,0);
  for(int i = 1; i <= n; ++i) {
    int q = 0;
    for(int j = 1; j <= i; ++j) {
      if(q < price[j] + r[i - j]) {
        q = price[j] + r[i-j];
        s[i] = j;
      }
    }
    r[i] = q;
  }
  s[0] = r[n];
  return s;
}

int cutRodMemoAuxExtended(vector<int> &price,int n,vector<int> &r,vector<int> &s) {
  if(n == 0)
    return 0;
  if(r[n])
    return r[n];
  int q = 0;
  for(int i = 1; i <= n; ++i) {
    int a = max(q,price[i] + cutRodMemoAuxExtended(price,n-i,r,s));
      if(q < a) {
        q = a;
        s[n] = i;
      }
    }
    r[n] = q;
    return q;
}

vector<int> cutRodMemoExtended(vector<int> &price,int n) {
  vector<int> s(n+1), r(n+1,0);
  s[0] = cutRodMemoAuxExtended(price,n,r,s);
  return s;
}

void printCutRod(vector<int> &price,int n) {
  //vector<int> s = bottomUpCutRodeExtended(price,n);
  vector<int> s = cutRodMemoExtended(price,n);
  cout<<"Revenue: "<<s[0];
  cout<<"\nPiece size: ";
  while(n > 0) {
    cout<<s[n]<<", ";
    n -= s[n];
  }
}
