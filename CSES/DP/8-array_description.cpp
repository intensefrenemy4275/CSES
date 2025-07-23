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
#define YES cout << "Yes\n"
#define NO cout << "No\n"
#define endl '\n'
#define KONECT4 int dx[] = {1,-1,0,0};\
                int dy[] = {0,0,1,-1};
#define KONECT8 int dx[] = {1,-1,0,0,1,1,-1,-1};\
                int dy[] = {0,0,1,-1,1,-1,-1,1};
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 2005; 
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

int n, m;
vector<vector<int>> dp(100002, vector<int>(102, -1));
int arr[100002];
int solve(int i, int v)
{
    if(i == n) return 1;
    if(arr[i] != 0 && abs(arr[i] - v) > 1) return 0;
    if(dp[i][v] != -1) return dp[i][v];
    if(arr[i] != 0) return dp[i][v] = solve(i+1, arr[i]) % MOD;
    else
    {
        int curr = solve(i+1, v) % MOD;
        if(v != m)
            curr = (curr + solve(i+1, v+1)) % MOD;
        if(v != 1)
            curr = (curr + solve(i+1, v-1)) % MOD;
        return dp[i][v] = curr;
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i<n ; i++)
        cin >> arr[i];
    if(arr[0] != 0)
        cout << solve(1, arr[0]) << '\n';
    else
    {
        int ans = 0;
        for(int i = 1; i<=m; i++)
        {
            ans = (ans + solve(1, i)) % MOD;
        }
        cout << ans << endl;
    }
}