#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h> 
#define ull unsigned long long int
#define ll long long int
#define ld long double
#define pb push_back
#define pii pair<int, int>
#define pil pair<int, ll>
#define pib pair<int, bool>
#define pli pair<ll, int>
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
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
            seg[idx] = val;
            return;
        }
        int mid = (l+r) / 2;
        if(i <= mid)
            update(2*idx+1, l, mid, i, val);
        else
            update(2*idx+2, mid+1, r, i, val);
        seg[idx] = min(seg[2*idx+1], seg[2*idx+2]);
    }
    ll query(int idx, int l, int r, int low, int high)
    {
        if(l > high || r < low)
            return INT_MAX;
        if(l >= low && r <= high)
            return seg[idx];
        int mid = (l + r)/2;
        int left = query(2*idx+1, l, mid, low, high);
        int right = query(2*idx+2, mid+1, r, low, high);
        return min(left, right);
    }
};
int n, m;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    SegmentTree* sgt1 = new SegmentTree(n);
    SegmentTree* sgt2 = new SegmentTree(n);
    for(int i = 1; i<=n; i++)
    {
        int a; cin >> a;
        sgt1 -> update(0, 0, n-1, i-1, a + i - 1);
        sgt2 -> update(0, 0, n-1, i-1, a - i + 1);
    }
    while(m--)
    {
        int a; cin >> a;
        if(a == 1)
        {
            int x; cin >> x; x--;
            int b; cin >> b;
            sgt1 -> update(0, 0, n-1, x, b + x);
            sgt2 -> update(0, 0, n-1, x, b - x);
        }
        else
        {
            int x; cin >> x; x--;
            cout << min(sgt1 -> query(0, 0, n-1, x, n-1) - x, sgt2 -> query(0, 0, n-1, 0, x-1) + x) << endl;
        }
    }
}