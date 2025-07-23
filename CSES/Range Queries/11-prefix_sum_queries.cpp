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
struct Node {
    long long sum;
    long long prefix;
    Node(long long v = 0) : sum(v), prefix(max(0LL, v)) {}
};

class SegTree {
    public:
    int n;
    vector<Node> tree;

    SegTree(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, arr);
    }

    void build(int idx, int l, int r, const vector<long long>& arr) {
        if (l == r) {
            tree[idx] = Node(arr[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * idx + 1, l, m, arr);
        build(2 * idx + 2, m + 1, r, arr);
        tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    Node combine(const Node& a, const Node& b) {
        Node res;
        res.sum = a.sum + b.sum;
        res.prefix = max(a.prefix, a.sum + b.prefix);
        return res;
    }

    void update(int pos, long long val, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = Node(val);
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            update(pos, val, 2 * idx + 1, l, m);
        else
            update(pos, val, 2 * idx + 2, m + 1, r);
        tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
    }
    // External update API
    void update(int pos, long long val) { update(pos, val, 0, 0, n - 1); }

    Node query(int ql, int qr, int idx, int l, int r) {
        if (qr < l || r < ql) return Node(0); // Neutral element
        if (ql <= l && r <= qr) return tree[idx];
        int m = (l + r) / 2;
        Node left = query(ql, qr, 2 * idx + 1, l, m);
        Node right = query(ql, qr, 2 * idx + 2, m + 1, r);
        return combine(left, right);
    }
    // External query API: returns the max prefix sum in [l, r]
    long long max_prefix(int l, int r) { return query(l, r, 0, 0, n - 1).prefix; }
};
int main()
{
    int n, q; cin >> n >> q;
    vl A;
    for(int i = 0; i<n; i++)
    {
        int a; cin >> a;
        A.pb(a);
    }
    SegTree* sgt = new SegTree(A);
    while(q--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1)
        {
            b--;
            sgt -> update(b, c);
        }
        else
            cout << sgt -> max_prefix(b-1, c-1) << endl;
    }
}