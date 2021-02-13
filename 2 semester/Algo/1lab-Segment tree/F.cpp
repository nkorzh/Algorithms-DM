//
// Created by Nik on 10.03.2020.
//
#include <iostream>
#include <vector>
#include <cmath>

#define modulo 16714589
#define inc_c 21563
#define maxSize 131072
//#define maxSize 10000
#define maxDepth 18
//#define maxDepth 18
#define callCalcFunc(_x, _y) _x <= _y ? calc(_x, _y) : calc(_y, _x)

using namespace std;

class TTable
{
private:
    int n, realSize, powOf2, queriesAmount;
    int a[maxSize][maxDepth];
    int logs[maxSize];
public:
    TTable() {}

    int getlog2(int x) {
        double lb = log2(x);

        if (lb != (double) (int(lb))) // n is not result of exponentiation of 2 in integer degree
            return (int) lb + 1;
        return (int)lb;
    }

    int getMaxInPow2(int x) {
        return int(log2(x));
    }

    void Init() {
        cin >> n >> queriesAmount;

        powOf2 = getlog2(n);
        realSize = pow(2, powOf2);

        vector<int> tmp(realSize);
        cin >> tmp[0];

        logs[0] = 0;
        for (int i = 1; i < n; ++i) {
            tmp[i] = (tmp[i - 1] * 23 + inc_c) % modulo;
            logs[i] = log2(i);
        }

        for (int i = n; i < tmp.size(); ++i) {
            tmp[i] = modulo + 100;
        }

        for (int j = 0; j < maxSize; ++j) {
            for (int i = 0; i < maxDepth; ++i) {
                a[j][i] = modulo + 100;
            }
        }

        for (int i = 0; i < realSize; ++i)
            a[i][0] = tmp[i];

        for (int k = 1, lastPow2 = 1; k <= powOf2; ++k, lastPow2 *= 2) {
            for (int i = 0; i <= realSize - lastPow2; ++i) {
                a[i][k] = min(a[i][k - 1], a[i + lastPow2][k - 1]);
            }
        }
    }

    void Process() {
        int u, v, response;
        cin >> u >> v;

        response = callCalcFunc(u - 1, v - 1);

        for (int i = 1; i < queriesAmount; ++i) {
            u = ((17 * u + 751 + response + 2 * (i)) % n) + 1;
            v = ((13 * v + 593 + response + 5 * (i)) % n) + 1;
            response = callCalcFunc(u - 1, v - 1);
        }
        cout << u << " " << v << " " << response << "\n";
    }

private:
    // borders included, guarantied l <= r
    int calc(int l, int r) {
        if (l == r)
            return a[l][0];
        int k = logs[r - l + 1], twoInK = 1 << k;
        return min(a[l][k], a[r - twoInK + 1][k]);
    }
};

//int main() {
//    ios_base::sync_with_stdio(false);
//    TTable Table;
//
//    Table.Init();
//    Table.Process();
//    return 0;
//}
//