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
vector<unordered_set<int>> adj;
vector<int> dp;
const int MOD = 1e9+7;
int solve(int z)
{
    int i = __builtin_popcount(z);
    if(i >= n) return 1;
    if(dp[z] != -1) return dp[z];
    int ans = 0;
    for(auto& f : adj[i])
    {
        if(!((1 << f) & z))
        {
            ans = (ans + solve((z | (1 << f)))) % MOD;
        }
    }
    return dp[z] = ans;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    adj.clear();
    adj.resize(n);
    for(int i = 0; i<n ;i++)
    {
        for(int j = 0; j<n; j++)
        {
            int a; cin >> a;
            if(a == 1) adj[i].insert(j);
        }
    }
    dp.clear();
    dp.resize(1 << 23, -1);
    cout << solve(0) << '\n';
    return 0;
}
