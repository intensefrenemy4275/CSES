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
int n, m;
vvi adj; vvi adjR;
vi vis;
stack<int> st;
vi king;
unordered_map<int, int> mp;
void dfs(int node)
{
    // cout << "dfs : " << node << endl;
    for(auto i : adj[node])
    {
        if(!vis[i])
        {
            vis[i] = 1;
            dfs(i);
        }
    }
    st.push(node);
}
void dfs2(int node, int val)
{
    // cout << "dfs2 : " << node << endl;
    king[node] = val;
    for(auto i: adjR[node])
    {
        if(!vis[i])
        {
            vis[i] = 1;
            dfs2(i, val);
        }
    }
}
int main()
{
    // 2-SAT problem (SCC + Topo Sort)
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    adj.resize(2*m+2);
    adjR.resize(2*m+2); int cnt = 1;
    mp.clear();
    for(int i = -m; i<=m; i++)
    {
        if(i != 0)
            mp[i] = cnt++;
    }
    while(n--)
    {
        char a; cin >> a;
        int b; cin >> b;
        if(a == '-') b = -b;
        char c; cin >> c;
        int d; cin >> d;
        if(c == '-') d = -d;
        // cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
        adj[mp[-b]].pb(mp[d]);
        adj[mp[-d]].pb(mp[b]);
        adjR[mp[b]].pb(mp[-d]);
        adjR[mp[d]].pb(mp[-b]);
    }
    vis.clear(); vis.resize(2*m+2, 0);
    for(int i = 1; i<=2*m; i++)
    {
        if(!vis[i])
        {
            vis[i] = 1;
            dfs(i);
        }
    }
    vis.clear(); vis.resize(2*m+2, 0);
    king.clear(); king.resize(2*m+2, 0);
    int cnnt = 1;
    while(!st.empty())
    {
        int i = st.top();
        if(!vis[i])
        {
            vis[i] = 1;
            dfs2(i, cnnt);
            cnnt++;
        }
        st.pop();
    }
    // for(auto i : mp)
    //     cout << i.first << ' ' << i.second << endl;
    
    for(int i = 1; i<=m; i++)
    {
        if(king[mp[i]] == king[mp[-i]])
        {
            // cout << i << ' ' << -i << endl;
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for(int i = 1; i<=m; i++)
    {
        if(king[mp[i]] > king[mp[-i]])
            cout << '+' << ' ';
        else
            cout << '-' << ' ';
    }
    cout << endl;
}