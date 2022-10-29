#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int allPossibleWays(int* arr, int n, int v)
{
    int **dp = new int* [n];
    for (int i = 0; i < n; i++)
    {
        dp[i] = new int [v + 1];
        dp[i][0] = 1;
    }
    for (int i = 1; i <= v; i++)
    {
        if(i % arr[n - 1] == 0)
            dp[n - 1][i] = 1;
        else
            dp[n - 1][i] = 0;
    }
    for (int i = 1; i <= v; i++)
    {
        for (int j = n - 2; j >= 0; j--)
        {
            if(i - arr[j] < 0)
                dp[j][i] = 0;
            else
                dp[j][i] = dp[j + 1][i] + dp[j][i - arr[j]];
        }
    }
    return dp[0][v];
}

int main(int argc, char const *argv[])
{
    int n,v;
    cin>>n;
    int* arr = new int [n];
    for (int i = 0; i < n; i++)
        cin>>arr[i];
    cin>>v;
    cout<<allPossibleWays(arr, n, v)<<endl;
    return 0;
}