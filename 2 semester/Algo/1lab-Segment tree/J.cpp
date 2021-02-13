#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;
#define Inf 10000002

typedef long long llong;
/* solve using segment tree */
#define mnt llong

#define wallPiece pair<mnt, mnt>

class TLeaf {
public:
    mnt height, index;
    mnt upgrade;

    TLeaf() : height(0), index(-1), upgrade(-1) {}

    TLeaf & operator=(const mnt b)
    {
        this->height = b;
        return *this;
    }

    void defend(TLeaf & left, TLeaf & right) {
        /* if existed cell height < upgrade, than it`s height will be updated
         * else no cell will be updated and index of cell with least height shouldn`t be recalculated */
        if (height < upgrade) {
            height = upgrade;
        }
        left.upgrade = right.upgrade = upgrade;
        if (left.height < upgrade) {
            left.height = upgrade;
        }
        if (right.height < upgrade) {
            right.height = upgrade;
        }
        upgrade = -1;
    }

    void setNeutral(mnt x = -1) /* init */
    {
        height = 0;
        index = x;
        upgrade = -1;
    }

    void setZero()
    {
        /* means that element is not in visible range */
        height = Inf;
    }

    TLeaf & combine(TLeaf & left, TLeaf & right)
    {
        if (left.height < right.height) {
            height = left.height;
            index = left.index;
        } else {
            height = right.height;
            index = right.index;
        }
        return *this;
    }
};

class TTree {
    mnt queriesAmount, rightBorderGlobal, rightBorderTrue, leftBorder;
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
        const string Defend = "defend";
        for (mnt i = 0; i < queriesAmount; ++i) {
            string action;
            mnt start, end;
            cin >> action >> start >> end;

            if (action == Defend) {
                mnt newHeight;
                cin >> newHeight;
                buildUp(getGlobalInd(start), getGlobalInd(end + 1), newHeight, 0, leftBorder, rightBorderGlobal);
            } else {
                wallPiece lowestPiece = get_rec(getGlobalInd(start), getGlobalInd(end + 1), 0, leftBorder, rightBorderGlobal);
                cout << lowestPiece.first << " " << getLocalIndex(lowestPiece.second) << "\n";
            }

        }
    }
private:
    mnt getLocalIndex(mnt i) {
        return i - leftBorder + 1;
    }

    void buildUp(mnt l, mnt r, mnt val, mnt x, mnt lx, mnt rx) {
        propogate(x, lx, rx);
        if (r <= lx || rx <= l) {
            return;
        }
        if (l <= lx && rx <= r) { // we`re inside
            if (val >= a[x].height) {
                a[x].height = a[x].upgrade = val;
                update(x);
            }
            return;
        }
        mnt m = (lx + rx) / 2;

        buildUp(l, r, val, 2 * x + 1, lx, m);
        buildUp(l, r, val, 2 * x + 2, m, rx);
    }

    /* returns pair<height, index> of cell with least height */
    pair<mnt, mnt> get_rec(mnt l, mnt r, mnt x, mnt lx, mnt rx) {
        propogate(x, lx, rx);
        if (r <= lx || rx <= l) {
            return make_pair(Inf, -1);
        }
        if (l <= lx && rx <= r && l <= a[x].index && a[x].index < r) {
            return make_pair(a[x].height, a[x].index);
        }
        mnt m = (lx + rx) / 2;

        wallPiece sl = get_rec(l, r, 2 * x + 1, lx, m);
        wallPiece sr = get_rec(l, r, 2 * x + 2, m, rx);

        if (l <= sl.second && sl.second < r && sl.first <= sr.first)
            return sl;
        else if (l <= sr.second && sr.second < r && sr.first <= sl.first)
            return sr;

//        return (sl.first < sr.first ? sl : sr);
    }

    void propogate(mnt x, mnt lx, mnt rx) {
        if (rx - lx > 1) ///if we are not in the leaf
        {
            if (a[x].upgrade != -1)
                a[x].defend(a[2 * x + 1], a[2 * x + 2]);
        }
    }

    void update(mnt i) {
        mnt x = (i - 1) / 2;
        while (x != 0) {
            a[x].combine(a[2 * x + 1], a[2 * x + 2]);
            x = (x - 1) / 2;
        }
        if (i > 0 && a.size() >= 3)
            a[0].combine(a[1], a[2]);
    }

    mnt getGlobalInd(mnt i) {
        i--;
        return a.size() - lsize + i;
    }

    void Init() {
        leftBorder = a.size() - lsize;
        rightBorderGlobal = a.size(); /* doesnt include border */
        rightBorderTrue = leftBorder + origsize; /* doesnt include border */

        for (mnt i = leftBorder; i < rightBorderTrue; ++i) {
            a[i].setNeutral(i);
        }

        for (mnt i = rightBorderTrue; i < rightBorderGlobal; ++i) {
            a[i].setZero();
        }

        for (mnt i = rightBorderGlobal / 2 - 1; i >= 0; --i) {
            a[i].combine(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    mnt getlog2(mnt x) {
        double lb = log2(x);

        if (lb != (double) (mnt(lb))) // n is not result of exponentiation of 2 in mnteger degree
            return (mnt) lb + 1;
        return (mnt)lb;
    }
};

int mtain()
{
        ios_base::sync_with_stdio(false);
//    freopen("test\\input0.txt", "r", stdin);
//    freopen("test\\out0.txt", "w", stdout);

    TTree Wall;
    Wall.process();

//    fclose(stdin);
//    fclose(stdout);

    return 0;
}
