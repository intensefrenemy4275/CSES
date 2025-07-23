#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>
#define ull unsigned long long int
#define ll long long int
#define ld long double
#define pb push_back
#define pii pair<int,long long>
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

class SegmentTree
{
    public:
    vector<ll> seg;
    SegmentTree(int n)
    {
        seg.clear();
        seg.resize(4*n, 0);
    }
    void update(int idx, int l, int r, int i, ll val)
    {
        if(l == r)
        {
            seg[idx] = max(val, seg[idx]);
            return;
        }
        int mid = (l+r) / 2;
        if(i <= mid)
            update(2*idx+1, l, mid, i, val);
        else
            update(2*idx+2, mid+1, r, i, val);

        seg[idx] = max(seg[2*idx+1], seg[2*idx+2]);
    }
    ll query(int idx, int l, int r, int low, int high)
    {
        if(r < low || l > high)
            return -1;
        if(l >= low && r <= high)
            return seg[idx];
        int mid = (l+r)/2;
        ll left = query(2*idx+1, l, mid, low, high);
        ll right = query(2*idx+2, mid+1, r, low, high);
        return max(left, right);
    }
};
int n, m;
vvi masks(1 << 11);
vvi dp(1003, vi(1<<10, -1));
void gen_mask(int s, int curr, int i, int next)
{
    if(i == n)
    {
        masks[s].pb(next);
        return;
    }
    if(curr & (1 << i))
        gen_mask(s, curr, i+1, next);
    else
    {
        gen_mask(s, curr | (1 << i), i+1, next | (1 << i));
        if(i + 1 < n && !(curr & (1 << (i+1))))
            gen_mask(s, ((curr | (1 << i)) | (1 << (i+1))), i+2, next);
    }
}
int solve(int col, int mask)
{
    if(col == m)
        return mask == 0 ? 1 : 0;
    if(dp[col][mask] != -1) return dp[col][mask];
    int curr = 0;
    for(auto f : masks[mask])
    {
        curr = (curr + solve(col+1, f)) % MOD;
    }
    return dp[col][mask] = curr;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int mask = 0; mask < (1 << n); mask++)
    {
        gen_mask(mask, mask, 0, 0);
    }
    cout << solve(0, 0) << endl;
}