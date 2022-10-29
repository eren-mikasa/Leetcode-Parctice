#include<bits/stdc++.h>
using namespace std;

vector<int> grayCode(int A) {
    vector<int> v;
    int a = 0;
    int p = pow(2, A) - 1;
    while(p >= 0)
    {
        v.push_back(p);
        p--;
    }
    return v;
}

int main(int argc, char const *argv[])
{
    vector<int> ans;
    int A = 0;
    cin>>A;
    ans = grayCode(A);
    for(int i = 0; i < ans.size(); i++)
        cout<<ans[i]<<" ";
    cout<<endl<<ans.size();
    return 0;
}
