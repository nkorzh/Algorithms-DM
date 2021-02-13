#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define INF 100000000

int n, k; // <= 10 000
vector<int> cost;
vector<ll> d;
vector<int> path;

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n >> k;
    cost.resize(n + 1);
    d.resize(n + 1);
    path.resize(n + 1, -1);

    for (int i = 2; i < n; ++i)
        cin >> cost[i];
    for (int i = 0; i <= n; ++i)
        d[i] = -INF;

    path[n] = n, path[1] = 1;
    d[1] = cost[0] = cost[1] = cost[n] = 0;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; i - j >= 1 && j <= k; ++j)
            if (d[i] < d[i - j]) {
                d[i] = d[i - j];
                path[i] = i - j;
            }
        d[i] += cost[i];
    }
    vector<int> ans;
    ans.push_back(n);
    int i = n;
    while (i != 1) {
        ans.push_back(path[i]);
        i = path[i];
    }
    cout << d[n] << " " << ans.size() - 1 << "\n";
    for (auto p = ans.rbegin(); p != ans.rend(); p++)
        cout << *p << " ";
    return 0;
}
