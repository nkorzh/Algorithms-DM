/* Prufer code */
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
vector<int> parent, deg, result;

void dfs(int v) {
    for (int to : g[v])
        if (to != parent[v]) {
            parent[to] = v;
            dfs(to);
        }
}

void prufer_code() {
    int ptr = 1;
    while (ptr < n && deg[ptr] != 1)
        ++ptr;
    int leaf = ptr;
    for (int i = 0, next; i < n - 2; ++i) {
        next = parent[leaf];
        if (next != -1) result.push_back(next);
        if (next != -1 && --deg[next] == 1 && next < ptr)
            leaf = next;
        else {
            ptr++;
            while (ptr <= n && deg[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
}

int main() {
//    freopen("a.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> n;
    g.resize(n + 1); parent.resize(n + 1);
    deg.resize(n + 1, 0);
    for (int i = 0, from, to; i < n - 1; ++i) {
        cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
        deg[from]++; deg[to]++;
    }
    parent[n] = -1;
    dfs(n);
    prufer_code();
    for (int c : result) cout << c << " ";
    return 0;
}