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
vvc grid;
inline bool check(int i, int j)
{
    return i == 0 || j == 0 || i == n-1 || j == m-1;
}
inline bool valid(int i, int j)
{
    return (i >= 0 && i < n && j >= 0 && j < m);
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    grid.clear();
    grid.resize(n, vc(m));
    vvi dist(n, vi(m, 1e9));
    queue<pair<int, pii>> q;
    pii start;
    for(int i = 0; i<n ; i++)
    {
        for(int j = 0; j<m ; j++)
        {
            cin >> grid[i][j];
            if(grid[i][j] == 'M')
            {
                dist[i][j] = 0;
                q.push({0, {i, j}});
            }
            if(grid[i][j] == 'A')
                start = {i, j};
        }
    }
    while(!q.empty())
    {
        auto p = q.front();
        q.pop();
        int d = p.first;
        if(dist[p.second.first][p.second.second] < d) continue;
        KONECT4
        for(int i = 0; i<4; i++)
        {
            int nx = p.second.first + dx[i];
            int ny = p.second.second + dy[i];
            if(valid(nx, ny) && grid[nx][ny] == '.' && dist[nx][ny] > d+1)
            {
                dist[nx][ny] = d+1;
                q.push({d+1, {nx, ny}});
            }
        }
    }
    q.push({0, start});
    vvi vis(n, vi(m, 0));
    vector<vector<pii>> hash(n, vector<pii>(m, {-1, -1}));
    int ans = 1e9;
    pii end = {-1, -1};
    while(!q.empty())
    {
        auto p = q.front();
        q.pop();
        KONECT4
        if(check(p.second.first, p.second.second))
        {
            if(ans > p.first)
            {
                ans = p.first;
                end = p.second;
            }
        }
        for(int i = 0; i<4; i++)
        {
            int nx = p.second.first + dx[i];
            int ny = p.second.second + dy[i];
            if(valid(nx, ny) && grid[nx][ny] == '.' && dist[nx][ny] > p.first+1 && vis[nx][ny] == 0)
            {
                q.push({p.first+1, {nx, ny}});
                vis[nx][ny] = 1;
                hash[nx][ny] = p.second;
            }
        }
    }

    if(ans < 1e9)
    {
        cout << "YES\n";
        cout << ans << endl;
        vector<pii> v;
        // v.pb(end);
        int i = end.first,  j = end.second;
        while(i >= 0 && j >= 0)
        {
            v.pb({i, j});
            int ii = hash[i][j].first;
            int jj = hash[i][j].second;
            // cout << ii << ' ' << jj << '\n';
            i = ii, j = jj;
        }
        reverse(v.begin(), v.end());
        for(i = 1; i<v.size(); i++)
        {
            pii l = v[i-1];
            if(v[i].first > l.first)
                cout << "D";
            else if(v[i].first < l.first)
                cout << "U";
            else if(v[i].second > l.second)
                cout << "R";
            else
                cout << "L";
        }
        cout << endl;
    }
    else cout << "NO\n";
}