#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

vector<int> pref;

void prefix_function (string & s) {
    size_t slen = s.length();
    pref.resize(slen);
    pref[0] = 0;
    for (int i = 1; i < slen; ++i) {
        int j = pref[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pref[j - 1];
        if (s[i] == s[j]) j++;
        pref[i] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
//    freopen("a.in", "r", stdin);
    string s;
    cin >> s;

    prefix_function(s);
    int k = (int)s.length() - pref[s.length() - 1]; // s.length() <= 10^6 <= INT_MAX = 2^31 - 1
    if (s.length() % k == 0) cout << k;
    else cout << s.length();
    return 0;
}
