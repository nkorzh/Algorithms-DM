#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define INF 100000000

int n, m; // <= 10 000
enum class Move : int {
    R, D
};
vector<int> cost;
vector<vector<int>> d;
vector<vector<Move>> path;

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n >> m;
    d.resize(n + 1);
    path.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
        d[i].resize(m + 1);
        path[i].resize(m + 1);
        for (int j = 1; j <= m; ++j)
            cin >> d[i][j];
    }
    // d[i, 1]
    for (int i = 2; i <= n; ++i)
        d[i][1] += d[i - 1][1], path[i][1] = Move::D;
    // d[j, 1]
    for (int j = 2; j <= m; ++j)
        d[1][j] += d[1][j - 1], path[1][j] = Move::R;

    for (int i = 2; i <= n; ++i)
        for (int j = 2; j <= m; ++j) {
            //      y    x      y     x
            if (d[i - 1][j] > d[i][j - 1]) {
            //   top              left
                d[i][j] += d[i - 1][j];
                path[i][j] = Move::D;
            } else {
                d[i][j] += d[i][j - 1];
                path[i][j] = Move::R;
            }
        }
    vector<Move> ans;
    int i = n, j = m;
    while (i != 1 || j != 1) {
        ans.push_back(path[i][j]);
        if (path[i][j] == Move::D) i--;
        else j--;
    }
    cout << d[n][m] << "\n";
    for (auto p = ans.rbegin(); p != ans.rend(); p++)
        cout << (*p == Move::D ? 'D' : 'R');

    return 0;
}
