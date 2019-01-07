#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <stack>
#include <iomanip>

using namespace std;

int cnt(string p, string t) {
    string s = p + '#' + t;
    int n = s.size();
    vector<int> z(n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        for (; i + z[i] < n && s[z[i]] == s[i + z[i]]; z[i]++) {};
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    int ans = 0;
    for (int i : z) ans += i == (int)p.size();
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    long long n, a, p, b, m;
    cin >> n >> a >> b >> p >> m;
    string w;
    cin >> w;
    if (n <= 1000000) {
        string s = "";
        for (long long i = 0; i < n; i++) {
            if ((a * i + b) % n >= p) {
                s += '1';
            } else {
                s += '0';
            }
        }
        cout << cnt(w, s) << endl;
        return 0;        
    }
    vector<pair<long long, long long>> s;
    s.push_back({0, n - 1});
    for (long long i = 0; i < (long long)w.size(); i++) {
        vector<pair<long long, long long>> nw;
        if (w[i] == '1') {
            for (pair<long long, long long> cur : s) {
                if (cur.second >= p) {
                    if (cur.first <= p) {
                        cur.first = p;
                    }
                    cur.first = (cur.first + a) % n;
                    cur.second = (cur.second + a) % n;
                    if (cur.second < cur.first) {
                        nw.push_back({cur.first, n - 1});
                        nw.push_back({0, cur.second});
                    } else {
                        nw.push_back(cur);
                    }
                }
            }
        } else {
            for (pair<long long, long long> cur : s) {
                if (cur.first < p) {
                    if (p < cur.second) {
                        cur.second = p - 1;
                    }
                    cur.first = (cur.first + a) % n;
                    cur.second = (cur.second + a) % n;
                    if (cur.second < cur.first) {
                        nw.push_back({0, cur.second});
                        nw.push_back({cur.first, n - 1});
                    } else {
                        nw.push_back(cur);
                    }
                }
            }
        }
        s = nw;
    }
    vector<pair<long long, long long>> nw;
    for (pair<long long, long long> cur : s) {
        cur.first -= w.size() * a;
        cur.first += (w.size() + 1) * n;
        cur.first %= n;
        cur.second -= w.size() * a;
        cur.second += (w.size() + 1) * n;
        cur.second %= n;
        if (cur.second < cur.first) {
            nw.push_back({0, cur.second});
            nw.push_back({cur.first, n - 1});
        } else {
            nw.push_back(cur);
        }
    }
    s = nw;

    vector<long long> prohib;
    for (long long i = n - w.size() + 1; i < n; i++) {
        prohib.push_back((a * i + b) % n);
    }
    sort(prohib.begin(), prohib.end());
    long long ans = 0;
    for (pair<long long, long long> cur : s) {
        ans += cur.second - cur.first + 1;
        auto it1 = lower_bound(prohib.begin(), prohib.end(), cur.first);
        auto it2 = upper_bound(prohib.begin(), prohib.end(), cur.second);
        ans -= it2 - it1;
    }
    cout << ans << endl;

    return 0;
}
