#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
using namespace std;
using namespace std::chrono;



int main()
{
    ios::sync_with_stdio(false);
    string s1 = "ABCBDAB", s2 = "BDCABA";

    auto start = high_resolution_clock::now();



    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " ms\n";
    return 0;
}

