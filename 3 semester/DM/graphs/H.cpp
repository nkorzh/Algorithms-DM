/* Chromatic polynome */

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

#define pair pair<int, int>
#define ENTERED 1
#define EXITED 2
int n, m;
vector<vector<bool>> g;
map<pair, int> edge_number;
vector<int> status;
vector<pair> edges; // {number, weight}

inline bool is_edge(int i, int j) {
    return g[i][j];
}
inline int getEdgeNumber(int u, int v) {
    if (u < v)
        return edge_number[{u, v}];
    return edge_number[{v, u}];
}
void writeTreePoly(vector<int> & p, int x, int y = 0);
void multiplyPolys(vector<int> &p, vector<int> &q);
bool insideSet(int v, set<int> & s) {
    if (s.find(v) != s.end())
        return true;
    return false;
}


vector<int> subtractPolys(vector<int> & a, vector<int> & b) {
    if (a.size() != b.size())
        return {};
    vector<int> res(a.size());
    for (int i = 0; i < res.size(); ++i)
        res[i] = a[i] - b[i];
    return res;
}

class GraphCondition {
    int contracted;
    int disabled;
    size_t edgesAmount;
    size_t verticesAmount;
public:
    GraphCondition() : contracted(0), disabled(0), edgesAmount(m), verticesAmount(n) {}
    GraphCondition(int c, int d) : contracted(c), disabled(d), edgesAmount(m), verticesAmount(n) {
        for (int i = 0; i < 32; ++i)
            if (contracted & (1 << i)) edgesAmount--;
    }
    void initParameters() { verticesAmount = n; edgesAmount = m; }
    void disable(int edgeNum) {
        if (disabled & (1 << edgeNum))
            edgeNum++;
        disabled |= 1 << edgeNum;
        edgesAmount--;
    }
    void contract(int edgeNum) {
        if (contracted & (1 << edgeNum))
            edgeNum++;
        contracted |= 1 << edgeNum;
        edgesAmount--; verticesAmount--;
    }
    [[nodiscard]] bool isDisabled(int edgeNum) const {
        return disabled & (1 << edgeNum);
    }
    [[nodiscard]] bool isDisabled(int u, int v) const {
        return disabled & (1 << getEdgeNumber(u, v));
    }
    [[nodiscard]] bool isContracted(int edgeNum) const {
        return contracted & (1 << edgeNum);
    }
    [[nodiscard]] bool isContracted(int u, int v) const {
        return contracted & (1 << getEdgeNumber(u, v));
    }
    [[nodiscard]] bool needTreeCheck() const { return edgesAmount <= verticesAmount; }
};

GraphCondition currentGraph;

// TODO: use set of parents
// give set by link, keep the last state only when going by contracted edge
// returns -1 if it is not a tree or amount of tree vertices
int dfs(int v, set<int> parent = {}) {
    status[v] = ENTERED;
    int amount = 0, retVal;
    for (int u = 1; u <= n; u++) {
        retVal = -1;
        if (insideSet(u, parent)) continue;
        if (g[v][u] && !currentGraph.isDisabled(u, v)) {
            bool edgeContracted = currentGraph.isContracted(u, v);
            if (!status[u]) {
                if (!edgeContracted)
                    retVal = dfs(u, {v});
                else {
                    parent.insert(v);
                    retVal = dfs(u, parent);
                }
            } else if (edgeContracted)
                continue;
            else return -1;
            
            if (retVal == -1) return -1;
            else amount += retVal;

            if (currentGraph.isContracted(u, v)) amount--;
        }
    }
    status[v] = EXITED;
    return amount + 1;
}
/**
 * Checks if graph is a tree
 * @param graph
 * @return {nodes inside tree, isolated nodes}
 */
 // multiply polinomials of different trees, keep amount of free vertices
