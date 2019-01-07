#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <stack>
#include <iomanip>

using namespace std;

void update(int& cc, int& bc, int& sc, char l) {
    if (l == 'C') {
        cc++;
    } else if (l == 'B') {
        bc++;
    } else {
        sc++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cc = 0;
        int bc = 0;
        int sc = 0;
        for (int j = i; j < n; j++) {
            update(cc, bc, sc, s[j]);
            if ((cc != sc && cc != bc && sc != bc) || (cc == 0 && sc == 0) || (bc == 0 && sc == 0) || (cc == 0 && bc == 0)) {
                ans = max(ans, j - i + 1);
            }
        }
    }
    cout << ans << endl;



    return 0;
}
