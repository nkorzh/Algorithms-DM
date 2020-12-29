#define _FORTIFY_SOURCE 0
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

#define pair pair<int, int>

int n, m, timer, bridgeAmount = 0;

map<pair, bool> is_bridge;
vector<pair> edges;

vector<bool> used;
vector<vector<int>> fromV;
//vector<set<int>> toV;
vector<int> time_in, up;

void dfs(int v, int p = -1) {
    used[v] = true;
    time_in[v] = up[v] = timer++;
    for (int to : fromV[v]) {
        if (to == p) continue;
        if (used[to])
            up[v] = min(up[v], time_in[to]);
        else {
            dfs(to, v);
            up[v] = min(up[v], up[to]);
            if (up[to] > time_in[v]) {
                bridgeAmount++;
                is_bridge[pair(v, to)] = true;
                is_bridge[pair(to, v)] = true;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs(i);
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    fromV.resize(n + 1);
    used.resize(n + 1, false);
    time_in.resize(n + 1, -1);
    up.resize(n + 1, -1);

    for (int i = 0, from, to; i < m; i++) {
        cin >> from >> to;
        fromV[from].push_back(to);
        fromV[to].push_back(from);
        edges.emplace_back(from, to);
    }

    find_bridges();
    cout << bridgeAmount << "\n";
    for (int num = 0; num < m; ++num) {
        pair edge = edges[num];
        if (is_bridge[edge])
            cout << num + 1 << " ";
    }
    return 0;
}

