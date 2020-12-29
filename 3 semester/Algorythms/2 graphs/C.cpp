#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e9;

struct edge {
    int to, w;
    edge() : to(-1), w(INT_MAX) {}
    edge(int t, int w) : to(t), w(w) {}
    bool operator<(const edge & b) const {
        return w < b.w;
    }
};


int n;
vector<long long> d, p;
vector<vector<edge>> g;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    g.resize(n + 1);
    d.resize(n + 1, INT_MAX);
    p.resize(n + 1, -1);
    d[1] = 0;
    int w;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> w;
            if (w != 100000)
                g[i].emplace_back(j, w);
        }

    int hasCycle = -1;
    for (int iteration = 0; iteration < n; ++iteration) {
        hasCycle = -1;
        for (int u = 1; u <= n; ++u)
            for (const edge &e : g[u])
                if (d[u] + e.w < d[e.to]) {
                    d[e.to] = max(-INF, d[u] + e.w);
                    p[e.to] = u;
                    hasCycle = e.to;
                }
    }

    if (hasCycle != -1) {
        vector<int> ans;
        int u, v = hasCycle;
        for (int i = 0; i < n; ++i) v = p[v];
        u = v;
        while (true) {
            if (ans.size() > 1 && v == u) break;
            ans.push_back(v);
            v = p[v];
        }
        cout << "YES\n" << ans.size() << "\n";
        for_each(ans.rbegin(), ans.rend(), [](int it) {
            cout << it << " ";
        });
        return 0;
    }

    cout << "NO";
    return 0;
}
