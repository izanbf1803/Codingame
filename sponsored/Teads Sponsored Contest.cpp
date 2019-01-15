#include <bits/stdc++.h>
using namespace std;

int n;
map<int,vector<int>> adj;

int dfs(int u, int parent)
{
    int depth = 1;
    for (int v : adj[u]) {
        if (v != parent) depth = max(depth, dfs(v,u)+1);
    }
    return depth;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = -1;
    for (int i = 0; i < n and root == -1; ++i) {
        if (adj[i].size() == 1) root = i;
    }
    cout << dfs(root,-1)/2 << endl;
}