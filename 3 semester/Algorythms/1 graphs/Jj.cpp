#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int from;
    int to;
    int w;
    edge(int s, int e, int w) : from(s), to(e), w(w) {}
};

vector<int> dsu;
int snm_find(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = snm_find(dsu[x]);
}

void snm_union(int x, int y) {
    int pred_x = snm_find(x);
    int pred_y = snm_find(y);
    dsu[pred_x] = pred_y;
}

int main() {
    vector<edge> edges;

    int n, m;
//    ifstream in("../in.txt");
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        dsu.push_back(i);
    for (int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        edges.emplace_back(--u, --v, w);
    }
    sort(edges.begin(), edges.end(), [](const edge & l, const edge & r) { return l.w < r.w; });
    long long ans = 0;
    for (auto edge : edges)
        if (snm_find(edge.from) != snm_find(edge.to)) {
            snm_union(edge.from, edge.to);
            ans += edge.w;
        }
    cout << ans;
}
