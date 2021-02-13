
#include <bits/stdc++.h>

using namespace std;
typedef long long ull;

int n;
struct setInfo {
    int size, head;
    ull add;
    setInfo() = default;
    setInfo(int a) : add(0), size(1), head(a) {}
};
vector<setInfo> p;

int getHead(int a) {
    if (p[a].head != a)
        return getHead(p[a].head);
    return a;
}

void join(int a, int b) {
    a = getHead(a);
    b = getHead(b);
    if (a == b)
        return;
    if (p[a].size < p[b].size) swap(a, b);
    // a size is greater ot equal
    p[a].size += p[b].size;
    p[b].head = a;
    p[b].add -= p[a].add;
}

// prints the answer
void get(int a) {
    ull res = 0;
    res += p[a].add;
    while (p[a].head != a) {
        a = p[a].head;
        res += p[a].add;
    }
    cout << res << "\n";
}

void add(int c, ull v) {
    p[getHead(c)].add += v;
}

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    int requests;
    cin >> n >> requests;
    p.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        p[i] = setInfo(i);
    string command;
    int a;
    ull b;
    for (int i = 0; i < requests; ++i) {
        cin >> command;
        cin >> a;
        if (command == "join") {
            cin >> b;
            join(a, b);
        } else if (command == "get")
            get(a);
        else {
            cin >> b;
            add(a, b);
        }
    }
    return 0;
}
