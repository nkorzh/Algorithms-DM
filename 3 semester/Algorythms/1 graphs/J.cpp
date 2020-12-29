#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

struct edge {
    int to;
    int w;
    edge(int to = -1, int w = 0) : to(to), w(w) {}
};

struct edge_compare {
    bool operator()(const edge & a, const edge & b) const {
        return a.w < b.w;
    }
};

int main() {
    int n, m;
//    ifstream in("../in.txt");
    cin >> n >> m;
//    in >> n >> m;
//    set<edge> s;
    vector<set<edge, edge_compare>> edges(n + 1);
    for (int i = 0, from, to, w; i < m; i++) {
        cin >> from >> to >> w;
        if (from == to) continue;
//        in >> from >> to >> w;
        edges[from].insert(edge(to, w));
        edges[to].insert(edge(from, w));
    }
    unordered_set<int> sp_tree_vertices;
    sp_tree_vertices.insert(1);
    long long ans = 0;
    int min, min_v;
    edge e;
    while (sp_tree_vertices.size() != n) {
        min = INT_MAX; min_v = 0;
        for (int v : sp_tree_vertices) {
            if (edges[v].empty()) continue;
            e = *(edges[v].begin());
            if (e.w < min) min_v = v, min = e.w;
        }
        e = *(edges[min_v].begin());
        edges[min_v].erase(edges[min_v].begin());
        edges[e.to].erase(edges[e.to].find(edge(min_v, e.w)));
        ans += e.w;
        sp_tree_vertices.insert(e.to);
    }
    cout << ans;
}
