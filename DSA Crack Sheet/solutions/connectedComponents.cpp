#include<bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int> > &edges, bool* visited, int a, int n, vector<int> &v)
{
    visited[a] = true;
    v.push_back(a);
    for(int i = 0; i < edges[a].size(); i++)
    {
        if(visited[edges[a][i]] == false)
        {
            dfs(edges, visited, edges[a][i], n, v);
        }
    }
}

vector<vector<int> > component(vector<vector<int> > &edges, bool* visited, int n)
{
    vector<vector<int> > output;
    for(int i = 0; i < n; i++)
    {
        if(visited[i] == false)
        {
            vector<int> v;
            dfs(edges, visited, i, n, v);
            output.push_back(v);
        }
    }
    return output;
}

int main()
{
    int n = 0, e = 0;
    cin>>n>>e;
    vector<vector<int> > edges(n);
    int a, b;
    for(int i = 0; i < e; i++)
    {
        cin>>a>>b;
        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    vector<vector<int> > output = component(edges, visited, n);
    for (int i = 0; i < output.size(); i++)
    {
        for(int j = 0; j < output[i].size(); j++)
        {
            cout<<output[i][j] + 1<<" ";
        }
        cout<<endl;
    }   
    return 0;
}