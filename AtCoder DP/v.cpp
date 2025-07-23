#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>
#define ull unsigned long long int
#define ll long long int
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pib pair<int,bool>
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vc vector<char>
#define vvc vector<vector<char>>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define vs vector<string>
#define vvs vector<vector<string>>
#define KONECT4 int dx[] = {1,-1,0,0};\
                int dy[] = {0,0,1,-1};
#define KONECT8 int dx[] = {1,-1,0,0,1,1,-1,-1};\
                int dy[] = {0,0,1,-1,1,-1,-1,1};
using namespace std;

int n;
vvi adj;
vvi dp;
vi ans;
int MOD;
void dfs(int node, int par)
{
    if(adj[node].size() == 1 && adj[node][0] == par)
    {
        dp[node][0] = 0;
        dp[node][1] = 1;
        return;
    }
    dp[node][1] = 1;
    for(int n : adj[node])
    {
        if(n == par) continue;
        dfs(n, node);
        dp[node][0] = (dp[node][0] + dp[n][1] + dp[n][0]) % MOD;
        dp[node][1] = (dp[node][1] * ((1 + dp[n][1])) % MOD) % MOD;
    }
}
void dfs_again(int node, int par, ll use_val)
{
    ans[node] = (dp[node][1] * use_val) % MOD;

    // Precompute prefix and suffix products of (1 + dp[f][1]) for all children
    vector<ll> children;
    for (auto f : adj[node]) {
        if (f != par) children.push_back(f);
    }
    int sz = children.size();
    vector<ll> prefix(sz + 1, 1), suffix(sz + 1, 1);

    // Build prefix products
    for (int i = 0; i < sz; ++i) {
        prefix[i + 1] = (prefix[i] * (1 + dp[children[i]][1]) % MOD);
    }
    // Build suffix products
    for (int i = sz - 1; i >= 0; --i) {
        suffix[i] = (suffix[i + 1] * (1 + dp[children[i]][1]) % MOD);
    }

    for (int i = 0; i < sz; ++i)
    {
        int f = children[i];
        ll sibling_prod = (prefix[i] * suffix[i + 1]) % MOD;
        ll new_use_val = (use_val * sibling_prod) % MOD;
        dfs_again(f, node, (new_use_val + 1) % MOD);
    }

}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> MOD;
    adj.clear(); adj.resize(n+1);
    dp.clear(); dp.resize(n+1, vi(2, -1));
    ans.clear(); ans.resize(n+1);
    for(int i = 1; i<n ; i++)
    {
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u); 
    }
    dfs(1, 0);
    ans[1] = dp[1][1];
    dfs_again(1,0,1);
    for(int i = 1; i<=n; i++)
        cout << ans[i] << '\n';
}