#define _FORTIFY_SOURCE 0
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

#define pair pair<int, int>

int n, m, timer = 0;

set<int> cut_vertices;
vector<bool> used;
vector<set<int>> fromV;
//vector<set<int>> toV;
vector<int> time_in, up;

void dfs(int v, int p = -1) {
    used[v] = true;
    time_in[v] = up[v] = timer++;
    int children = 0;
    for (int to : fromV[v]) {
        if (to == p) continue;
        if (used[to])
            up[v] = min(up[v], time_in[to]);
        else {
            dfs(to, v);
            up[v] = min(up[v], up[to]);
            if (up[to] >= time_in[v] && p != -1) {
                cut_vertices.insert(v);
            }
            children++;
        }
    }
    if (p == -1 && children > 1)
        cut_vertices.insert(v);
}

int main() {
    ios_base::sync_with_stdio(false);

//    ifstream in("../in.txt");
    cin >> n >> m;
    fromV.resize(n + 1);
    used.resize(n + 1, false);
    time_in.resize(n + 1, -1);
    up.resize(n + 1, -1);

    for (int i = 0, from, to; i < m; i++) {
        cin >> from >> to;
        fromV[from].insert(to);
        fromV[to].insert(from);
    }

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs(i);
        
    cout << cut_vertices.size() << "\n";
    for (int cut_vertice : cut_vertices)
        cout << cut_vertice << "\n";
    return 0;
}

