#include <bits/stdc++.h>

using namespace std;

int n, m, s;
vector<bool> used;
vector<vector<int>> g, gt;

int main() {
    ios::sync_with_stdio(false);
    ifstream in("game.in");
    if (!in.is_open())
        return -1;
    in >> n >> m >> s;
    g.resize(n + 1);
    gt.resize(n + 1);
    used.resize(n + 1, false);
    for (int i = 1; i <= m; ++i) {
        int from, to;
        in >> from >> to;
        g[from].emplace_back(to);
        gt[to].emplace_back(from); // check for invalidation
    }
    queue<int> q;
    vector<char> res(n + 1, '0');
    vector<int> cnt(n + 1, 0);
    for (int v = 1; v <= n; ++v)
        if (g[v].empty()) {
            q.push(v);
            res[v] = '-';
        }
    int v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (res[v] == '-') {
            for (int from : gt[v])
                if (res[from] == '0') {
                    res[from] = '+';
                    q.push(from);
                }
        } else
            for (int from : gt[v]) {
                cnt[from]++;
                if (cnt[from] == g[from].size()) {
                    res[from] = '-';
                    q.push(from);
                }
            }
    }
    ofstream out("game.out");
    out << (res[s] == '+' ? "First " : "Second ") << "player wins";
    return 0;
}
