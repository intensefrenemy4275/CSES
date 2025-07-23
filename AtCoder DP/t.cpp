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
int n;
vvi dp;
const int MOD = 1e9+7;
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> s;
    dp.clear(); dp.resize(n+1, vi(n+1, 0));
    dp[1][1] = 1;
    for(int i = 2; i<=n ; i++)
    {
        vi pref(n+1);
        pref[1] = dp[i-1][1];
        for(int k = 2; k<=n; k++)
        {
            pref[k] = (pref[k-1] + dp[i-1][k]) % MOD;
        }
        for(int j = 1; j<=i; j++)
        {
            if(s[i-2] == '<' && j != 1)
                dp[i][j] = (pref[j-1]) % MOD;
            else if(s[i-2] == '>' && j != i)
                dp[i][j] = (pref[i] + (MOD - pref[j]) % MOD + dp[i-1][j]) % MOD;
        }
    }
    ll ans = 0;
    for(auto& i : dp[n])
        ans = (ans + i) % MOD;
    cout << ans << '\n';
}