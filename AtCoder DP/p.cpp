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
const ll MOD = 1e9+7;
vvi adj, dp;
ll dfs(int node, int s, int par)
{
    if(adj[node].size() == 1 && adj[node][0] == par)
    {
        if(s == 0) return 2;
        return 1;
    }
    if(dp[node][s] != -1) return dp[node][s];
    ll ans = 1;
    for(auto i : adj[node])
    {
        if(i == par) continue;
        ll temp = dfs(i, 0, node) % MOD;
        ans = ((ll)ans * (ll)temp) % MOD;
    }
    ll as = 0;
    if(s == 0)
    {
        as = 1;
        for(auto i : adj[node])
        {
            if(i == par) continue;
            ll temp = (dfs(i, 1, node)) % MOD;
            as = ((ll)as * (ll)temp) % MOD;
        }
    }

    return dp[node][s] = ans + as;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    adj.clear(); adj.resize(n+1);
    dp.clear(); dp.resize(n+1, vi(2, -1));
    for(int i = 1; i<n ; i++)
    {
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if(n != 1)
        cout << (dfs(1, 0, -1) % MOD)<< '\n';
    else
        cout << 2 << '\n';
}
