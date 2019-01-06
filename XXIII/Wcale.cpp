#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <stack>
#include <iomanip>
#include <cassert>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    long long ans = 0;
    sort(a.rbegin(), a.rend());
    ans += ((int)log2(a[0]) + 1) * 2 + 1;
    string s = "";
    s += to_string(a[0]);
    s += ',';
    for (int i = 1; i < n; i++) {
        s += to_string(a[i]);
        s += ',';
        if (a[i] == 1) {
            ans += 2;
            // cout << a[i] << ' ' << 2 << endl;
        } else {
            ans += ((int)log2(a[i] - 1) + 1) * 2 + 2;
            // cout << a[i] << ' ' << ((int)log2(a[i] - 1) + 1) * 2 + 2 << endl;
        }
    }
    cout << s << endl;
    cout << ans << endl;

    return 0;
}
