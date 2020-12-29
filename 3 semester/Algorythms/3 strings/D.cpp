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
    string s, bigStr;
    cin >> bigStr >> s;
    size_t patternLen = bigStr.length();
    bigStr.append("$").append(s);

    prefix_function(bigStr);
    vector<int> entries;
    for (size_t i = patternLen + 1; i < bigStr.length(); ++i)
        if (pref[i] == patternLen)
            entries.push_back(i - patternLen * 2 + 1);
    cout << entries.size() << "\n";
    for (int entry : entries) cout << entry << ' ';
    return 0;
}
