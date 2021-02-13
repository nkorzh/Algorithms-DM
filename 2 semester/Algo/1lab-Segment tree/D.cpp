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

enum color
{
    black, white, mix
};

class TLeaf {
public:
    color c, leftc, rightc;
    llong sum;
    int amount;

    TLeaf() : sum(0), amount(0), c(white), leftc(white), rightc(white) {}

    void setColor(color c, int size)
    {
        this->c = leftc = rightc = c;
        if (c == white)
            sum = amount = 0;
        else
        {
            sum = size;
            amount = 1;
        }
    }

    void combine(TLeaf & left, TLeaf & right)
    {
        sum = left.sum + right.sum;
        amount = left.amount + right.amount;
        if (left.c == right.c && left.c != mix)
            leftc = rightc = c = left.c;
        else
        {
            c = mix;
            leftc = left.leftc;
            rightc = right.rightc;
        }

        if (left.rightc == right.leftc && left.rightc == black)
            amount--;
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
private:
//    TOperator<TLeaf, llong, int> *op;
public:
    size_t lsize, origsize;
    vector<TLeaf> a;

    TTree() {}

    TTree(size_t n) {
//        op = new TMin<TLeaf, llong, int>();
        n = origsize = 500001 * 2/*pow(2, 20)*/;
        double lb = log2(n);

        if (lb != (float) (long(lb))) // n is not result of exponentiation of 2 in integer degree
            lb = (long) lb + 1;

        lsize = size_t(pow(2, lb));
        size_t size_all = pow(2, lb + 1) - 1;

        a.resize(size_all);
//        Init();
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
        cout << endl;
      }
    }*/

    void process() {
        string s, indi, indj, strx;
        llong i, j, x;
        while (cin >> s) {
            cin >> indi >> indj;
            i = stoll(indi);
            j = getGlobalInd(stoll(indj) + i);

            i = getGlobalInd(i);

            paint(i, j, s == "W" ? color::white : color::black, 0,
                    a.size() - lsize, a.size());
            cout << a[0].amount << " " << a[0].sum << endl;
        }
    }

private:
    void paint(int l, int r, color c, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (l <= lx && rx <= r) {
            a[x].setColor(c, rx - lx);
            update(x);
            return;
        }
        int m = (lx + rx) / 2;

        paint(l, r, c, 2 * x + 1, lx, m);
        paint(l, r, c, 2 * x + 2, m, rx);
    }

/*
    void add(int l, int r, llong v, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (l <= lx && rx <= r) {
            a[x].add += v; // current add is already 0
            a[x].el += v;
            update(x);
            return;
        }
        int m = (lx + rx) / 2;

        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);

        a[x].el = op->exe(a[2 * x + 1].el, a[2 * x + 2].el);
    }
*/

    void propogate(int x, int lx, int rx) {
        if (lx < rx - 1 && a[x].c != mix) ///if we are not in the leaf
        {
            TLeaf &left = a[2 * x + 1], &right = a[2 * x + 2];

            left.setColor(a[x].c, (rx - lx) / 2);
            right.setColor(a[x].c, (rx - lx) / 2);
        }
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
        return a.size() - lsize / 2 + i;
    }

    void Init() {
        /* fill leaves */
//        string s;
//        for (size_t i = a.size() - lsize; i < a.size() - lsize + origsize; i++) {
//            cin >> s;
//            a[i] = stoll(s);
//        }

//        for (size_t i = a.size() - lsize + origsize; i < a.size(); i++)
//            a[i] = op->getNeutral();
//
//        for (int i = a.size() / 2 - 1; i >= 0; i--)
//            a[i] = op->exe(a, 2 * i + 1, 2 * i + 2);
    }
};

int main(/* string fin, string fout*/ ) {

    int n;
    cin >> n;

    TTree Tree(n);

    Tree.process();

//    ifs.close();
//    cin.rdbuf(old_buffer_in);
//    ofs.close();                                       ///
//    cout.rdbuf(old_buffer_out);                        ///
//    system("pause");                                   ///
    return 0;
}

