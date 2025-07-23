#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT2D {
    int n;
    vector<vector<ll>> bit;
    BIT2D(int sz) : n(sz), bit(sz+2, vector<ll>(sz+2, 0)) {}

    // Add val to cell (x, y)
    void update(int x, int y, ll val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                bit[i][j] += val;
    }

    // Query sum from (1,1) to (x,y)
    ll query(int x, int y) {
        ll res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res += bit[i][j];
        return res;
    }

    // Query sum in rectangle (x1, y1) to (x2, y2)
    ll query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    BIT2D bit(n);

    // Read grid and initialize BIT
    for (int i = 1; i <= n; ++i) {
        string row;
        cin >> row;
        for (int j = 1; j <= n; ++j) {
            if (row[j-1] == '*') {
                bit.update(i, j, 1);
            }
        }
    }

    // Process queries
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << bit.query(x1, y1, x2, y2) << '\n';
    }

    return 0;
}
