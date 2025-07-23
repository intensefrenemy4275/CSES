// #include <iostream>
// #include <vector>
// // #include <chrono> // For time measurement
// using namespace std;
// // using namespace std::chrono;

// #define ull unsigned long long int
// #define ll long long int
// #define ld long double
// #define pb push_back
// #define pii pair<int,int>
// #define pib pair<int,bool>
// #define vi vector<int>
// #define vvi vector<vi>
// #define vvvi vector<vvi>
// #define vc vector<char>
// #define vvc vector<vector<char>>
// #define vb vector<bool>
// #define vvb vector<vector<bool>>
// #define vs vector<string>
// #define vvs vector<vector<string>>
// #define YES cout << "Yes\n"
// #define NO cout << "No\n"
// #define endl '\n'
// #define KONECT4 int dx[] = {1,-1,0,0};\
//                 int dy[] = {0,0,1,-1};
// #define KONECT8 int dx[] = {1,-1,0,0,1,1,-1,-1};\
//                 int dy[] = {0,0,1,-1,1,-1,-1,1};

// const int MOD = 1e9+7;
// const int MAXN = 200005;
// long long fact[MAXN], inv_fact[MAXN];

// long long mod_pow(long long a, long long b, int mod) {
//     long long res = 1;
//     while (b > 0) {
//         if (b & 1) res = res * a % mod;
//         a = a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }
// void precompute() {
//     fact[0] = inv_fact[0] = 1;
//     for (int i = 1; i < MAXN; ++i) {
//         fact[i] = fact[i-1] * i % MOD;
//     }
//     inv_fact[MAXN-1] = mod_pow(fact[MAXN-1], MOD-2, MOD);
//     for (int i = MAXN-2; i >= 1; --i) {
//         inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
//     }
// }
// long long C(int n, int k) {
//     if (k < 0 || k > n) return 0;
//     return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
// }

// vvi dp;
// int solve(int x, int y)
// {
//     if(x == y) return 0;
//     if(x == 1 || y == 1)
//         return max(x,y) - 1;
//     if(dp[x][y] != -1) return dp[x][y];
//     // columns
//     int curr = 1e9;
//     for(int i = 1; i < y; i++)
//     {
//         curr = min(curr, 1 + solve(x,i) + solve(x, y-i));
//     }
//     // rows
//     for(int i = 1; i < x; i++)
//     {
//         curr = min(curr, 1 + solve(i,y) + solve(x-i, y));
//     }
//     return dp[x][y] = curr;
// }

// int main()
// {
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//     int a = 500, b = 499; cin >> a >> b;
//     dp.clear(); dp.resize(a+1, vi(b+1, -1));

//     int result = solve(a, b);
//     cout << result << endl;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

    // Base cases: squares need 0 moves
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
            } else {
                int res = 1e9;

                // Try vertical cuts
                for (int k = 1; k < j; k++) {
                    res = min(res, 1 + dp[i][k] + dp[i][j - k]);
                }

                // Try horizontal cuts
                for (int k = 1; k < i; k++) {
                    res = min(res, 1 + dp[k][j] + dp[i - k][j]);
                }

                dp[i][j] = res;
            }
        }
    }

    cout << dp[a][b] << "\n";

    return 0;
}
