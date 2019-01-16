#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
#include <deque>

using namespace std;

struct CoolSet {
    deque<pair<int, int>> q;
    void insert(int x, int i) {
        for (; !q.empty() && q.back().first > x; q.pop_back()) {};
        q.push_back({x, i});
    }
    void update(int ind) {
        if (q.empty()) return;
        while (!q.empty() && q.front().second <= ind) {
            q.pop_front();
        }
    }
    int top() {
        return q.front().first;
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    int q;
    cin >> q;
    for (int x = 0; x < q; x++) {
        int k;
        cin >> k;
        CoolSet last_k;
        vector<CoolSet> val(n);
        val[0].insert(-a[0], 0);
        last_k.insert(0, 0);
        int ans = 0;
        vector<int> dp(n);
        for (int i = 1; i < n; i++) {
            auto cur = last_k.top();
            if (-val[cur].top() > a[i]) {
                ans = cur;
            } else {
                ans = cur + 1;
            }
            val[ans].insert(-a[i], i);
            last_k.insert(ans, i);
            dp[i] = ans;
            last_k.update(i - k);
            val[ans].update(i - k);
        }
        cout << ans << endl;
    }


    return 0;
}
