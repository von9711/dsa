#include<iostream>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono;

int findPeak(vector<int> &arr,int p,int r);

int main() {
    ios::sync_with_stdio(false);
    vector<int> arr{1,2,3,4,5,6,7,8,11,10};
    auto start = high_resolution_clock::now();

    cout << "Peak: " << findPeak(arr, 0, arr.size() - 1) << "\n";
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nexecution time: " << duration.count() << " us\n";
    return 0;
}

/*int findPeak(vector<int> &arr,int p,int r) {
    if (p < r) {
        int mid = (p + r)/2;
        if(arr[mid] < arr[mid+1])
            return findPeak(arr, mid + 1, r);
        else if(mid > p && arr[mid] < arr[mid - 1])
            return findPeak(arr,p,mid-1);
        else
            return arr[mid];
    }
    return arr[p];
}*/

int findPeak(vector<int> &arr, int low, int high)
{
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] < arr[mid + 1])
            low = mid + 1;
        else if (mid > low && arr[mid] < arr[mid - 1])
            high = mid - 1;
        else
            return arr[mid];
    }
    return arr[low];
}