#include <bits/stdc++.h>

using namespace std;
int n;
vector<vector<int>> d;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    d.resize(n + 1);
    int input;
    for (int i = 1; i <= n; ++i) {
        d[i].resize(n + 1);
        for (int j = 1; j <= n; ++j) {
            cin >> input;
            d[i][j] = input;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                if (u != v) d[u][v] = min(d[u][v], d[u][i] + d[i][v]);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            cout << d[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
