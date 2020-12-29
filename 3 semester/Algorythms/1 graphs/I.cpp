#include <bits/stdc++.h>

using namespace std;

const int MAX = 10000;

int x[MAX];
int y[MAX];

int dist(int i, int j) {
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

double prim(int n) {
    vector<bool> used(n, false);
    vector<int> d(n, INT_MAX);
    d[0] = 0;
    double ans = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (u == -1 || d[u] > d[j]))
                u = j;
        used[u] = true;
        ans += sqrt(d[u]);
        for (int j = 0; j < n; j++)
            if (d[j] > dist(u, j)) d[j] = dist(u, j);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    cout << prim(n);
}
