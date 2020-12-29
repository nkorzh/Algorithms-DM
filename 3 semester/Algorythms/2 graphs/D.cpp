#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

struct edge {
    int to, w;
    edge() : to(-1), w(INT_MAX) {}
    edge(int t, int w) : to(t), w(w) {}
    bool operator<(const edge & b) const {
        return w < b.w;
    }
};

int n, m, max_pathlen, s;
vector<vector<int>> d;
vector<vector<edge>> g;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> max_pathlen >> s;
    g.resize(n + 1);
    d.resize(n + 1);
    int from, to, w;
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to >> w;
        g[from].emplace_back(to, w);
    }
    for (int i = 1; i <= n; ++i)
        d[i].resize(max_pathlen + 1, INF);

    d[s][0] = 0;

    int path;
    for (int iteration = 0; iteration < max_pathlen; ++iteration) {
        for (int u = 1; u <= n; ++u)
            for (const edge &e : g[u]) {
                path = 0;
                while (path < max_pathlen) {
                    if (d[u][path] != INF && d[u][path] + e.w < d[e.to][path + 1])
                        d[e.to][path + 1] = d[u][path] + e.w;
                    path++;
                }
            }
    }

    for (int i = 1; i <= n; ++i) {
        if (d[i][max_pathlen] == INF) cout << "-1\n";
        else cout << d[i][max_pathlen] << "\n";
    }
    return 0;
}
