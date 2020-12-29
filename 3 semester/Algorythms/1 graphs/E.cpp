#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

#define pair pair<int, int>

int n, m, timer = 0, maxColor = 0, start;

vector<pair> edges;
set<int> cut_vertices;
vector<bool> used;
vector<vector<int>> fromV;
vector<int> time_in, up;
vector<map<int, int>> color;

void paint(int v, int col, int p = -1) {
    bool firstEdgeBack = true;
    used[v] = true;

    for (int to : fromV[v]) {
        if (to == p && firstEdgeBack) {  // indexes!
            firstEdgeBack = false;
            continue;
        }
        if (!used[to])
            if (up[to] >= time_in[v]) { // (v, to) is a bridge
                color[v][to] = ++maxColor;
                color[to][v] = maxColor;
                paint(to, maxColor, v);
            } else {
                color[v][to] = col;
                color[to][v] = col;
                paint(to, col, v);
            }
        else if (time_in[to] < time_in[v]) {
            color[v][to] = col;
            color[to][v] = col;
        }
    }
}

void dfs(int v, int p = -1) {
    bool firstEdgeBack = true;
    used[v] = true;
    time_in[v] = up[v] = timer++;
    int children = 0;
    for (int to : fromV[v]) {
        if (to == p && firstEdgeBack) {
            firstEdgeBack = false;
            continue;
        }
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

    ifstream in("../in.txt");
//    cin >> n >> m;
    in >> n >> m;
    fromV.resize(n + 1);
    used.resize(n + 1, false);
    time_in.resize(n + 1, -1);
    up.resize(n + 1, -1);
    color.resize(n + 1);


    for (int i = 0, from, to; i < m; i++) {
//        cin >> from >> to;
        in >> from >> to;
        fromV[from].push_back(to);
        fromV[to].push_back(from);
        edges.emplace_back(from, to);

    }

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs(i);

    used.assign(n + 1, false);
    for (int i = 1; i <= n; i++)
        if (!used[i])
            paint(i, maxColor), maxColor++;

    cout << maxColor - 1 << "\n";
    int c = 1, cur = -10;
    map<int, int> table;
    table[color[edges.front().first][edges.front().second]] = c;
    for (pair & edge : edges) {
        cur = color[edge.first][edge.second];
        if (!table[cur])
            table[cur] = ++c;
        cout << table[cur] << " ";
    }
    return 0;
}

