#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

const long long INF = 1e18;
const long long MAXI = 1 << 19; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct Segment {
    long long l, r;
    long long base, d;
    long long sum = 0;
    bool flag = 0;
};

vector<Segment> t(MAXI * 2);

long long ar_sum(long long b, long long d, long long n) {
    return b * n + d * n * (n - 1) / 2;
}

void push(long long v) {
    if (t[v].flag) {
        t[2 * v].d += t[v].d;
        t[2 * v + 1].d += t[v].d;
        t[2 * v].base += t[v].base;
        t[2 * v + 1].base += t[v].base + t[v].d * (t[2 * v].r - t[2 * v].l);
        t[2 * v].sum += ar_sum(t[v].base, t[v].d, t[2 * v].r - t[2 * v].l);
        t[2 * v + 1].sum += ar_sum(t[v].base + t[v].d * (t[2 * v].r - t[2 * v].l), t[v].d, t[2 * v].r - t[2 * v].l);
        t[v].flag = 0;
        t[2 * v].flag = t[2 * v + 1].flag = 1;
        t[v].base = 0;
        t[v].d = 0;
    }
}

void add(long long v, long long l, long long r, long long b, long long d) {
    if (t[v].r <= l || r <= t[v].l) {
        return;
    }
    if (l <= t[v].l && t[v].r <= r) {
        // cout << endl;
        // cout << "old base: " << t[v].base << " old dif: " << t[v].d << endl;
        t[v].base += b + d * (t[v].l - l);
        t[v].d += d;
        t[v].sum += ar_sum(b + d * (t[v].l - l), d, t[v].r - t[v].l);
        t[v].flag = 1;
        // cout << v << ' ' << t[v].base << ' ' << t[v].d << ' ' << "sum: " << t[v].sum << endl;;
        // cout << "base: " << t[v].base << " dif: " << t[v].d << endl;
        return;
    }
    push(v);
    add(v * 2, l, r, b, d);
    add(v * 2 + 1, l, r, b, d);
    t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
}

long long get_sum(long long v, long long l, long long r) {
    if (t[v].r <= l || r <= t[v].l) {
        return 0;
    }
    if (l <= t[v].l && t[v].r <= r) {
        return t[v].sum;
    }
    push(v);
    return get_sum(v * 2, l, r) + get_sum(v * 2 + 1, l, r);
}

void build(long long i, long long s, long long a) {
    long long l = max(0LL, i);
    long long r = min(MAXI, i + s / a + 1);
    add(1, l, r, s, -a);
    l = max(0LL, i - s / a);
    r = i;
    add(1, l, r, s - (r - l) * a, a);
}

long long get_aver(long long l, long long r) {
    return get_sum(1, l, r) / (r - l);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    long long n, m;
    cin >> n >> m;
    for (long long i = MAXI; i < MAXI * 2; i++) {
        t[i].l = i - MAXI;
        t[i].r = i + 1 - MAXI;
    }
    for (long long i = MAXI - 1; i > 0; i--) {
        t[i].l = t[i * 2].l;
        t[i].r = t[i * 2 + 1].r;
    }
    vector<long long> ss(n);
    vector<long long> aa(n);
    for (long long i = 0; i < m; i++) {
        char q;
        cin >> q;
        if (q == 'P') {
            long long i, s, a;
            cin >> i >> s >> a;
            ss[i] = s;
            aa[i] = a;
            build(i, s, a);
        } else if (q == 'U') {
            long long i;
            cin >> i;
            build(i, -ss[i], -aa[i]);
        } else {
            long long l, r;
            cin >> l >> r;
            r++;
            cout << get_aver(l, r) << endl;
        }
    }

    return 0;
    
}
