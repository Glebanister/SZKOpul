#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MAX = 15001;

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<vector<int>> a(2, vector<int>(MAX));
    vector<vector<int>> last(2, vector<int>(MAX));
    vector<int> row(MAX);
    vector<int> eql(MAX);
	cin>> n >> m;
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i <= n[j]; i++) {
			cin >> a[j][i];
			last[j][i] = 0;
			for (int k = i - 1; k > 0; k--){
				if (a[j][i] == a[j][k]) {
					last[j][i] = k;
					break;
				}
			}
		}
    }
	
	for (int i = 1; i <= n; i++) {
        if (last[0][i] != 0) {
            for (int j = 1; j <= m; j++) {
                if (row[j - 1] > row[j] || (a[0][i] == a[1][j] && last[1][j] != 0 && row[j] == row[last[1][j] - 1] && eql[last[1][j] - 1] < last[0][i])) {
                    row[j]++;
                    eql[j] = i;
                }
            }
        }
    }
		
	cout << row[m] * 2 << endl;
}
