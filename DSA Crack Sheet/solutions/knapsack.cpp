#include <iostream>
#include <vector>

using namespace std;

int knapsack(vector<int> values, vector<int> weights, int element, int weight_rem, vector<int> &result)
{
    int res;
    if(weight_rem <= 0 || element >= values.size())
        return 0;
    if(weights[element] <= weight_rem)
    {
        int x = knapsack(values, weights, element + 1, weight_rem, result);
        int y = values[element] + knapsack(values, weights, element + 1, weight_rem - weights[element], result);
        if(x < y)
            result[element] = 1;
        res = max(x, y);
    }
    else
    {
        res = knapsack(values, weights, element + 1, weight_rem, result);
    }
    return res;
}

int main(int argc, char const *argv[])
{
    vector<int> values = {120, 100, 60}, weights = {30 , 20, 10}, result(values.size(), 0);
    int weight = 50;
    cout<<knapsack(values, weights, 0, weight, result)<<endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout<<result[i]<<" ";
    }
    
    return 0;
}
