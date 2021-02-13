#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n; // <= 2 000
vector<ll> a; // sequence
vector<int> pathLen,
            pred; // predecessor

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n;
    a.resize(n + 1);
    pathLen.resize(n + 1, 1);
    pred.resize(n + 1, -1);

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (a[i] > a[j] && pathLen[j] + 1 > pathLen[i]) {
                pred[i] = j;
                pathLen[i] = pathLen[j] + 1;
            }
    // search subsequence with max length
    int maxLen = -1, end;
    for (int i = 0; i < n; ++i)
        if (pathLen[i] > maxLen) {
            maxLen = pathLen[i];
            end = i;
        }
    vector<int> seqId;
    while (end != -1) {
        seqId.push_back(a[end]);
        end = pred[end];
    }
    cout << seqId.size() << "\n";
    for (auto p = seqId.rbegin(); p != seqId.rend(); p++)
        cout << *p << " ";

    return 0;
}
