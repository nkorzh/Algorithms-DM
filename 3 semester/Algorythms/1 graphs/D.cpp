#define _FORTIFY_SOURCE 0

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <stack>
#include <map>


using namespace std;

#define pair pair<int, int>
#define vertices vector<int>
#define insert push_back // or push_back

int n, m, timer;
int maxColor = 0;

vector<vertices> fromV;

vector<bool> used;
vector<int> time_in, up;

map<pair, bool> is_bridge;
vector<pair> edges;

vector<int> colors;

void paint(int v) {
    used[v] = true;
    colors[v] = maxColor;

    for (int to : fromV[v])
        if (colors[to] == -1)
            paint(to);
}

void dfs(int v, int p = -1) {
    bool firstEdgeBack = true;
    used[v] = true;
    time_in[v] = up[v] = timer++;
//    s.push(v);
    for (int to : fromV[v]) {
        if (to == p && firstEdgeBack) {
            firstEdgeBack = false;
            continue;
        }
        if (used[to]) // back
            up[v] = min(up[v], time_in[to]);
        else { // !used[to]
            dfs(to, v);
            up[v] = min(up[v], up[to]);
            if (up[to] > time_in[v]) { // (v, to) - bridge, paint that component
//                paint(to);
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
//    ifstream in("../in.txt");
    cin >> n >> m;
    fromV.resize(n + 1);
    used.resize(n + 1, false);
    time_in.resize(n + 1, -1);
    up.resize(n + 1, -1);
    colors.resize(n + 1, -1);

    for (int i = 0, from, to; i < m; i++) {
        cin >> from >> to;
        fromV[from].insert(to);
        fromV[to].insert(from);
        edges.emplace_back(from, to);
    }

    find_bridges();
    // remove bridges
    vector<vertices> newG(n + 1);
    for (auto & edge : edges)
        if (!is_bridge[edge]) {
            newG[edge.first].insert(edge.second);
            newG[edge.second].insert(edge.first);
        }
    fromV.clear();
    fromV = move(newG);
//    used.assign(n + 1, false);
    // paint all components
    for (int v = 1; v <= n; ++v)
        if (colors[v] == -1) {
            maxColor++;
            paint(v);
        }
        
    cout << maxColor << "\n";
    for (int v = 1; v <= n; v++)
        cout << colors[v] << " ";
    return 0;
}

