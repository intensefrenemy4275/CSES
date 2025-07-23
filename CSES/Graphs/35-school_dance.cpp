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
class DSU
{
    public:
    vi parent;
    vi size;
    int maxs, tot;
    DSU(int n)
    {
        parent.clear(); parent.resize(n+1, 0);
        size.clear(); size.resize(n+1, 1);
        this->maxs = 1; this->tot = n;
        for(int i = 1; i<=n ; i++)
            parent[i] = i;
    }
    int findUltimateParent(int n)
    {
        if(parent[n] == n)
            return n;
        return parent[n] = findUltimateParent(parent[n]); 
    }
    void unionBySize(int u, int v)
    {
        int upu = findUltimateParent(u);
        int upv = findUltimateParent(v);
        if(upu == upv) return;
        tot--;
        if(size[upu] > size[upv])
        {
            parent[upv] = upu;
            size[upu] += size[upv];
            maxs = max(maxs, size[upu]);
        }
        else
        {
            parent[upu] = upv;
            size[upv] += size[upu];
            maxs = max(maxs, size[upv]);            
        }
    }
};
int n,m,k;
vvi adj, flow, capacity;
vi parent;
int bfs()
{
    fill(parent.begin(), parent.end(), -1);
    parent[0] = -2;
    queue<pii> q;
    q.push({0, 100});
    while(!q.empty())
    {
        auto p = q.front(); q.pop();
        for(auto i : adj[p.first])
        {
            if(parent[i] == -1 && capacity[p.first][i] - flow[p.first][i] > 0)
            {
                parent[i] = p.first;
                q.push({i, min(p.second, capacity[p.first][i] - flow[p.first][i])});
                if(i == n+m+1)
                    return min(p.second, capacity[p.first][i] - flow[p.first][i]);
            }
        }
    }
    return 0;
}
int main()
{
    // Edmonds-Karp 
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    adj.clear(); adj.resize(n+m+2);
    flow.clear(); flow.resize(n+m+2, vi(n+m+2, 0));
    capacity.clear(); capacity.resize(n+m+2, vi(n+m+2, 0));
    parent.clear(); parent.resize(n+m+2, -1);
    while(k--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v+n);
        adj[v+n].pb(u);
        capacity[u][v+n] = 1;
        capacity[v+n][u] = 0;
    }
    for(int i = 1; i<=n ; i++)
    {
        adj[0].pb(i);
        adj[i].pb(0);
        capacity[0][i] = 1;
        capacity[i][0] = 0; 
    }
    for(int i = n+1; i<=n+m; i++)
    {
        adj[i].pb(n+m+1);
        adj[n+m+1].pb(i);
        capacity[i][n+m+1] = 1;
        capacity[n+m+1][i] = 0;
    }
    int maxF = 0;
    int f;
    while(f = bfs())
    {
        maxF += f;
        int curr = n+m+1;
        while(curr != 0)
        {
            flow[parent[curr]][curr] += f;
            flow[curr][parent[curr]] -= f;
            curr = parent[curr];
        }
    }
    cout << maxF << endl;
    for(int i = 1; i<=n ; i++)
    {
        for(int j = n+1; j<=n+m; j++)
        {
            if(flow[i][j] == 1)
                cout << i << ' ' << (j-n) << endl;
        }
    }
}