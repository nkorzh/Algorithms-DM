/* Hamiltonian cycle in a tournament */
/* 'Merge-sort' algorithm */

#include <bits/stdc++.h>
using namespace std;
#define EDGE_LESS(c) ((c) - '0')

int n;
vector<vector<bool>> g;
bool check_ham_cycle(const vector<int> & path);

inline bool is_edge(int i, int j) {
    return g[i][j];
}

vector<int> merge_paths(vector<int>::iterator left, size_t left_size, vector<int>::iterator right, size_t right_size) {
    if (right_size == 0)
        return move(vector<int>(left, left + left_size));
    if (left_size == 0)
        return move(vector<int>(right, right + right_size));

    vector<int> res;
    int first;
    if (is_edge(*left, *right)) {
        first = *left;
        res = move(merge_paths(left + 1, left_size - 1, right, right_size));
    } else {
        first = *right;
        res = move(merge_paths(left, left_size, right + 1, right_size - 1));
    }
    res.insert(res.begin(), first);
    return move(res);
}

void merge_sort(vector<int>::iterator a, size_t amount) {
    if (amount < 2) return;
    size_t mid = amount / 2;
    merge_sort(a, mid);
    merge_sort(a + mid, amount - mid);
    auto merged = merge_paths(a, mid, a + mid, amount - mid);
    for (int & node : merged) {
        *a = node;
        a++;
    }
}

int main() {
//    freopen("a.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    (cin >> n).ignore(numeric_limits<streamsize>::max(), '\n');
    g.resize(n + 1);
    for (int i = 1; i <= n; i++) g[i].resize(n + 1);

    string input;
    for (int i = 2; i <= n; ++i) {
        cin >> input;
        for (int j = 1; j < i; ++j) {
            g[i][j] = EDGE_LESS(input[j - 1]);
            g[j][i] = !EDGE_LESS(input[j - 1]);
        }
    }
    vector<int> path(n);
    for (int i = 0; i < n; ++i)
        path[i] = i + 1;
    merge_sort(path.begin(), n); // found hamiltonian path

    auto xi = path.begin();
    while (!is_edge(path.back(), path.front())) { // edge x_n -> x_1 does not exist
        auto xn = path.end() - 1;
        if (xi == path.end()) // made not to find xi again in case of first 'if' branch
            xi = path.begin();

        while (!is_edge(*xn, *xi))
            xi++;

        if (is_edge(*(xn - 1), *(xi - 1))) {
            swap(*xn, *(xi - 1));
            xi--;
        } else {
            auto xj = path.begin(), xt = xn - 1;
            while (true) {
                while (xj != xi && (!is_edge(*xt, *xj) || !is_edge(*(xi - 1), *(xt + 1))))
                    xj++;
                if (xj == xi) xt--, xj = path.begin();
                else break;
            }
            path.insert(xi, xt + 1, path.end());
            path.resize(n);
            xi = path.end();
        }
    }
//    cout << (check_ham_cycle(path) ? "OK\n" : "error\n");
    for (int p : path) cout << p << ' ';
    return 0;
}

bool check_ham_cycle(const vector<int> & path) {
    vector<bool> used(n + 1, false);
    for (auto v = path.begin(); v != path.end(); v++) {
        auto next = v + 1;
        if (v == path.end() - 1) next = path.begin();
        if (!is_edge(*v, *next)) {
            cerr << "wrong edge\n";
            return false;
        }
        if (used[*v]) {
            cerr << "met " << *v << "twice!\n";
            return false;
        }
        used[*v] = true;
    }
    for (int i = 1; i <= n; ++i)
        if (!used[i]) {
            cerr << i << " not used!\n";
            return false;
        }
    return true;
}