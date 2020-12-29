#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int p = 31;
vector<ull> p_pow (100005), h(100005, 0);


void myhash(string & s) {
    ull hash = 0;
    for (int i = 0; i < s.size(); ++i) {
        h[i] += (s[i] - 'a' + 1) * p_pow[i];
        if (i > 0) h[i] += h[i - 1];
    }
}

// 1 <= l <= r <= 10^5
ull substr_hash(int l, int r) {
    if (l == 1) return h[r - 1];
    return h[r - 1] - h[l - 2];
}

int main() {
    ios::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);   
    string s;
    int a, b, c, d, m;
    cin >> s;
    cin >> m;

    p_pow[0] = 1;
    for (size_t i = 1; i < s.length() + 1; ++i)
        p_pow[i] = p_pow[i - 1] * p;

    myhash(s);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        if (b - a == d - c) {
            ull left, right;
            if (c < a) swap(a, c), swap(b, d);
            left = substr_hash(a, b);
            right = substr_hash(c, d);
            if (left * p_pow[c - a] == right) {
                cout << "Yes\n";
                continue;
            }
        }
        cout << "No\n";
    }
    return 0;
}
