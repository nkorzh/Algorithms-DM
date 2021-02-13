// Levenshtein distance
// capital latin letters only
 #include <bits/stdc++.h>

using namespace std;
#define ll unsigned long long
#define NUMBERS 10
#define INF 1000000000


vector<vector<int>> d;

/*  a a a a a a 
 * b
 * b
 * b
 * b
 */

template<typename type>
type minMultiple(type a, type b...) {
    va_list args;
    type m, val;

    if (a < b) m = a;
    else m = b;

    va_start(args, b);
    val = va_arg(args, type);
    if (val < m)
        m = val;
    va_end(args);

    return m;
}

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    string a, // j
           b; // i
    int insertCost = 1, deleteCost = 1, replaceCost = 1;
    cin >> a >> b;
    size_t n = a.size(), m = b.size();
    d.resize(n + 1);

    for (auto & i : d)
        i.resize(m + 1, INF);

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0) {
                d[i][j] = i + j;
                continue;
            }

            if (a[i - 1] == b[j - 1])
                d[i][j] = d[i - 1][j - 1];
            else
                d[i][j] = minMultiple(d[i - 1][j] + insertCost,
                                      d[i][j - 1] + deleteCost,
                                         d[i - 1][j - 1] + replaceCost);
        }
    cout << d[n][m];

    return 0;
}
