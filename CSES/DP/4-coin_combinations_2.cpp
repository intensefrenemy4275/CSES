#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto& ci : c) cin >> ci;
    vector<int> dp(x+1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int sum = c[i]; sum <= x; ++sum) {
            dp[sum] = (dp[sum] + dp[sum - c[i]]) % MOD;
        }
    }
    cout << dp[x] << '\n';
}
