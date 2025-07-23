#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>
#define ull unsigned long long int
#define ll long long int
#define ld long double
#define pb push_back
#define pii pair<int, ll>
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
vvi adj;
vvi adjM;
vi vis;
bool check(int node, int target)
{
    if(node == target)
        return 1;
    for(auto i: adjM[node])
    {
        if(!vis[i])
        {
            vis[i] = 1;
            if(check(i, target))
                return 1;
        }
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    adj.clear(); adj.resize(m, vi(3));
    adjM.clear(); adjM.resize(n+1);
    // reverse bellman ford
    for(int i = 0; i<m ; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        adj[i][0] = u;
        adj[i][1] = v;
        adj[i][2] = w;
        adjM[u].pb(v);
    }
    vector<ll> dist(n+1, -1e18);
    dist[1] = 0;
    for(int i = 1; i<n ; i++)
    {
        for(int j = 0; j<m; j++)
        {
            int u = adj[j][0];
            int v = adj[j][1];
            int w = adj[j][2];
            if(dist[u] > -1e18 && dist[u] + (ll)w > dist[v])
                dist[v] = dist[u] + (ll)w;
        }
    }
    vi f;
    for(int j = 0; j<m; j++)
    {
        int u = adj[j][0];
        int v = adj[j][1];
        int w = adj[j][2];
        if(dist[u] > -1e18 && dist[u] + (ll)w > dist[v])
        {
            dist[v] = dist[u] + (ll)w;
            f.pb(v);
        }
    }
    for(auto i : f) // check for 1 -> i -> n;
    {
        vis.clear(); vis.resize(n+1, 0);
        if(check(1, i))
        {
            vis.clear(); vis.resize(n+1, 0);
            if(check(i, n))
            {
                cout << "-1\n";
                return 0;
            }
        }
    }

    cout << dist[n] << endl;
}