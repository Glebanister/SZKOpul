#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <unordered_map>
 
using namespace std;

vector<vector<int>> g;
vector<int> dg;
vector<vector<int>> fr;

const int k = 500;
vector<int> lazy;
int cur = 1;
vector<bool> is;

int rem(int u) {
    is[u] = 0;
    if (dg[u] > k) {
        int plus = g[u].size() - fr[u].size() - lazy[u];
        for (int v : fr[u]) {
            if (is[v]) {
                plus++;
            }
        }
        cur += plus - 1;
    } else {
        int plus = 0;
        for (int v : g[u]) {
            if (is[v]) {
                plus++;
            }
        }
        for (int v : fr[u]) {
            lazy[v]++;
        }
        cur += plus - 1;
    }
    return cur;
}

int rec(int u) {
    is[u] = 1;
    if (dg[u] > k) {
        int plus = g[u].size() - fr[u].size() - lazy[u];
        for (int v : fr[u]) {
            if (is[v]) {
                plus++;
            }
        }
        cur -= plus - 1;
    } else {
        int plus = 0;
        for (int v : g[u]) {
            if (is[v]) {
                plus++;
            }
        }
        for (int v : fr[u]) {
            lazy[v]--;
        }
        cur -= plus - 1;
    }
    return cur;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    g.resize(n);
    dg.resize(n);
    lazy.resize(n);
    is.resize(n, 1);
    fr.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
        dg[a]++;
        dg[b]++;
    }
    for (int i = 0; i < n; i++) {
        for (int v : g[i]) {
            if (dg[v] > k) {
                fr[i].push_back(v);
            }
        }
    }
    int q;
    cin >> q;
    for (int x = 0; x < q; x++) {
        int u;
        cin >> u;
        if (u > 0) {
            u--;
            cout << rem(u) << endl;
        } else {
            u++;
            cout << rec(abs(u)) << endl;
        }
    }

    return 0;
}
