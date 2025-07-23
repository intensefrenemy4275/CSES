#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

int n, m;
vvi adj, adjR;
vi vis, king, k;
vector<ll> sk;
stack<int> st;

void dfs(int node) {
    vis[node] = 1;
    for(auto i : adj[node]) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    st.push(node);
}

void dfs2(int node, int val) {
    king[node] = val;
    vis[node] = 1;
    for(auto i: adjR[node]) {
        if(!vis[i]) {
            dfs2(i, val);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    adj.assign(n+1, {});
    adjR.assign(n+1, {});
    vector<pair<int,int>> edges;
    k.assign(n+1, 0);
    for(int i = 1; i <= n; i++)
        cin >> k[i];
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjR[v].push_back(u);
        edges.push_back({u, v});
    }
    vis.assign(n+1, 0);
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    vis.assign(n+1, 0);
    king.assign(n+1, 0);
    int cnt = 0;
    while(!st.empty()) {
        int i = st.top(); st.pop();
        if(!vis[i]) {
            ++cnt;
            dfs2(i, cnt);
        }
    }
    // Aggregate points for each SCC
    sk.assign(cnt+1, 0);
    for(int i = 1; i <= n; i++) {
        sk[king[i]] += k[i];
    }
    // Build compressed graph (SCC DAG)
    vvi dag(cnt+1);
    vi indeg(cnt+1, 0);
    set<pair<int,int>> scc_edges; // Avoid duplicate edges
    for(auto &e : edges) {
        int u = king[e.first], v = king[e.second];
        if(u != v && scc_edges.insert({u,v}).second) {
            dag[u].push_back(v);
            indeg[v]++;
        }
    }
    // DP on DAG (Kahn's algorithm)
    queue<int> q;
    vector<ll> ma(cnt+1, 0);
    for(int i = 1; i <= cnt; i++) {
        ma[i] = sk[i];
        if(indeg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int f = q.front(); q.pop();
        for(auto i : dag[f]) {
            if(ma[i] < ma[f] + sk[i]) ma[i] = ma[f] + sk[i];
            indeg[i]--;
            if(indeg[i] == 0)
                q.push(i);
        }
    }
    ll ans = 0;
    for(int i = 1; i <= cnt; i++)
        ans = max(ma[i], ans);
    cout << ans << endl;
}
