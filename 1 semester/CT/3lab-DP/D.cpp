#include <bits/stdc++.h>

using namespace std;
#define ll unsigned long long
#define NUMBERS 10
#define MOD 1000000000

int n; // <= 100
vector<vector<int>> nextButton = {
        {4, 6},
        {6, 8}, {7, 9}, {4, 8},
        {3, 9, 0}, {}, {0, 1, 7},
        {2, 6}, {1, 3}, {2, 4}
};
vector<vector<ll>> d; // d[num][step] = ways to get here for 'step' steps


int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n;
    d.resize(NUMBERS);
    for (int i = 0; i < NUMBERS; ++i) {
        d[i].resize(n + 1, 0);
        switch (i) {
            case 8: [[fallthrough]];
            case 0:
                d[i][1] = 0;
                break;
            default:
                d[i][1] = 1;
        }
    }

    for (int i = 1; i < n; ++i)
        for (int num = 0; num < NUMBERS; ++num)
            for (int next : nextButton[num]) {
                d[next][i + 1] += d[num][i] % MOD;
                d[next][i + 1] %= MOD;
            }

    ll ans = 0;
    for (int num = 0; num < NUMBERS; ++num)
        ans = (ans + d[num][n]) % MOD;

    cout << ans;

    return 0;
}
