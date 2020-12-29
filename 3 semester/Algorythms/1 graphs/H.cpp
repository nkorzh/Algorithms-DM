#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <fstream>

using namespace std;

#define SIZE 1000

struct vertex{
    int used, color;
    int g[SIZE], gt[SIZE];
};

stack<int> lst;
vector <vertex> v;
int n, weight, a;
int l, r = -1;

void dfs(int id) {
    v[id].used = 1;
    for (int i = 0; i < n; i++)
        if (i != id && !v[i].used && v[id].g[i] <= weight)
            dfs(i);

    lst.push(id);
}

void dfsr(int id, int color){
    v[id].used = 2;
    v[id].color = color;
    for (int i = 0; i < n; i++)
        if (i != id && v[i].used != 2 && v[id].gt[i] <= weight)
            dfsr(i, color);
}

bool strongly_connected_count() {
    int color = 0;
    for (int i = 0; i < n; i++) v[i].used = 0;

    for (int i = 0; i < n; i++)
        if (!v[i].used) dfs(i);

    while (!lst.empty()) {
        if (v[lst.top()].used != 2)
            dfsr(lst.top(), color++);
        lst.pop();
    }
    return color == 1;
}


int main() {
    ios::sync_with_stdio(false);
    ifstream in("avia.in");
    ofstream out("avia.out");

    in >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            in >> a;
            v[i].g[j] = a;
            v[j].gt[i] = a;
            r = max(r, a);
        }

    while (l < r) {
        static bool res;
        weight = (l + r) / 2;
        res = strongly_connected_count();
        if (res) r = weight;
        else l = weight + 1;
    }

    out << r;
}
