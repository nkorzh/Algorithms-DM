#include <bits/stdc++.h>

using namespace std;

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

#define inf 300005
int n, killedAmount = 0;
vector<vector<int>> table;
vector<int> a;
vector<bool> killed;

int totalCheck( int day, int coupons) {
    if (coupons < 0 || coupons > day) return inf;
    if (day == 0) return 0;
    int lastPrice = a[day];

    if (coupons > 0 && table[day][coupons] != -1)
        return table[day][coupons];

    int bought = totalCheck(day - 1, coupons - (lastPrice > 100 ? 1 : 0)) + lastPrice;
    int spent = totalCheck(day - 1, coupons + 1);

    return table[day][coupons] = min(spent, bought);
}

void restoreCoupons(int day, int coupons) {
    if (day == 0 || coupons > day) return; // impossible
    int lastPrice = a[day];

    int spent = totalCheck(day - 1, coupons + 1);
    int bought = totalCheck(day - 1, coupons - (lastPrice > 100 ? 1 : 0)) + lastPrice;
    killed[day] = spent < bought;

    int prevCoupons = coupons;
    if (killed[day]) {
        killedAmount++;
        prevCoupons++;
    } else
        prevCoupons -= (lastPrice > 100 ? 1 : 0);

    restoreCoupons(day - 1, prevCoupons);
}

int main() {
//    ios::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n;
    a.resize(n + 1);
    killed.resize(n + 1, false);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    table.resize(n + 1);
    for (auto & row : table) {
        row.resize(n + 2);
        for (auto & j : row)
            j = -1;
    }

    int ans = inf, couponsLeft;
    for (int i = 0; i <= n; i++)
        if (ans >= totalCheck(n, i)) {
            ans = totalCheck(n, i);
            couponsLeft = i;
        }
    restoreCoupons(n, couponsLeft);
    cout << ans << "\n" << couponsLeft << " " << killedAmount << "\n";
    for (int i = 1; i <= n; ++i)
        if (killed[i])
            cout << i << "\n";
    
    return 0;
}