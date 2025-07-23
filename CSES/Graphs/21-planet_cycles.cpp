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
int n;
vi adj;
vi head;
vi dp;
unordered_set<int> st;
unordered_map<int, int> mp;
int dfs(int node, int compo)
{
    if(node == compo)
        return 0;
    head[node] = compo;
    return 1 + dfs(adj[node], compo);
}
int solve(int node)
{
    if(dp[node] != -1) return dp[node];
    return dp[node] = 1 + solve(adj[node]);
}
int main()
{
    // Use DP :)
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    vi indeg(n+1, 0);
    adj.clear(); dp.clear(); head.clear(); st.clear(); mp.clear();
    adj.resize(n+1); dp.resize(n+1, -1); head.resize(n+1, -1);
    for(int i = 1; i<=n ;i++){
        cin >> adj[i];
        indeg[adj[i]]++;
    }
    for(int i = 1; i<=n ; i++)
        st.insert(i);
    queue<int> q;
    for(int i = 1; i<=n; i++)
    {
        if(indeg[i] == 0)
            q.push(i);
    }
    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        st.erase(node);
        indeg[adj[node]]--;
        if(indeg[adj[node]] == 0)
            q.push(adj[node]);
    }
    for(auto i : st)
    {
        if(head[i] == -1)
        {
            head[i] = i;
            mp[i] = 1 + dfs(adj[i], i);
        }
        dp[i] = mp[head[i]];
    }
    for(int i = 1; i<=n; i++)
    {
        solve(i);
    }
    for(int i = 1; i<=n ; i++)
        cout << dp[i] << ' ';
    cout << endl;
    
}