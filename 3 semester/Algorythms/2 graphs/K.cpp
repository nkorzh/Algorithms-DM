#include <bits/stdc++.h>

using namespace std;

int n, s;
vector<bool> used;
vector<vector<int>> g;
vector<int> stree_sz, gr;
map<pair<int, int>, int> edge_number;

int grundy(int v) {
    used[v] = true;
    int res = 0;
    for (int i : g[v])
        if (!used[i])
            res ^= (grundy(i) + 1);
    return gr[v] = res;
}

int stree_count(int v) {
    used[v] = true;
    for (int i : g[v])
        if (!used[i])
            stree_sz[v] += stree_count(i);
    return stree_sz[v];
}

void find_edge(int v, int num_to_get = 0) {
    used[v] = true;
    int cur;
    for (int to : g[v]) {
        if (used[to]) continue;
        if ((cur = (gr[v] ^ (gr[to] + 1) ^ num_to_get)) == 0) { // find such edge that after removing it to gr[s] == 0
            cout << edge_number[{v, to}];
            exit(0);
        }
        find_edge(to, cur - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    ifstream in("game.in");
//    if (!in.is_open())
//        return -1;
    cin >> n >> s;
//    in >> n >> s;
    g.resize(n + 1);
    stree_sz.resize(n + 1, 1);
    gr.resize(n + 1);
    used.resize(n + 1, false);
    int from, to;
    for (int i = 1; i < n; ++i) {
        cin >> from >> to;
//        in >> from >> to;
        g[from].emplace_back(to);
        g[to].emplace_back(from);
        edge_number[{from, to}] = edge_number[{to, from}] = i;
    }

    stree_count(s);
    used.assign(n + 1, false);
    grundy(s);
    if (gr[s] == 0) {
        cout << 2;
        return 0;
    }
    used.assign(n + 1, false);
    cout << "1\n";
    find_edge(s);
    return 0;
}
