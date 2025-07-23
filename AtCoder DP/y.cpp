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
int h,w,n;
vi dp;
vector<pii> pts;
const int MOD = 1e9+7;
const int MAXN = 200005; // Should be >= H+W

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
static bool comp(pii& A, pii& B)
{
    if(A.first == B.first)
        return A.second < B.second;
    return A.first < B.first;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> h >> w >> n;
    pts.clear(); pts.resize(n+2);
    pts[0] = {1,1};
    for(int i = 1; i<n+1; i++)
        cin >> pts[i].first >> pts[i].second;
    pts[n+1] = {h, w};
    dp.clear();
    dp.resize(n+2);
    dp[0] = 1;
    precompute();
    sort(pts.begin(), pts.end(), comp);
    for(int i = 1; i<n+2; i++)
    {
        ll toRem = 0;
        ll totWays = C(pts[i].first + pts[i].second - 2, pts[i].first - 1);
        for(int j = 1; j<i ; j++)
        {
            ll curr = dp[j] * C(pts[i].first + pts[i].second - pts[j].first - pts[j].second, pts[i].first - pts[j].first) % MOD;
            toRem = (toRem + curr) % MOD;
        }
        dp[i] = (totWays - toRem + MOD) % MOD;
    }
    cout << dp[n+1] << '\n'; 
}