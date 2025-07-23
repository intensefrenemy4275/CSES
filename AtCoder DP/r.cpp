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
ll n, K;
const int MOD = 1e9+7;
vvi mul(vvi& A, vvi& B)
{
    vvi x(n, vi(n));
    for(int k = 0; k<n; k++)
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                x[i][j] = ((ll)x[i][j] + (ll)A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }
    return x;
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> K;
    vvi A(n, vi(n));
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n ; j++)
        {
            cin >> A[i][j];
        }
    }

    vvi result(n, vi(n, 0));
    for(int i = 0; i<n ; i++)
        result[i][i] = 1;
    while(K)
    {
        if(K%2 == 1)
            result = mul(result, A);
        A = mul(A, A);
        K /= 2;       
    }
    ll ans = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n ; j++)
        {
            // cout << result[i][j] << '\n';
            ans = (ans + result[i][j]) % MOD;
        }
    }
    
    cout << ans << '\n';
}