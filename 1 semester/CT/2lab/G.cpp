
#include <bits/stdc++.h>

using namespace std;

int n;
struct setInfo {
    int min, max, size, head;
    setInfo() = default;
    setInfo(int a) : min(a), max(a), size(1), head(a) {}
};
vector<setInfo> p;

int getHead(int a) {
    if (p[a].head != a)
        return p[a].head = getHead(p[a].head);
    return a;
}

void join(int a, int b) {
    a = getHead(a);
    b = getHead(b);
    if (a == b)
        return;
    if (p[a].size < p[b].size) swap(a, b);
    // a size is greater ot equal
    p[a].max = max(p[a].max, p[b].max);
    p[a].min = min(p[a].min, p[b].min);
    p[a].size += p[b].size;
    p[b].head = a;
}

// prints the answer
void get(int a) {
    a = getHead(a);
    cout << p[a].min << " " << p[a].max << " " << p[a].size << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> n;
    p.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        p[i] = setInfo(i);
    string command;
    int a, b;
    while (cin >> command) {
        cin >> a;
        if (command == "union") {
            cin >> b;
            join(a, b);
        } else
            get(a);
    }
    return 0;
}
