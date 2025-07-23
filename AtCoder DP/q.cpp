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
#define KONECT4 int dx[] = {1,-1,0,0};\
                int dy[] = {0,0,1,-1};
#define KONECT8 int dx[] = {1,-1,0,0,1,1,-1,-1};\
                int dy[] = {0,0,1,-1,1,-1,-1,1};
using namespace std;
int n;
class SegmentTree
{
    public:
    vector<ll> seg;
    SegmentTree()
    {
        seg.clear();
        seg.resize(4*n);
    }
    void update(int idx, int low, int high, int i, ll val)
    {
        if(low == high)
        {
            seg[idx] = val;
            return;
        }
        int mid = (low + high)/2;
        if(i <= mid)
            update(2*idx+1, low, mid, i, val);
        else
            update(2*idx+2, mid+1, high, i, val);
        seg[idx] = max(seg[2*idx+1], seg[2*idx+2]);
    }
    ll query(int idx, int low, int high, int l, int r)
    {
        if(high < l || low > r) return -3;
        else if(low >= l && high <= r) return seg[idx];
        else
        {
            int mid = (low + high) / 2;
            ll left = query(2*idx+1, low, mid, l, r);
            ll right = query(2*idx+2, mid+1, high, l, r);
            return max(left, right);
        }
    }
};
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    SegmentTree* sgt = new SegmentTree();
    vi h(n), a(n);
    for(auto& i : h)
        cin >> i;
    for(auto& i : a)
        cin >> i;
    ll ans = 0;
    for(int i = 0; i<n ; i++)
    {
        ll cur = 0;
        if(h[i] > 1)
            cur = sgt -> query(0, 1, n, 1, h[i]-1);
        ans = max(ans, cur + (ll)a[i]);
        sgt -> update(0, 1, n, h[i], (ll)a[i] + cur);
    }
    cout << ans << '\n';
}