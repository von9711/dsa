//karatsuba algorithm

#include<iostream>
#include<string>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;

long long multiply(long num1,long num2);
int getLength(long num);

int main()
{
    auto start = high_resolution_clock::now();

    cout << "Result: " << multiply(567896326, 345624567);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\nExecution time: "<<duration.count()<<" us\n";
    
    return 0;
}

long long multiply(long num1,long num2) {
    int n = max(getLength(num1),getLength(num2));
    if (n < 4)
        return num1*num2;
    
    long long multiplier = pow(10,n/2 + n%2);
    long long hi1 = num1 / multiplier;
    long long hi2 = num2 / multiplier;
    long long lo1 = num1 % multiplier;
    long long lo2 = num2 % multiplier;

    long long z0 = multiply(lo1,lo2);
    long long z2 = multiply(hi1,hi2);
    long long z1 = multiply((hi1 + lo1), (hi2 + lo2)) - z2 - z0;

    return z2*pow(10,n) + z1 * multiplier + z0;
}

int getLength(long num) {
    int count = 0;
    while(num > 0) {
        ++count;
        num /= 10;
    }
    return count;
}