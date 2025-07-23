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
            seg[idx] = (seg[idx] + val) % MOD;
            return;
        }
        int mid = (l+r) / 2;
        if(i <= mid)
            update(2*idx+1, l, mid, i, val);
        else
            update(2*idx+2, mid+1, r, i, val);

        seg[idx] = (seg[2*idx+1] + seg[2*idx+2]) % MOD;
    }
    ll query(int idx, int l, int r, int low, int high)
    {
        if(r < low || l > high)
            return 0;
        if(l >= low && r <= high)
            return seg[idx];
        int mid = (l+r)/2;
        ll left = query(2*idx+1, l, mid, low, high);
        ll right = query(2*idx+2, mid+1, r, low, high);
        return (left + right) % MOD;
    }
};
int n, m;
vector<vector<pii>> adj;
vvi edges;
int main()
{
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    edges.clear();
    adj.clear(); adj.resize(n+1);
    for(int i = 0; i<m ; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].pb({v,w});
        edges.pb({u, v, w});
    }
    vector<ll> dist(n+1, 0);
    vi pred(n+1);
    int x = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            int u = edges[j][0], v = edges[j][1], w = edges[j][2];
            if(dist[u] + (ll)w < dist[v]) {
                dist[v] = dist[u] + (ll)w;
                pred[v] = u;
                x = v;
            }
        }
    }
    
    // cout << x << endl;
    if(x < 1)
    {
        cout << "NO\n";
        return 0;
    }
    vi cycle;
    for(int i = 0; i<n; i++) // guaranteed to enter the cycle
        x = pred[x];
    
    if(x < 1)
    {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    int tx = x;
    while(x != tx || cycle.size() == 0)
    {
        cycle.pb(x);
        x = pred[x];
    }
    cycle.pb(x);
    reverse(cycle.begin(), cycle.end());
    for(auto i : cycle)
        cout << i << ' ';
    cout << endl;
}