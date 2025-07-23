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
vvi nums;
const int MOD = 1e9+7;

static bool comp(vi& A, vi& B)
{
    return A[0] + A[1] < B[0] + B[1];
}

ll solve(int i, int s)
{
    if(i >= n || s > 10000) return 0;
    if(dp[i][s] != -1) return dp[i][s];
    if(s <= nums[i][1])
        dp[i][s] = nums[i][2] + solve(i+1, s+nums[i][0]);
    return dp[i][s] = max(dp[i][s], solve(i+1, s));
}
int main()
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    nums.clear(); dp.clear();
    nums.resize(n, vi(3)); dp.resize(n, vi(10003, -1));
    for(auto& i : nums)
    {
        cin >> i[0] >> i[1] >> i[2];
    }
    sort(nums.begin(), nums.end(), comp);
    cout << solve(0, 0) << '\n';
}