bool isTree(GraphCondition graph, vector<int> & poly) {
    swap(currentGraph, graph);
    status.assign(n + 1, 0);

    int treeVertices = dfs(1, {});
    if (treeVertices == -1) {
        swap(currentGraph, graph);
        return false;
    } else {
        poly.resize(n + 1, 0);
        writeTreePoly(poly, treeVertices);
    }

    for (int v = 2; v <= n; ++v)
        if (!status[v]) {
            treeVertices = dfs(v, {});
            if (treeVertices != -1) {
                vector<int> q(treeVertices + 1, 0);
                writeTreePoly(q, treeVertices);
                multiplyPolys(poly, q);
            } else {
                swap(currentGraph, graph);
                return false;
            }
        }

    swap(currentGraph, graph);
    return true;
}
/**
 * Counts chromatic polinomial of the graph
 * @param graph
 * @return vector of coefficients
 */
 vector<int> getPoly(GraphCondition & graph, size_t nextEdge = 0) {
    if (graph.needTreeCheck()) {
        vector<int> poly;
        if (isTree(graph, poly))
            return poly;
    }
    GraphCondition gDisabled = graph;
    gDisabled.disable(edges[nextEdge].first);
    vector<int> polyDisabled = getPoly(gDisabled, nextEdge + 1);

    GraphCondition gContracted = graph;
    gContracted.contract(edges[nextEdge].first);
    vector<int> polyContracted = getPoly(gContracted, nextEdge + 1);

    return subtractPolys(polyDisabled, polyContracted);
}

int main() {
    chrono::high_resolution_clock::time_point t_start = chrono::high_resolution_clock::now();
    freopen("a.in", "r", stdin);
//    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    g.resize(n + 1);
    edges.resize(m);
    vector<int> deg(n + 1, 0);
    for (int i = 1; i <= n; ++i) g[i].resize(n + 1, false);
    for (int i = 0, v, u; i < m; ++i) {
        cin >> v >> u;
        g[u][v] = g[v][u] = true;
        if (v > u) swap(v, u);
        edge_number[{v, u}] = i;
        edges[i] = {i, 0};
        deg[u]++, deg[v]++;
    }

    // its simpler to find edge with max weight for first deletion
    for (int v = 1; v <= n; ++v)
        for (int u = 1; u <= n; ++u)
            if (g[v][u]) 
                edges[edge_number[{v, u}]].second += deg[v];
    
    sort(edges.begin(), edges.end(), [](const auto & a, const auto & b) {
        return a.second > b.second;
    });
    currentGraph.initParameters();
    auto res = getPoly(currentGraph);

    for (int i = res.size(); i >= 0; --i) {
        cout << i << ": " << res[i] << "\n";
    }

    cout << "Done\n"<<
        chrono::duration<double, std::milli>(chrono::high_resolution_clock::now() - t_start).count() << " ms\n";
    return 0;
}

// count t(t-1)^(x-1) * t^y; where treeParameters = {x, y}
void writeTreePoly(vector<int> & p, int x, int y ) {
    static vector<vector<int>> binomialCoef = {{1},
                                               {1, 1},
                                               {1, 2,  1},
                                               {1, 3,  3,  1},
                                               {1, 4,  6,  4,   1},
                                               {1, 5,  10, 10,  5,   1},
                                               {1, 6,  15, 20,  15,  6,   1},
                                               {1, 7,  21, 35,  35,  21,  7,   1},
                                               {1, 8,  28, 56,  70,  56,  28,  8,   1},
                                               {1, 9,  36, 84,  126, 126, 84,  36,  9,  1},
                                               {1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1}};
    x--;
    for (int k = 0; k <= x; k++)
        p[x - k + y + 1] = binomialCoef[x][k] * (k % 2 == 0 ? 1 : -1);
    if (x < 0)
        p[y] = 1;
}

void multiplyPolys(vector<int> &p, vector<int> &q) {
    vector<int> res(p.size() + q.size(), 0);

    for (int i = 0; i < p.size(); ++i)
        for (int j = 0; j < q.size(); ++j)
            res[i + j] += p[i] * q[j];

    p.resize(res.size());
    for (int i = 0; i < p.size(); ++i)
        p[i] = res[i];
}
