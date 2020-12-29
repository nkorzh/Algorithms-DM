#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

vector<int> z;

void z_function (string & s) {
    size_t slen = s.length();
    z.resize(slen);
    z[0] = slen;
    int left = 0, right = 0;
    for (int i = 1; i < slen; ++i) {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < slen && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);   
    string s;
    cin >> s;

    z_function(s);
    for (int i = 1; i < z.size(); ++i) cout << z[i] << ' ';
    return 0;
}
