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
vi dp;
const int MOD = 1e9+7;
ll solve(int m)
{
    if(__builtin_popcount(m) == 1) return dp[m] = 0;
    if(dp[m] != -1) return dp[m];
    ll curr = 0;
    for(int i = 0; i<16; i++)
    {
        if((1<<i) & m)
        {
            for(int j = i+1; j<16; j++)
            {
                if((1<<j) & m)
                    curr = curr + (ll)adj[i][j];
            }
        }
    }
    int s = (m-1) & m;
    while(s)
    {
        curr = max((ll)curr, (ll)solve(s) + solve(m^s));
        s = (s-1) & m;
    }
    return dp[m] = curr;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    adj.clear(); adj.resize(n, vi(n));
    dp.clear(); dp.resize(1<<n, -1); dp[0] = 0;
    for(int i = 0; i<n ;i++)
    {
        for(int j = 0; j<n ; j++)
        {
            cin >> adj[i][j];
        }
    }
    int mask = dp.size() - 1;
    cout << solve(mask) << '\n';
}