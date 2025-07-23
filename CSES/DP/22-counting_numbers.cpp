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
#define vi vector<ull>
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

unsigned long long mod_pow(ull a, ull b, ull mod) {
    ull res = 1;
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
string a, b;
vvvi dp[2];
ull solve(string& s, int t, int i, int d, int v)
{
    if(i == s.length()) return 1;
    int curr = (int)(s[i] - '0');
    ull f = 0;
    if(dp[t][i][d][v] != -1) return dp[t][i][d][v];
    if(v)
    {
        for(int j = 0; j<=9; j++)
        {
            if(j != d)
                f = f + solve(s, t, i+1, j, 1);
        }
    }
    else
    {
        for(int j = curr; j <= 9; j++)
        {
            if(j != d)
                f += solve(s, t, i+1, j, j != curr);
        }
    }
    return dp[t][i][d][v] = f;
}
bool check()
{
    for(int i = 0; i<b.length()-1; i++)
    {
        if(b[i] == b[i+1])
            return 0;
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> a >> b;
    dp[0].clear(); dp[0].resize(a.length(), vvi(10, vi(2, -1)));
    dp[1].clear(); dp[1].resize(b.length(), vvi(10, vi(2, -1)));
    ull q = solve(a, 0, 0, 0, 0);
    ull g = solve(b, 1, 0, 0, 0);
    
    if(a.length() == b.length())
    {
        cout << (q - g + check()) << endl;
        return 0;
    }
    ull ans = q;
    for(int i = a.length()+1; i<b.length(); i++)
        ans = ans + mod_pow(9, i, 1e19);
    ans = ans + mod_pow(9, b.length(), 1e19) - g + check();
    cout << ans << endl;   
}