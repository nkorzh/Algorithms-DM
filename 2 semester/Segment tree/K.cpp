#include <iostream>
#include <vector>
#include <cmath>
#include <vector>

using namespace std;
#define Inf 600000
#define InfInv 600005

typedef long long llong;
/* solve using segment tree */


class TLeaf {
public:
    int leftFreeIndex;

    TLeaf() : leftFreeIndex(Inf) {}

    TLeaf & operator=(const int b)
    {
        this->leftFreeIndex = b;
        return *this;
    }

    void setNeutral()
    {
        this->leftFreeIndex = Inf;
    }

    void setZero()
    {
        /* means that element is not in visible range */
        this->leftFreeIndex = InfInv;
    }

    TLeaf & combine(TLeaf & left, TLeaf & right)
    {
        this->leftFreeIndex = min(left.leftFreeIndex, right.leftFreeIndex);
        return *this;
    }
};

class TTree {
    int queriesAmount, rightBorderGlobal, rightBorderTrue, leftBorder;
public:
    size_t lsize, origsize;
    vector<TLeaf> a;

//    TTree() {}

    TTree()
    {
        cin >> origsize;
        cin >> queriesAmount;
        double lb = getlog2(origsize);


        lsize = size_t(pow(2, lb));
        size_t size_all = pow(2, lb + 1) - 1;

        a.resize(size_all);
        Init();
    }

    void process() {
        const string Park = "enter";
        for (int i = 0; i < queriesAmount; ++i) {
            string action;
            int place;
            cin >> action >> place;

            if (action == Park) {
//                int truePlace = findPlaceLeft(getGlobalInd(place), rightBorderGlobal);
                int truePlace = get_rec(getGlobalInd(place), rightBorderTrue, 0, leftBorder, rightBorderGlobal);
                if (truePlace == Inf) {
//                    truePlace = findPlaceLeft(getGlobalInd(0), getGlobalInd(place));
                    truePlace = get_rec(getGlobalInd(1), getGlobalInd(place), 0, leftBorder, rightBorderGlobal);
                }
                cout << getLocalIndex(truePlace) << endl;
                update(truePlace, 1);
            } else {
                update(getGlobalInd(place), 0);
            }

        }
    }
private:
    int getLocalIndex(int i) {
        return i - leftBorder + 1;
    }

    int findPlaceLeft(int qleft, int qright) {
        if (qright - qleft == 1) {
            return qleft;
        }

        int mid = (qleft + qright) / 2;
        int place = get_rec(qleft, qright, 0, leftBorder, rightBorderGlobal);
        if (place >= qleft) {
            return place;
        } else {
            if ((place = get_rec(qleft, mid, 0, leftBorder, rightBorderGlobal)) < mid) {
                findPlaceLeft(qleft, mid);
            } else {
                findPlaceLeft(mid, qright);
            }
        }
    }

    int get_rec(int l, int r, int x, int lx, int rx)
    {
        if (r <= lx || rx <= l) {
//            res.setNeutral(); //neutral element
            return Inf;
        }
        if (l <= lx && rx <= r) {
//            res = a[x];
            return a[x].leftFreeIndex;
        }
        int m = (lx + rx) / 2;

        int sl = get_rec(l, r, 2 * x + 1, lx, m);
        int sr = get_rec(l, r, 2 * x + 2, m, rx);

        return min(sl, sr);
    }

//    void propogate(int x, int lx, int rx) {
//        if (lx < rx - 1 && a[x].c != mix) ///if we are not in the leaf
//        {
//            TLeaf &left = a[2 * x + 1], &right = a[2 * x + 2];
//
//            left.setColor(a[x].c, (rx - lx) / 2);
//            right.setColor(a[x].c, (rx - lx) / 2);
//        }
//    }

    void update(int i, int val) {
        a[i] = val == 1 ? Inf : i;

        int x = (i - 1) / 2;
        while (x != 0) {
            a[x].combine(a[2 * x + 1], a[2 * x + 2]);
            x = (x - 1) / 2;
        }
        if (i > 0 && a.size() >= 3)
            a[0].combine(a[1], a[2]);
    }

//    void update(int index, int x, int v, int left, int right) {
//        if (left == right) {
//            a[v] = x;
//            return;
//        }
//
//        int mid = (left + right) / 2;
//        if (index <= mid) {
//            update(index, x, v * 2 + 1, left, mid);
//        } else {
//            update(index, x, v * 2 + 2, mid + 1, right);
//        }
//
//        a[v].combine(a[v * 2 + 1], a[v * 2 + 2]);
//    }

    int getGlobalInd(int i) {
        i--;
        return a.size() - lsize + i;
    }

    void Init() {
        leftBorder = a.size() - lsize;
        rightBorderGlobal = a.size(); /* doesnt include border */
        rightBorderTrue = leftBorder + origsize; /* doesnt include border */

        for (int i = leftBorder; i < rightBorderTrue; ++i) {
            a[i] = i;
        }

        for (int i = rightBorderTrue; i < rightBorderGlobal; ++i) {
            a[i].setZero();
        }

        for (int i = rightBorderGlobal / 2 - 1; i >= 0; --i) {
            a[i].combine(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    int getlog2(int x) {
        double lb = log2(x);

        if (lb != (double) (int(lb))) // n is not result of exponentiation of 2 in integer degree
            return (int) lb + 1;
        return (int)lb;
    }
};

int maifn() {
//    ios_base::sync_with_stdio(false);

    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);

    TTree Tree;
    Tree.process();

    fclose(stdin);
    fclose(stdout);

    return 0;
}
