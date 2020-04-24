//
// Created by Nik on 02.03.2020.
//
/* */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

typedef long long llong;

using namespace std;
#define MAX_COORD 500000

#define mGetB(i, j) b##i##j

int rModule = 0;

class TLeaf {
public:
    int a[2][2];

    TLeaf() // Init with zeros
    {
//        this->setNeutral();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[i][j] = 0;
    }

    TLeaf & operator=(const TLeaf & b)
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[i][j] = b.a[i][j];
        return *this;
    }

    void print()
    {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                cout << a[i][j] << " ";
            cout << "\n";
        }
    cout << "\n";
    }

    void Fill( int b11, int b12, int b21, int b22 )
    {
        a[0][0] = mGetB(1, 1);
        a[0][1] = mGetB(1, 2);
        a[1][0] = mGetB(2, 1);
        a[1][1] = mGetB(2, 2);
    }

    void setNeutral()
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[i][j] = i == j ? 1 : 0;
    }

    void setZero()
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[i][j] = 0;
    }

    TLeaf & combine(TLeaf & left, TLeaf & right)
    {
        this->setZero();
        for (int j = 0; j < 2; j++)
            for (int i = 0; i < 2; i++)
                for (int k = 0; k < 2; ++k)
                    a[j][i] += (left.a[j][k] * right.a[k][i]) % rModule;
        for (int j = 0; j < 2; j++)
            for (int i = 0; i < 2; i++) {
                a[j][i] %= rModule;
            }
        return *this;
    }
};

/*
template<class TLeaf, typename typev, typename typei>
class TOperator {
public:
    TOperator() {}

    virtual typev getNeutral() = 0;

    virtual TLeaf &setNeutral(TLeaf &a) = 0;

    virtual typev exe(const vector<TLeaf> &, typei, typei) = 0;

    //virtual typev exe(const vector<typev> &, typei, typei) = 0;
    virtual typev exe(typev, typev) = 0;

    virtual typev exe(const TLeaf &, const TLeaf &) = 0;
};
*/

/*
template<class TLeaf, typename typev, typename typei>
class TMin : public TOperator<TLeaf, typev, typei> {
private:
    typev e;

public:
    TMin() {
        e = neutral;
    }

    virtual typev getNeutral() {
        return e;
    }

    virtual TLeaf &setNeutral(TLeaf &a) {
        a.el = e;
        return a;
    }

    virtual typev exe(const vector<TLeaf> &a, typei i, typei j) {
        return min(a[i].el, a[j].el);
    }

    //virtual typev exe(const vector<typev> &, typei, typei)
    virtual typev exe(typev a, typev b) {
        return min(a, b);
    }

    virtual typev exe(const TLeaf &a, const TLeaf &b) {
        return min(a.el, b.el);
    }
};
*/

class TTree {
    int m;
public:
    size_t lsize, origsize;
    vector<TLeaf> a;

//    TTree() {}

    TTree()
    {
        cin >> rModule;
        cin >> origsize;
        cin >> m;
        double lb = log2(origsize);

        if (lb != (float) (long(lb))) // n is not result of exponentiation of 2 in integer degree
            lb = (long) lb + 1;

        lsize = size_t(pow(2, lb));
        size_t size_all = pow(2, lb + 1) - 1;

        a.resize(size_all);
        Init();
    }

    /*void print()
    {
      size_t cur = size, gone = 0;
      while (size != 0)
      {
        for (size_t i = a.size() - size - gone; i < a.size() - gone; i++)
        {
          cout << a[i].el;
          for (int j = 0; j < size; j++)
            cout << " ";
        }
        cout << "\n";
      }
    }*/

    void process() {
        string s, indi, indj, strx;
        llong i, j, x;
        for (int k = 0; k < m; ++k) {
            cin >> indi >> indj;
            i = getGlobalInd(stoll(indi));
            j = getGlobalInd(stoll(indj) + 1);
            TLeaf res;
            get_rec(res, i, j, 0, a.size() - lsize, a.size());
            cin.clear();
            res.print();
            cout.clear();
        }
    }

private:
    void get_rec(TLeaf & res, int l, int r, int x, int lx, int rx)
    {
        if (r <= lx || rx <= l) {
            res.setNeutral(); //neutral element
            return;
        }
        if (l <= lx && rx <= r) {
            res = a[x];
            return;
        }
        int m = (lx + rx) / 2;

        TLeaf sl, sr;
        sl.setNeutral();
        sr.setNeutral();
        get_rec(sl, l, r, 2 * x + 1, lx, m);
        get_rec(sr, l, r, 2 * x + 2, m, rx);

        res.combine(sl, sr);
    }

    void propogate(int x, int lx, int rx) {
        // TODO propogate
//        if (lx < rx - 1 && a[x].c != mix) ///if we are not in the leaf
//        {
//            TLeaf &left = a[2 * x + 1], &right = a[2 * x + 2];
//
//            left.setColor(a[x].c, (rx - lx) / 2);
//            right.setColor(a[x].c, (rx - lx) / 2);
//        }
    }

    void update(int i) {
        int x = (i - 1) / 2;
        while (x != 0) {
            a[x].combine(a[2 * x + 1], a[2 * x + 2]);
            x = (x - 1) / 2;
        }
        if (i > 0 && a.size() >= 3)
            a[0].combine(a[1], a[2]);
    }

    int getGlobalInd(int i) {
        i--;
        return a.size() - lsize + i;
    }

    void Init() {
        /* fill leaves */
        int a11, a12, a21, a22;
        for (size_t i = a.size() - lsize; i < a.size() - lsize + origsize; i++) {
            cin >> a11 >> a12 >> a21 >> a22;
            a[i].Fill(a11, a12, a21, a22);
        }

        for (size_t i = a.size() - lsize + origsize; i < a.size(); i++)
            a[i].setNeutral();

        for (int i = a.size() / 2 - 1; i >= 0; i--)
            a[i].combine(a[2 * i + 1], a[2 * i + 2]);
    }
};

int main() {
//    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

//    int n;
//    cin >> n;

    TTree Tree;

    Tree.process();


    fclose(stdin);
    fclose(stdout);
//    ifs.close();
//    cin.rdbuf(old_buffer_in);
//    ofs.close();                                       ///
//    cout.rdbuf(old_buffer_out);                        ///
//    system("pause");                                   ///
    return 0;
}

