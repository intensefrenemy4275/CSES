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
string s;
int d;
vvvi dp;
const int MOD = 1e9+7;

int solve(int i, int r, int v)
{
    if(i == s.size() && r == 0) return 1;
    if(i == s.size()) return 0;
    if(dp[i][r][v] != -1) return dp[i][r][v];
    int curr = (int)(s[i] - '0');
    ll ans = 0;
    for(int f = 0; f<=9; f++)
    {
        if(f < curr || v == 1)
            ans = (ans + solve(i+1, (r + f) % d, 1)) % MOD;
        else if(f == curr)
            ans = (ans + solve(i+1, (r + f) % d, 0)) % MOD;
        else
            break;
    }
    return dp[i][r][v] = ans;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> s;
    cin >> d;
    dp.clear(); dp.resize(s.length(), vvi(d, vi(2, -1)));
    cout << (solve(0, 0, 0) - 1 + MOD) % MOD << '\n';
}