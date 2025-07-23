#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    ordered_multiset ost;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        ost.insert({A[i], i});
    }
    while (m--) {
        char q; int b, c;
        cin >> q >> b >> c;
        if (q == '?') {
            // Find number of employees with salary in [b, c]
            // order_of_key returns number of elements < given key
            int l = ost.order_of_key({b, 0});
            int r = ost.order_of_key({c + 1, 0});
            cout << r - l << '\n';
        } else {
            // Update: change salary of employee b to c
            --b; // 0-based
            ost.erase(ost.find({A[b], b}));
            ost.insert({c, b});
            A[b] = c;
        }
    }
}
