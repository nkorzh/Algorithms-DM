#include <bits/stdc++.h>
using namespace std;

#define IS_EDGE(c) ((c) - '0')
int n;
vector<vector<int>> g;
deque<int> v;

int index_next(bool first_only = true) {
    int i = 2;
    int first = v[0], sec = v[1];
    while (i < n - first_only && (!g[first][v[i]] || (first_only && !g[sec][v[i + 1]])))
        i++;
    if (i < n - 1)
        return i;
    return index_next(false);
}

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n;
    g.resize(n + 1);
    string input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    g[1].resize(n + 1, 0);
    v.push_back(1);

    for (int i = 2; i <= n; ++i) {
        v.push_back(i);
        g[i].resize(n + 1, false);
        cin >> input;
        for (int j = 1; j < i; ++j)
            if (IS_EDGE(input[j - 1])) g[j][i] = g[i][j] = 1;
    }
    int n2 = n * (n - 1);
    int first, sec;
    for (int k = 0; k < n2; ++k) {
        first = v[0]; sec = v[1];
        if (!g[first][sec])
            reverse(v.begin() + 1, v.begin() + index_next() + 1);
        v.push_back(first);
        v.pop_front();
    }
    for (auto i : v) cout << i << " ";
    return 0;
}
