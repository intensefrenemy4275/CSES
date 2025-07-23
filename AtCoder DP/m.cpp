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

int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vi A(n+1, 0);
    for(int i = 1; i<=n ; i++) cin >> A[i];
    vvi dp(n+1, vi(k+1, 0));
    for(int i = 0; i<=n ; i++)
        dp[i][0] = 1;
    const int MOD = 1e9+7;
    for(int i = 1; i<=n; i++)
    {
        vi pref(k+1);
        pref[0] = dp[i-1][0];
        for(int l = 1; l<=k ; l++)
        {
            pref[l] = (pref[l-1] + dp[i-1][l]) % MOD;
        }
        for(int j = 1; j<=k; j++)
        {
            // bool f = (i == 1) && (j == 1);
            int x = max(0, j - A[i]);
            // if(f)
            //     cout << x << ' ' << pref[j] << ' ' << pref[x] << ' ' << dp[i-1][x] << endl;
            dp[i][j] = ((pref[j] +( MOD - pref[x]) % MOD) % MOD + dp[i-1][x]) % MOD;
        }
    }
    
    cout << dp[n][k] << '\n';
}
