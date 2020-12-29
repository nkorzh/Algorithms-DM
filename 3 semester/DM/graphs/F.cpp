/* Prufer code */
#include <bits/stdc++.h>
using namespace std;

#define pair pair<int, int>
int n;
vector<int> deg, prufer;
vector<pair> result;

void treePrufer() {
    int ptr = 1;
    while (ptr <= n && deg[ptr] != 1)
        ++ptr;
    int leaf = ptr;
    for (int pcode : prufer) {
        result.emplace_back(leaf, pcode);
        if (--deg[pcode] == 1 && pcode < ptr)
            leaf = pcode;
        else {
            ptr++;
            while (ptr <= n && deg[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    result.emplace_back(leaf, n);
}

int main() {
//    freopen("a.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> n;
    deg.resize(n + 1, 1);
    for (int i = 0, code; i < n - 2; ++i) {
        cin >> code;
        prufer.push_back(code);
        deg[code]++;
    }
    treePrufer();
    for (auto & p : result) cout << p.first << " " << p.second << "\n";
    return 0;
}