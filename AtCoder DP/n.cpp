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
#define vi vector<ll>
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
vvi dp;
vi pref, A;
ll solve(int i, int j)
{
    if(i >= j) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    ll s = pref[j] - pref[i] + A[i];
    // cout << s << ' ';
    ll ans = s + solve(i,i) + solve(i+1,j);
    for(int k = i+1; k<j; k++)
    {
        ans = min(ans, s + solve(i,k) + solve(k+1,j));
    }
    return dp[i][j] = ans;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    dp.clear();
    dp.resize(n, vi(n, -1));
    pref.clear(); pref.resize(n); A.clear(); A.resize(n);
    for(auto& i : A)
        cin >> i;
    pref[0] = A[0];
    for(int i = 1; i<n ; i++)
        pref[i] = pref[i-1] + A[i];
    cout << solve(0, n-1) << '\n';
}