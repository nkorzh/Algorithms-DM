#include <bits/stdc++.h>

using namespace std;
#define MAXN 100000
int n, m;
vector<bool> used;
vector<vector<int>> g;
vector<int> res;

int mex (int v) {
    static bool usedg[MAXN+1];
    int c = g[v].size() + 1;

    for (int i : g[v])
        if (res[i] <= MAXN)
            usedg[res[i]] = true;

    int result = 0;
    for (int i = 0; i < c; ++i)
        if (!usedg[i]) {
            result = i;
            break;
        }
    for (int i : g[v])
        if (res[i] <= MAXN)
            usedg[res[i]] = false;

    return result;
}

void grundy(int v) {
    if (res[v] <= MAXN) return;
    if (g[v].empty())
        res[v] = 0;
    else
        res[v] = mex(v);
}

void count(int v) {
    used[v] = true;
    for (int i : g[v])
        if (!used[i])
            count(i);

    grundy(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    g.resize(n + 1);
    used.resize(n + 1, false);
    res.resize(n + 1, MAXN + 100);
    int from, to;
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to;
        g[from].emplace_back(to);
    }

    for (int i = 1; i <= n; ++i)
        if (!used[i])
            count(i);

    for (int i = 1; i <= n; ++i)
        cout << res[i] << "\n";
    return 0;
}
