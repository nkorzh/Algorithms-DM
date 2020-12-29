#include <bits/stdc++.h>

using namespace std;

const long long INF = INTMAX_MAX;

struct edge {
    int to;
    int w;
    edge() : to(-1), w(INT_MAX) {}
    edge(int t, int w) : to(t), w(w) {}
    bool operator<(const edge & b) const {
        return w < b.w;
    }
};

int n, m;
vector<long long> d;
vector<bool> used;
vector<vector<edge>> g;
map<long long, set<int>> mapa;
map<int, map<int, long long>> di;

void dijkstra(int a, int b = 1, int c = 1) {
    d.assign(n + 1, INF);
    used.assign(n + 1, false);
    d[a] = 0;
    int v, counter = 0;
    set<int> s = {a}; // starting to walk from a
    mapa.emplace(0, s); // emplaced set with single vertex a to zero-distance mapa place
    while (counter < n) {
        v = -1;
        while (!mapa.empty() && (v == -1 || used[v])) {
            auto ld_it = mapa.begin(); // ld_it - least distance iterator
            v = *(ld_it->second.begin()); // get the node index
            ld_it->second.erase(ld_it->second.begin()); // erase node from set (not to take it again)
            if (ld_it->second.empty()) mapa.erase(ld_it);
        }
        if (v == -1 || used[v]) break; // graph has more than 1 connected components
        used[v] = true;
        for (auto & e : g[v])
            if (d[v] + e.w <= d[e.to]) {
                d[e.to] = d[v] + e.w;
                mapa[d[e.to]].insert(e.to);
            }
        for (int i = 1; i < d.size(); ++i)
            if (d[i] == INF)
                cout << "∞ ";
            else
                cout << d[i] << " ";
        cout << "\n";
        counter++;
    }
//    di[a][b] = d[b];
//    di[a][c] = d[c];
}

int main() {
    ios::sync_with_stdio(false);
    freopen("game.in", "r", stdin);
    cin >> n >> m;
    g.resize(n + 1);
    d.resize(n + 1, INF);
    used.resize(n + 1, false);
    int from, to, w;
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to >> w;
        g[from].emplace_back(to, w);
//        g[to].emplace_back(from, w);
    }
    from = 1;
    dijkstra(from);
//    vector<int> kefir_point(3);
//    for (int & i : kefir_point) cin >> i;
//    for (int i = 0; i < 3; i++)
//        dijkstra(kefir_point[i], kefir_point[(i + 1) % 3], kefir_point[(i + 2) % 3]);
//    long long res = INF;
//    for (int i = 0; i < 3; i++) {
//        int a = kefir_point[i];
//        int b = kefir_point[(i + 1) % 3];
//        int c = kefir_point[(i + 2) % 3];
//        if (di[a][b] == INF && di[a][c] == INF) {
//            cout << -1;
//            return 0;
//        }
//        res = min(res, di[a][b] + di[b][c]);
//        res = min(res, di[a][c] + di[c][b]);
//    }
//    cout << res;
    return 0;
}
