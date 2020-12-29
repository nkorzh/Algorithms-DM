#include <bits/stdc++.h>

using namespace std;

int n, m, s;
vector<bool> used;
vector<vector<int>> gt;
vector<int> out;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    ifstream in("game.in");
//    if (!in.is_open())
//        return -1;
    while (cin >> n) {
        cin >> m;
        out.assign(n + 1, 0);
        gt.assign(n + 1, {});
        used.assign(n + 1, false);
        for (int i = 1; i <= m; ++i) {
            int from, to;
            cin >> from >> to;
            out[from]++;
            gt[to].emplace_back(from); // check for invalidation
        }
        queue<int> q;
        vector<char> res(n + 1, '0');
        vector<int> cnt(n + 1, 0);
        for (int v = 1; v <= n; ++v)
            if (out[v] == 0) {
                q.push(v);
                res[v] = '-';
            }
        int v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            used[v] = true;
            for (int from : gt[v])
                if (used[from]) continue;
                else if (res[v] == '-') {
                    if (res[from] == '0') {
                        res[from] = '+';
                        q.push(from);
                    }
                } else if (res[v] == '+') {
                    cnt[from]++;
                    if (cnt[from] == out[from]) {
                        res[from] = '-';
                        q.push(from);
                    }
                }
        }
        for (int i = 1; i <= n; ++i)
            cout << (res[i] == '+' ? "FIRST\n" : (res[i] == '-' ? "SECOND\n" : "DRAW\n"));
        cout << "\n";
    }
    return 0;
}
