#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> next_node(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> next_node[i];
    }

    vector<int> comp_root(n+1, -1);
    vector<int> depth(n+1, 0);
    vector<int> cycle_index(n+1, -1);
    vector<int> cycle_length(n+1, 0);
    vector<int> color(n+1, 0);
    vector<int> in_path(n+1, -1);

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            vector<int> path;
            int cur = i;
            while (color[cur] == 0) {
                color[cur] = 1;
                in_path[cur] = path.size();
                path.push_back(cur);
                cur = next_node[cur];
            }

            if (in_path[cur] != -1) {
                int pos = in_path[cur];
                int rep = path[pos];
                int L = path.size() - pos;
                cycle_length[rep] = L;

                for (int j = pos; j < path.size(); j++) {
                    comp_root[path[j]] = rep;
                    depth[path[j]] = 0;
                    cycle_index[path[j]] = j - pos;
                }
                for (int j = 0; j < pos; j++) {
                    comp_root[path[j]] = rep;
                    depth[path[j]] = pos - j;
                }
            } else {
                for (int j = path.size()-1; j >= 0; j--) {
                    int nxt = next_node[path[j]];
                    depth[path[j]] = depth[nxt] + 1;
                    comp_root[path[j]] = comp_root[nxt];
                }
            }

            for (int node : path) {
                color[node] = 2;
                in_path[node] = -1;
            }
        }
    }

    vector<vector<int>> up(n+1, vector<int>(LOG));
    for (int i = 1; i <= n; i++) {
        up[i][0] = next_node[i];
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }

    auto jump = [&](int u, int k) {
        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
            }
        }
        return u;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;
        if (comp_root[a] != comp_root[b]) {
            cout << "-1\n";
        } else {
            if (depth[b] > 0) {
                if (depth[a] < depth[b]) {
                    cout << "-1\n";
                } else {
                    int k = depth[a] - depth[b];
                    int candidate = jump(a, k);
                    if (candidate == b) {
                        cout << k << '\n';
                    } else {
                        cout << "-1\n";
                    }
                }
            } else {
                int k1 = depth[a];
                int r = jump(a, k1);
                int rep = comp_root[a];
                int L = cycle_length[rep];
                int idx_r = cycle_index[r];
                int idx_b = cycle_index[b];
                int k2 = (idx_b - idx_r) % L;
                if (k2 < 0) k2 += L;
                cout << k1 + k2 << '\n';
            }
        }
    }
}
