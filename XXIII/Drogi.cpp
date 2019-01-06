#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> gr;
vector<int> t;

void dfs(int u, vector<bool>& used, vector<vector<int>>& g) {
    used[u] = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs(v, used, g);
        }
    }
}

void dfs_paint(int u, vector<int>& c, int cl, vector<vector<int>>& g) {
    c[u] = cl;
    for (int v : g[u]) {
        if (c[v] == -1) {
            dfs_paint(v, c, cl, g);
        }
    }
}

void dfs_cond(int u, vector<bool>& used, vector<vector<int>>& g) {
    used[u] = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs_cond(v, used, g);
        }
    }
    t.push_back(u);
}

int main() {
    iostream::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    if (n <= 5000 && m <= 5000) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // if (0) {
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            vector<bool> used1(n);
            vector<bool> used2(n);
            dfs(i, used1, g);
            dfs(i, used2, gr);
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (used1[i] || used2[i]) {
                    cnt++;
                }
            }
            if (cnt == n) {
                ans.push_back(i);
            }
        }
        cout << ans.size() << endl;
        for (int i : ans) cout << i + 1 << ' ';
        cout << endl;
    } else {
        vector<bool> used(n);
        vector<int> c(n, -1);
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                dfs_cond(i, used, g);
            }
        }
        reverse(t.begin(), t.end());
        int cur = 0;
        for (int i : t) {
            if (c[i] == -1) {
                dfs_paint(i, c, cur, gr);
                cur++;
            }
        }
        vector<int> din(cur);
        unordered_map<int, unordered_map<int, bool>> ed;
        for (int i = 0; i < n; i++) {
            for (int j : g[i]) {
                if (c[i] != c[j] && ed[c[i]][c[j]] == 0) {
                    din[c[j]]++;
                    ed[c[i]][c[j]] = 1;
                }
            }
        }
        int ist = 0;
        int ist_i = 0;
        for (int i = 0; i < cur; i++) {
            if (din[c[i]] == 0) {
                ist++;
                ist_i = c[i];
            }
        }
        set<int> ans;
        if (ist == 1) {
            for (int i = 0; i < n; i++) {
                if (c[i] == ist_i) {
                    ans.insert(i);
                }
            }
        }
        vector<int> res;
        for (int i : ans) res.push_back(i);
        sort(res.begin(), res.end());
        cout << ans.size() << endl;
        for (int i : res) cout << i + 1 << ' ';
        cout << endl;

    }
    return 0;
}
