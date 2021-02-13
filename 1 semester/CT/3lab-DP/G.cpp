 #include <bits/stdc++.h>

using namespace std;

vector<vector<int>> d;
vector<vector<int>> charToDivide;

string a;
size_t brTypes = 3;
char brOpen[] = {'(', '[', '{'};
char brClose[] = {')', ']', '}'};
string result = "";

void makeRightSequence(int l, int r) {
    if (d[l][r] == r - l + 1) // length
        return;
    if (d[l][r] == 0) {// right sequence
        result.append(a.substr(l, r - l + 1)); // substr takes start and length
        return;
    }
    if (charToDivide[l][r] == -1) {
        result.append(a.begin() + l, a.begin() + l + 1); // append char at 'l'
        makeRightSequence(l + 1, r - 1);
        result.append(a.begin() + r, a.begin() + r + 1); // append char at 'l'
    } else {
        makeRightSequence(l, charToDivide[l][r]); // skipping thar char
        makeRightSequence(charToDivide[l][r] + 1, r);
    }
}

int main() {
//    ios_base::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    cin >> a;
    int n = a.size();
    d.resize(n + 1);
    charToDivide.resize(n + 1);

    for (int i = 0; i < n; ++i) {
        d[i].resize(n + 1, n);
        charToDivide[i].resize(n + 1, -1);
    }
    for (int i = 0; i < n; ++i)
        d[i][i] = 1;

    for (int r = 1; r < n; ++r) {
        for (int left = r - 1; left >= 0; --left) {
            int minCharsToDelete = n;

            for (int i = 0; i < brTypes; ++i)
                if (a[left] == brOpen[i] && a[r] == brClose[i]) {
                    if (r == left + 1)
                        minCharsToDelete = 0;
                    minCharsToDelete = min(minCharsToDelete, d[left + 1][r - 1]);
                }

            // concatenation of two right br sequences
            for (int k = left; k < r; ++k)
                if (minCharsToDelete > d[left][k] + d[k + 1][r]) {
                    minCharsToDelete = d[left][k] + d[k + 1][r];
                    charToDivide[left][r] = k;
                }
            d[left][r] = minCharsToDelete;
        }
    }
    if (!a.empty())
        makeRightSequence(0, n - 1);
    cout << result;
    return 0;
}
