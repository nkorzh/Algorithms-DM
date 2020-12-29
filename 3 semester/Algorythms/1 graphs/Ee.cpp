#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <map>


using namespace std;
//#define pair pair<int, int>

int n, m, timer = 1, componentsAmount = 0;

struct edge {
    int to, id;
    edge(int where = -1, int id = -1) : to(where), id(id) {}
};
vector<vector<edge>> fromV; // pair = (to, edge’s index)
stack<edge> st;
vector<int> time_in, up;
vector<int> edge_comp;


void dfs(int v, int prev = -1) {
    up[v] = time_in[v] = ++timer;
    for (auto curEdge : fromV[v]) {
        if (curEdge.id == prev) continue;
        if (!time_in[curEdge.to]) {
            st.push(curEdge);
            dfs(curEdge.to, curEdge.id);
            up[v] = min(up[v], up[curEdge.to]);
            if (prev == -1 || up[curEdge.to] >= time_in[v]) {
                componentsAmount++;
                while (true) {
                    int edge_id = st.top().id;
                    st.pop();
                    edge_comp[edge_id] = componentsAmount;
                    if (edge_id == curEdge.id) break;
                }
            }
        } else {
            if (time_in[curEdge.to] < time_in[v])
                st.push(curEdge);
            up[v] = min(up[v], time_in[curEdge.to]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

//    ifstream in("../in.txt");
    cin >> n >> m;
//    in >> n >> m;
    fromV.resize(n + 1);
    time_in.resize(n + 1, 0);
    up.resize(n + 1, 0);
    edge_comp.resize(m);

    for (int i = 0, from, to; i < m; i++) {
        cin >> from >> to;
//        in >> from >> to;
        fromV[from].push_back({to, i});
        fromV[to].push_back({from, i});
    }
    for (int i = 1; i <= n; i++)
        if (!time_in[i])
            dfs(i);

    cout << componentsAmount << "\n";
    int c = 0, cur = -10;
    map<int, int> table;
    for (int col : edge_comp) {
        if (!table[col])
            table[col] = ++c;
        cout << table[col] << " ";
    }
    return 0;
}
