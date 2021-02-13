 #include <bits/stdc++.h>

using namespace std;
#define INF 900000000

int n;
vector<vector<unsigned int>> dist;
vector<vector<unsigned int>> weight; // weight[v][mask] -- weight of ham. path with
// end at v which includes set of vertices at mask

 void printVertices(int mask) {
     int i = 0;
     cout << "\nVertices in mask " << mask << ":\n";
     while (i < 32) {
         if (mask & (1 << i))
             cout << i << " ";
         i++;
     }
     cout << "\n";
 }

 int countMask(int mask) {
     int res = 0, i = 0;
     while (i < 32) {
         if (mask & (1 << i))
             res++;
         i++;
     }
     return res;
 }

void ham(int v, int mask) {
//    int mask = (*lastMask)[v];
    printVertices(mask);
    int minV = -1;
    int minWeight = INT_MAX;
    for (int j = 0; j < n; ++j) {
        int nmask = mask | (1 << j);
        if ((((1 << j) & mask) == 0) &&
            weight[v][nmask] > dist[v][j] + weight[j][nmask & ~(1 << v)]) {
            weight[v][nmask] = dist[v][j] + weight[j][nmask & ~(1 << v)];
            minV = j;
//            (*newMask)[minV] = mask | (1 << minV);
        }
    }
}

 unsigned int countPathLen(int i, unsigned int mask) {
     if (weight[i][mask] != INF)
         return weight[i][mask];

     for (int j = 0; j < n; j++) {
         if (i != j && (mask & (1 << j))) {
             weight[i][mask] = min(weight[i][mask],
                                   (countPathLen(j, mask - (1 << j)) + dist[i][j]));
         }                                        //      remove bit 1 << j
     }

     return weight[i][mask];
 }

int main() {
//    ios_base::sync_with_stdio(false);
    freopen("a.in", "r", stdin);
    cin >> n;
    dist.resize(n);
    for (int i = 0; i < n; ++i) {
        dist[i].resize(n + 1, 0);
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];
    }

    size_t allSubsets = 1 << n;
    weight.resize(n);
    for (int v = 0; v < n; ++v) { // doing resize for path of one vertex
        weight[v].resize(allSubsets, INF);
        weight[v][1 << v] = 0;
    }

    weight[0][0] = 0;
    int pathWeight = countPathLen(0, allSubsets - 1), startVertex = -1;
    vector<int> path;
    int mask = allSubsets - 1;
    for (int i = 0; i < n; ++i) {
        if (pathWeight > weight[i][mask]) {
            pathWeight = weight[i][mask];
            startVertex = i;
        }
    }
    cout << pathWeight << "\n";
    path.push_back(startVertex);

    printVertices(mask);
    mask ^= 1 << startVertex;
    while (path.size() != n) {
        printVertices(mask);
        for (int v = 0; v < n; ++v)
            if (pathWeight == weight[v][mask ^ (1 << v)] + dist[startVertex][v]) {
                pathWeight = weight[v][mask ^ (1 << v)];
                startVertex = v;
            }
        path.push_back(startVertex);
        mask ^= 1 << startVertex;
    }
    int sum = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        sum += dist[path[i]][path[i + 1]];
    }
    cout << "\ncheck: " << sum << "\n"
    ;
    for (auto it = path.rbegin(); it != path.rend(); it++)
        cout << *it + 1 << " ";

    return 0;
}
