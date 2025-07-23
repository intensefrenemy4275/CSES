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
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vc vector<char>
#define vvc vector<vector<char>>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define vs vector<string>
#define vvs vector<vector<string>>
#define YES cout << "Yes\n"
#define NO cout << "No\n"
#define endl '\n'
#define KONECT4 int dx[] = {1,-1,0,0};\
                int dy[] = {0,0,1,-1};
#define KONECT8 int dx[] = {1,-1,0,0,1,1,-1,-1};\
                int dy[] = {0,0,1,-1,1,-1,-1,1};
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 200005; 
long long fact[MAXN], inv_fact[MAXN];

long long mod_pow(long long a, long long b, int mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void precompute() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[MAXN-1] = mod_pow(fact[MAXN-1], MOD-2, MOD);
    for (int i = MAXN-2; i >= 1; --i) {
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
}
long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

int n;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    vs grid(n);
    for(auto&i:grid)
        cin >> i;
    vvb vis(n, vb(n, false));
    vis[0][0] = 1;
    vector<pii> p;
    p.pb({0,0});
    string ans = "";
    ans.pb(grid[0][0]);
    while(p.size() > 0)
    {
        vector<pair<int,int>> x;
        char mini = 'Z';
        for(auto& f : p)
        {
            int i = f.first;
            int j = f.second;
            if(i+1<n)
                mini = min(mini, grid[i+1][j]);
            if(j+1<n)
                mini = min(mini, grid[i][j+1]);
        }
        ans.pb(mini);
        for(auto& f : p)
        {
            int i = f.first;
            int j = f.second;
            if(i+1<n && grid[i+1][j] == mini && vis[i+1][j] == 0)
            {
                x.emplace_back(i+1, j);
                vis[i+1][j] = 1;
            }
            if(j+1<n && grid[i][j+1] == mini && vis[i][j+1] == 0)
            {
                x.emplace_back(i, j+1);
                vis[i][j+1] = 1;
            }    
        }
        p = move(x);
    }
    ans.pop_back();
    cout << ans << endl;
}