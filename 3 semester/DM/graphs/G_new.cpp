/* Greedy coloring with BFS */
#include <bits/stdc++.h>
using namespace std;

#define pair pair<int, int>
int n, m; /* 3 <= n <= 9999; 2 <= m <= 100 000 */

struct vertex {
    int color;
    set<int> to_set;
    vertex() : color(-1) {}
    void emplace(int v) {
        to_set.emplace(v);
    }
};
vector<vertex> g;
vector<bool> available;

bool color(int from) {
    available.assign(available.size(), true);
    for (int v : g[from].to_set) {
        if (g[v].color != -1)
            available[g[v].color] = false;
    }
    for (int i = 1; i < available.size(); ++i)
        if (available[i]) {
            g[from].color = i;
            return true;
        }
    return false;
}
void bfs(int from) {
    queue<int> q;
    if (!color(from)) cerr << "no available!\n";
    q.push(from);
    while (!q.empty()) {
        from = q.front(); q.pop();
        for (int to : g[from].to_set)
            if (g[to].color == -1) {
                if (!color(to)) cerr << "no available!\n";
                q.push(to);
            }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n >> m;
    g.resize(n + 1);

    vector<int> degs(n + 1, 0);
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        g[a].emplace(b);
        g[b].emplace(a);
        degs[a]++;
        degs[b]++;
    }
    int max_deg = -1, max_deg_index = -1;
    for (int v = 1; v <= n; ++v)
        if (max_deg < degs[v]) {
            max_deg = degs[v];
            max_deg_index = v;
        }
    available.resize((max_deg | 1) + 1, false);
    bfs(max_deg_index);
    cout << (max_deg | 1) << "\n";
    for (int v = 1; v <= n; ++v)
        cout << g[v].color << "\n";
    return 0;
}
