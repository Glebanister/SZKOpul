#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>

using namespace std;

const long long INF = 1e9 + 1;

struct Segment {
    int l, r;
    int ind;
};

struct Rect {
    Segment l, r, u, d;
    int x1, y1, x2, y2;
    int ind;
};

unordered_map<int, vector<Segment>> horu, hord, verr, verl;
vector<pair<int, int>> by_x;
vector<pair<int, int>> by_y;

bool cmp_seg(Segment a, Segment b) {
    if (a.l == b.l) {
        return a.r < b.r;
    }
    return a.l < b.l;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

bool cmp_in(Segment a, int b) {
    return (a.l <= b && b <= a.r);
}

vector<vector<int>> g;
vector<Rect> mem;
vector<bool> used;
vector<int> dist;
vector<pair<int, int>> pmem;
int n;

int get_ind_rect(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (cmp_in(mem[i].d, x) && cmp_in(mem[i].l, y)) {
            return mem[i].ind;
        }
    }
    return -1;
}

bool in(int x, int y, int r) {
    if (cmp_in(mem[r].d, x) && cmp_in(mem[r].l, y)) {
        return 1;
    }
    return 0;
}

bool tag(int i) {
    auto it1d = upper_bound(by_x.begin(), by_x.end(), pair<int, int>{mem[i].x1, -INF});
    auto it2d = upper_bound(by_x.begin(), by_x.end(), pair<int, int>{mem[i].x2, -INF});
    auto it1l = upper_bound(by_y.begin(), by_y.end(), pair<int, int>{mem[i].y1, -INF});
    auto it2l = upper_bound(by_y.begin(), by_y.end(), pair<int, int>{mem[i].y2, -INF});
    if (it2d - it1d > it2l - it1l) {
        for (auto it = it1l; it < it2l; it++) {
            if (in(it->first, it->second, i)) {
                return 1;
            }
        }
    } else {
        for (auto it = it1d; it < it2d; it++) {
            if (in(it->first, it->second, i)) {
                return 1;
            }
        }
    }
    return 0;
}
 

void dfs(int u, int t, int d = 0) {
    used[u] = 1;
    dist[u] = d;
    if (u == t) {
        return;
    }
    for (int v : g[u]) {
        if (!used[v] && !tag(v)) {
            dfs(v, t, d + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int w, h, m;
    cin >> w >> h >> n >> m;
    used.resize(n);
    dist.resize(n);
    g.resize(n);
    int xs, ys;
    cin >> xs >> ys;
    int xf, yf;
    cin >> xf >> yf;
    vector<int> allx;
    vector<int> ally;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Segment l, r, u, d;
        l = r = {y1, y2, i};
        u = d = {x1, x2, i};
        verr[x1].push_back(l);
        verl[x2].push_back(r);
        horu[y1].push_back(d);
        hord[y2].push_back(u);
        Rect cur;
        cur.ind = i;
        cur.l = l; cur.r = r; cur.u = u; cur.d = d;
        cur.x1 = x1; cur.x2 = x2; cur.y1 = y1; cur.y2 = y2;
        mem.push_back(cur);
        allx.push_back(x1);
        allx.push_back(x2);
        ally.push_back(y1);
        ally.push_back(y2);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        pmem.push_back({x, y});
        by_x.push_back({x, i});
        by_y.push_back({y, i});
    }
    for (int i : allx) {
        sort(verr[i].begin(), verr[i].end(), cmp_seg);
        sort(verl[i].begin(), verl[i].end(), cmp_seg);
    }
    for (int i : ally) {
        sort(horu[i].begin(), horu[i].end(), cmp_seg);
        sort(hord[i].begin(), hord[i].end(), cmp_seg);
    }
    sort(by_x.begin(), by_x.end());
    sort(by_y.begin(), by_y.end(), cmp);
    for (int i = 0; i < n; i++) {
        Rect cur = mem[i];
        auto itd1 = lower_bound(hord[cur.y1].begin(), hord[cur.y1].end(), cur.d.l, cmp_in);
        auto itd2 = lower_bound(hord[cur.y1].begin(), hord[cur.y1].end(), cur.d.r, cmp_in);
        for (auto it = itd1; it <= itd2; it++) {
            g[cur.ind].push_back(it->ind);
            g[it->ind].push_back(cur.ind);
        }
        cerr << '1';
        auto itu1 = lower_bound(horu[cur.y2].begin(), horu[cur.y2].end(), cur.u.l, cmp_in);
        auto itu2 = lower_bound(horu[cur.y2].begin(), horu[cur.y2].end(), cur.u.r, cmp_in);
        for (auto it = itu1; it <= itu2; it++) {
            g[cur.ind].push_back(it->ind);
            g[it->ind].push_back(cur.ind);
        }
        cerr << '2';
        auto itr1 = lower_bound(verr[cur.x2].begin(), verr[cur.x2].end(), cur.r.l, cmp_in);
        auto itr2 = lower_bound(verr[cur.x2].begin(), verr[cur.x2].end(), cur.r.r, cmp_in);
        for (auto it = itr1; it <= itr2; it++) {
            g[cur.ind].push_back(it->ind);
            g[it->ind].push_back(cur.ind);
        }
        cerr << '3';
        auto itl1 = lower_bound(verl[cur.x1].begin(), verl[cur.x1].end(), cur.l.l, cmp_in);
        auto itl2 = lower_bound(verl[cur.x1].begin(), verl[cur.x1].end(), cur.l.r, cmp_in);
        for (auto it = itl1; it <= itl2; it++) {
            g[cur.ind].push_back(it->ind);
            g[it->ind].push_back(cur.ind);
        }
    }
    int start = get_ind_rect(xs, ys);
    int finish = get_ind_rect(xf, yf);
    dfs(start, finish);
    cout << dist[finish] << endl;

    return 0;
}
