#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
 
using namespace std;

const int k = 777;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> upd(k + 1);
    vector<int> ans(n);
    for (int i = 0; i < m; i++) {
        int a, l, d;
        cin >> a >> l >> d;
        a--;
        int le = a;
        int ri = a + (l - 1) * d;
        if (d > k) {
            for (int j = le; j <= ri; j += d) {
                ans[j]++;
            }
        } else {
            upd[d].push_back({le, 0});
            upd[d].push_back({ri + 1, 1});
        }
    }
    for (int i = 1; i <= k; i++) {
        sort(upd[i].begin(), upd[i].end());
        /*
        cout << i << " : ";
        for (auto x : upd[i]) cout << '{' << x.first << ", " << x.second << '}' << ' ';
        cout << endl;
        */
        int last = 0;
        int j = 0;
        vector<int> d(n);
        for (; j < n; j++) {
            for (; last < (int)upd[i].size() && upd[i][last].first == j; last++) {
                if (upd[i][last].second == 0) {
                    d[j % i]++;
                } else {
                    d[(j - 1) % i]--;
                }
            }
            ans[j] += d[j % i];
        }
        /*
        for (int i : ans) cout << i << ' ';
        cout << endl;
        */
    }
    for (int i : ans) cout << i << ' ';
    cout << endl;


    return 0;
}
