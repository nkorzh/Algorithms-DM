#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<set<int>> graph;
vector<int> list;

bool isCyclic = false;
int n, m;

enum class VertexType : int {
    white, gray, black
};
vector<VertexType> type;

void dfs(int i) {
    type[i] = VertexType::gray;
    for (int to : graph[i]) {
        if (type[to] == VertexType::gray) isCyclic = true;

        if (type[to] == VertexType::white) dfs(to);
    }
    type[i] = VertexType::black;
    list.emplace_back(i);
}

int main() {
    cin >> n >> m;

    graph.resize(n + 1); type.resize(n + 1);
    for (int i = 0, from, to; i < n; i++) {
        cin >> from >> to;
        graph[from].insert(to);
    }

    for (int i = 1; i <= n; i++) if (type[i] == VertexType::white) dfs(i);

    if (isCyclic) cout << -1;
    else
        for_each(list.rbegin(), list.rend(), [](int i) { cout << i << " "; });
    return 0;
}