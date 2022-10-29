#include<iostream>
#include<math.h>
#include<string.h>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono; 

int noOfBalancedBst(int height)
{
    int mod = (int)(pow(10, 9) + 7);
    if(height <= 1)
        return 1;
    int x = noOfBalancedBst(height - 1);
    int y = noOfBalancedBst(height - 2);

    int a = (int)(((long long)(x)*x) % mod);
    int b = (int)((2*(long long)(x)*y) % mod);
    return (int)(((long long)(a)+b) % mod);
}

int mNoOfBalancedBst(int height, vector<int> &ans)
{
    int mod = (int)(pow(10, 9) + 7);
    if(height <= 1)
    {
        return 1;
    }
    if(ans[height] != -1)
        return ans[height];
    int x = mNoOfBalancedBst(height - 1, ans);
    int y = mNoOfBalancedBst(height - 2, ans);
    int a = (int)(((long long)(x)*x) % mod);
    int b = (int)((2*(long long)(x)*y) % mod);
    ans[height] = (int)(((long long)(a)+b) % mod);
    return ans[height];
}

int main()
{
    int height;
    cout<<"Enter height of BST:";
    cin>>height;
    vector<int> ans(height + 1, -1);
    auto start = high_resolution_clock::now();
    mNoOfBalancedBst(height, ans);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start); 
    cout<<ans[height]<<endl;
    cout << "Time taken by function: "
         << duration.count() << " nanoseconds" << endl;
    start = high_resolution_clock::now();
    cout<<noOfBalancedBst(height)<<endl;
    stop = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration1.count() << " microseconds" << endl;
}