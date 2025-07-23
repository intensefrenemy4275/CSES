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
const int INV2 = (MOD + 1) / 2;
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

int n;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    vi indeg(n, 0);
    vvi adj(n);
    vi h(n);
    for(auto&i:h)
        cin>>i;
    stack<int> s;
    for(int i = 0; i<n ; i++)
    {
        while(!s.empty() && h[s.top()] <= h[i])
            s.pop();
        if(!s.empty())
        {
            indeg[i]++;
            adj[s.top()].pb(i);
        }
        s.push(i);
    }
    while(!s.empty()) s.pop();
    for(int i = n-1; i>=0 ; i--)
    {
        while(!s.empty() && h[s.top()] <= h[i])
            s.pop();
        if(!s.empty())
        {
            indeg[i]++;
            adj[s.top()].pb(i);
        }
        s.push(i);
    }

    queue<pii> q;
    for(int i = 0; i<n ; i++)
        if(indeg[i] == 0)
            q.push({i, 1});

    int ans = 0;
    while(!q.empty())
    {
        auto p = q.front();
        q.pop();
        int node = p.first;
        int cnt = p.second;
        ans = max(ans, cnt);
        for(auto i : adj[node])
        {
            indeg[i]--;
            if(indeg[i] == 0)
                q.push({i, cnt+1});
        }
    }
    cout << ans << endl;
}