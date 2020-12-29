/* Wales Powell algorithm */
/* doesnt work on crown graphs since the order of v-s with same degrees is undefined */
#include <bits/stdc++.h>
using namespace std;

#define pair pair<int, int>

int n, m; /* 3 <= n <= 9999; 2 <= m <= 100 000 */
int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n >> m;
    vector<set<int>> g(n + 1);

    vector<pair> degs(n + 1, {-1, 0});
    degs[0] = {0, std::numeric_limits<int>::max()};
    for (int i = 1; i < degs.size(); ++i)
        degs[i].first = i;

    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        g[a].emplace(b);
        g[b].emplace(a);
        degs[a].second++;
        degs[b].second++;
    }
    sort(degs.rbegin(), degs.rend(), [](const pair & a, const pair & b) { return a.second < b.second; });

    list<int> L;
    cout << (degs[1].second | 1) << "\n"; // sorted degs, taking odd number
    for (int i = 1; i < degs.size(); i++)                                           
        L.push_back(degs[i].first);
    int p = 0;
    vector<vector<int>> col(1);
    while (!L.empty()) {
        p++;
        degs[L.front()].first = p;
        col.push_back({L.front()}); L.pop_front();
        for (auto v = L.begin(); v != L.end(); ) {
            bool can_paint = true;
            for (auto u : col[p])
                if (g[u].find(*v) != g[u].end()) {// if there is edge (v, u), where u is colored vertex
                    can_paint = false;
                    break; // therefore we cant paint v in color p, skip it
                }
            if (can_paint) {
                col[p].emplace_back(*v);
                degs[*v].first = p;
                auto it = v++;
                L.erase(it);
            } else
                v++;
        }
    }
    if (p != (degs[1].second | 1)) cout << "wrong color amount! p = " << p << "\n";
    for (int i = 1; i <= n; ++i) cout << degs[i].first << "\n";
    return 0;
}
