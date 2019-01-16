#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <set>
#include <assert.h>

using namespace std;

const int INF = 1e9;

vector<vector<int>> g;
vector<vector<int>> gr;
vector<bool> used;
vector<int> t;

struct CoolSet {
    set<int> val;
    unordered_map<int, int> cnt;
    void insert(int x) {
        cnt[x]++;
        if (cnt[x] == 1) {
            val.insert(x);
        }
    }
    void erase(int x) {
        cnt[x]--;
        if (cnt[x] == 0) {
            val.erase(x);
        }
    }
    set<int>::iterator begin() {
        return val.begin();
    }
    bool empty() {
        return val.empty();
    }
};

void dfs(int u) {
    used[u] = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs(v);
        }
    }
    t.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n); 
    gr.resize(n);
    used.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        gr[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(t.begin(), t.end());
    vector<int> e(n), b(n);
    for (int i = 0; i < n; i++) {
        int v = t[i];
        for (int to : gr[v]) {
            e[v] = max(e[v], e[to] + 1);
        }
    }
    for (int i = n - 1; i > -1; i--) {
        int v = t[i];
        for (int to : g[v]) {
            b[v] = max(b[v], b[to] + 1);
        }
    }
    vector<int> t_ind(n);
    for (int i = 0; i < n; i++ ) {
        t_ind[t[i]] = i;
    }
    vector<vector<int>> close(n);
    vector<vector<int>> open(n);
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) {
            if (abs(t_ind[v] - t_ind[u]) > 1) {
                open[t_ind[u]].push_back(e[u] + b[v]);
                close[t_ind[v]].push_back(e[u] + b[v]);
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        cout << e[i] << ' ' << b[i] << endl;
    }
    */
    vector<int> prefe(n + 1);
    vector<int> suffb(n + 1);
    for (int i = 1; i < n + 1; i++) {
        prefe[i] = max(prefe[i - 1], e[t[i - 1]]);
    }
    for (int i = n - 1; i > -1; i--) {
        suffb[i] = max(suffb[i + 1], b[t[i]]);
    }
    CoolSet maxi;
    int ans = INF;
    int ind = 0;
    for (int i = 0; i < n; i++) {
        int cur = INF;
        int upd = 1;
        if (i > 0) {
            for (int w : open[i - 1]) {
                maxi.insert(-w);
            }
        }
        int st = 0;
        if (maxi.empty()) {
            cur = 0;
        } else {
            cur = -*maxi.begin() + 1;
            st = cur;
        }
        if (prefe[i] > cur) {
            cur = prefe[i];
            upd = 2;
        }
        if (suffb[i + 1] > cur) {
            cur = suffb[i + 1];
            upd = 3;
        }
        cur = max(cur, prefe[i]);
        cur = max(cur, suffb[i + 1]);
        if (ans > cur) {
            ans = cur;
            ind = t[i];
        }
        if (i < n - 1) {
            for (int w : close[i + 1]) {
                maxi.erase(-w);
            }
        }
    }
    cout << ind + 1 << ' ' << ans << endl;

    return 0;
}
