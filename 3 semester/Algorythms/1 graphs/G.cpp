#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> gt;
stack<int> top_sort;
vector<bool> used;
vector<int> comp;
int n;

void dfs(int u) {
    used[u] = true;
    for (auto v : g[u])
        if (!used[v])
            dfs(v);
    top_sort.push(u);
}

void dfs_color(int u, int c) {
    used[u] = true;
    comp[u] = c;
    for (auto v : gt[u])
        if (comp[v] == -1)
            dfs_color(v, c);
}

int main() {
    ios::sync_with_stdio(false);
    int m, nd;
    cin >> n >> m;
    nd = n * 2;
    g.resize(nd);
    gt.resize(nd);
    used.resize(nd, false);
    comp.resize(nd, -1);
    map<string, int> name_to_numbet;
    vector<string> numbet_to_name(n);
    string name;
    for (int i = 0; i < n; i++) {
        cin >> name;
        name_to_numbet["+"+name] = i;
        name_to_numbet["-"+name] = n + i;
        numbet_to_name[i] = name;
    }
    string name2;
    char c;
    for (int i = 0; i < m; i++) {
        cin >> name >> c >> c >> name2;
        int u = name_to_numbet[name];
        int v = name_to_numbet[name2];
        g[u].push_back(v);
        gt[v].push_back(u);
        u = (u + n) % nd;
        v = (v + n) % nd;
        g[v].push_back(u);
        gt[u].push_back(v);
    }

    for (int i = 0; i < nd; i++)
        if (!used[i])
            dfs(i);

    int color = 0;

    while (!top_sort.empty()) {
        int v = top_sort.top();
        if (comp[v] == -1)
            dfs_color(v, color++);
        top_sort.pop();
    }

    for (int i = 0; i < n; i++)
        if (comp[i] == comp[i + n]) {
            cout << -1;
            return 0;
        }

    vector<string> ans;
    for (int i = 0; i < n; i++)
        if (comp[i] > comp[i + n])
            ans.push_back(numbet_to_name[i]);

    cout << ans.size() << endl;
    for (const auto& a : ans)
        cout << a << endl;
    return 0;
}
