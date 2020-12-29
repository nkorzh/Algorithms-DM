/* Zafar's trap */
#include <bits/stdc++.h>
using namespace std;

bool cmp(int a, int b) {
    (cout << 1 << " " << a << " " << b << "\n").flush();
    string ans;
    cin >> ans;
    return ans == "YES";
}
int n;
vector<int> row;

void magicSort(int r) {
    int l = 0, mid, nextLamp = r + 1;
    while (l < r) {
        mid = (l + r) / 2;
        if (cmp(row[mid], nextLamp)) l = mid + 1;
        else r = mid;
    }
    row.insert(row.begin() + l, nextLamp);
}

int main() {
    cin >> n;
    row.emplace_back(1);
    for (int i = 1; i < n; ++i) magicSort(i);
    cout << 0 << " ";
    for (int lamp : row)
        cout << lamp << " ";
    return 0;
}