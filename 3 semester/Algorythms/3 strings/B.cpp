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
    for (int val : pref) cout << val << ' ';
    return 0;
}
