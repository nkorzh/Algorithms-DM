#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to, w;
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

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    g.resize(n + 1);
    d.resize(n + 1, INTMAX_MAX);
    d[1] = 0;
    used.resize(n + 1, false);
    int from, to, w;
    for (int i = 1; i <= m; ++i) {
        cin >> from >> to >> w;
        g[from].emplace_back(to, w);
        g[to].emplace_back(from, w);
    }
    int v, counter = 0;
    set<int> s = {1};
    mapa.emplace(0, s);
    while (counter < n) {
        v = -1;
        while (v == -1 || used[v]) {
            auto ld_it = mapa.begin(); // ld_it - least distance iterator
            v = *(ld_it->second.begin()); // get the node index
            ld_it->second.erase(ld_it->second.begin()); // erase node from set (not to take it again)
            if (ld_it->second.empty()) mapa.erase(ld_it);
        }
        used[v] = true;
        for (auto & e : g[v])
            if (d[v] + e.w < d[e.to]) {
                d[e.to] = d[v] + e.w;
                mapa[d[e.to]].insert(e.to);
            }
        counter++;
    }

    for (int i = 1; i <= n; ++i) cout << d[i] << " ";
    return 0;
}
