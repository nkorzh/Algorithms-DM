#include <bits/stdc++.h>

using namespace std;

const long long INF = 2 * powl(10, 18) + 1;

struct edge {
    int to;
    long long w;
    edge() : to(-1), w(INF) {}
    edge(int t, long long w) : to(t), w(w) {}
    bool operator<(const edge & b) const {
        return w < b.w;
    }
};

int n, m, s;
vector<long long> d;
vector<vector<edge>> g;
vector<bool> checked;

void mark_inf_dist(int v) {
    checked[v] = true;
    for (const edge & e : g[v])
        if (!checked[e.to]) mark_inf_dist(e.to);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    g.resize(n + 1);
    d.resize(n + 1, INF);
    checked.resize(n + 1, false);
    long long w;
    int from, to;
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to >> w;
        g[from].emplace_back(to, w);
    }
    d[s] = 0;

    for (int iteration = 0; iteration < n; ++iteration) {
        for (int u = 1; u <= n; ++u)
            for (const edge &e : g[u])
                if (d[u] != INF && d[u] + e.w < d[e.to])
                    d[e.to] = d[u] + e.w;
    }

    for (int u = 1; u <= n; ++u)
        for (const edge &e : g[u])
            if (d[u] != INF && d[u] + e.w < d[e.to] && !checked[e.to])
                mark_inf_dist(e.to);

    for (int v = 1; v <= n; ++v) {
        if (d[v] == INF) cout << "*\n";
        else if (checked[v]) cout << "-\n";
        else cout << d[v] << "\n";
    }

    return 0;
}
