#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> g, gnc, gr;
vector<int> used;
vector<int> cnt;
vector<int> t;

void dfs(int u) {
    used[u] = 1;
    for (int v : gnc[u]) {
        if (!used[v]) {
            dfs(v);
        }
    }
    t.push_back(u);
}

vector<int> sz;

int dfs_line(int u) {
    if (cnt[u] != -1) {
        return cnt[u] + sz[u];
    }
    int cur = 0;
    if ((int)g[u].size() == 0) {
        cnt[u] = 0;
        return sz[u];
    }
    for (int v : g[u]) {
        cur += dfs_line(v);
    }
    cnt[u] = cur;
    return cur + sz[u];
}

vector<int> c;

void dfs_paint(int u, int cl) {
    c[u] = cl;
    for (int v : gr[u]) {
        if (c[v] == -1) {
            c[v] = cl;
            dfs_paint(v, cl);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    gnc.resize(n);
    gr.resize(n);
    bool f = 1;
    vector<pair<int, int>> e;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u > v) {
            f = 0;
        }
        gnc[u].push_back(v);
        gr[v].push_back(u);
        e.push_back({u, v});
    }
    cnt.resize(n, -1);
    used.resize(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(t.begin(), t.end());
    c.resize(n, -1);
    int last = 0;
    sz.resize(n);
    for (int i : t) {
        if (c[i] == -1) {
            dfs_paint(i, last);
            last++;
        }
    }
    for (int i = 0; i < n; i++) {
        sz[c[i]]++;
    }
    for (pair<int, int> p : e) {
        if (c[p.first] != c[p.second]) {
            g[c[p.first]].push_back(c[p.second]);
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < last; i++) {
        ans[i] = dfs_line(i) - 1;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[c[i]] << endl;
    }
    return 0;
}
