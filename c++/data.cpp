#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
    ofstream outf("string100k.dat",ios::binary);
    for(int i = 0; i < 100000; ++i) {
        char a = rand() % 26 + 97;
        outf.write((char *) &a,sizeof(a));
    }
    outf.close();
    /*ifstream inf("sample.dat",ios::binary);
    int arr[100];
    inf.read((char * ) arr,sizeof(arr));
    for(int i = 0; i < 100; ++i)
        cout<<arr[i]<<" ";*/
    return 0;
}