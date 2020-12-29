#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;
#define MAX_N 10000

vector<int> used, color;
vector<vector<int>> g, gt;

int n, m, maxColor = 0;
stack<int> st;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v])
        if (!used[to]) dfs(to);
    st.push(v);
}

void dfsr(int i, int col) {
    used[i] = 2;
    color[i] = col;
    for (int to : gt[i])
        if (used[to] != 2) dfsr(to, col);
}

int main() {
    ios::sync_with_stdio(false);

//    ifstream in("../in.txt");
    cin >> n >> m;
//    in >> n >> m;
    g.resize(n + 1);
    gt.resize(n + 1);
    used.resize(n + 1);
    color.resize(n + 1);

    for (int i = 0, from, to; i < m; ++i) {
        cin >> from >> to;
//        in >> from >> to;
        g[from].push_back(to);
        gt[to].push_back(from);
    }

    for (int i = 1; i <= n; i++)
        if (!used[i]) dfs(i);

    while (!st.empty()) {
        int top_v = st.top();
        if (used[top_v] != 2)
            dfsr(top_v, maxColor++);
        st.pop();
    }

    set<int> gg[MAX_N];

    for (int from = 1; from <= n; from++)
        for (int to : g[from])
            if (color[from] != color[to])
                gg[color[from]].insert(color[to]);

    int ans = 0;
    for (auto & i : gg)
        ans += i.size();

    cout << ans;
}


