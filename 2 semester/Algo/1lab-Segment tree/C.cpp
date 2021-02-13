/* */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

typedef long long llong;

using namespace std;
#define neutral LLONG_MAX

class TLeaf {
public:
    llong el;
    llong add, set;

    TLeaf() : el(neutral), add(0), set(neutral) {}

    TLeaf &addVal(llong a) {
        this->add += a;
        return *this;
    }

    TLeaf &operator=(TLeaf &b) {
        el = b.el;
        return *this;
    }

    TLeaf &operator=(llong a) {
        el = a;
        return *this;
    }
};

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

//template <typename typev, typename typei>
//class TSum : public TOperator<typev, typei>
//{
//public:
//  TSum() {}
//  virtual typev exe(const vector<TLeaf> &a, typei left, typei right) override
//  {
//    return a[left].el + a[right].el;
//  }
//
//  virtual typev exe(const vector<typev> &a, typei left, typei right) override
//  {
//    return a[left] + a[right];
//  }
//
//  virtual typev exe(typev a, typev b) override
//  {
//    return a + b;
//  }
//
//  virtual typev exe(const TLeaf & a, const TLeaf & b) override
//  {
//    return a.el + b.el;
//  }
//};


class TTree {
private:
    TOperator<TLeaf, llong, int> *op;
public:
    size_t lsize, origsize;
    vector<TLeaf> a;

    TTree() {}

    TTree(size_t n) {
        op = new TMin<TLeaf, llong, int>();

        origsize = n;
        double lb = log2(n);

        //if (!_Is_pow_2(n))
        //  lb = (long)lb + 1;
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
        cout << endl;
      }
    }*/

    void process() {
        string s, indi, indj, strx;
        llong i, j, x;
        while (cin >> s) {
            cin >> indi >> indj;
            i = getGlobalInd(stoll(indi));
            j = stoll(indj);

            if (s == "min") {
                cout << get_rec(i, getGlobalInd(j + 1), 0, a.size() - lsize, a.size()) << "\n";
            } else {
                cin >> strx;
                x = stoll(strx);

                if (s == "set")
                    set(i, getGlobalInd(j + 1), x, 0, a.size() - lsize, a.size());
                else /* add */
                    add(i, getGlobalInd(j + 1), x, 0, a.size() - lsize, a.size());
            }
        }
    }

private:
    void set(int l, int r, llong v, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (l <= lx && rx <= r) {
            a[x].set = v; ///do 0 -> neutral by add
            a[x].el = v;
            update(x);
            return;
        }
        int m = (lx + rx) / 2;

        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);

        a[x].el = op->exe(a[2 * x + 1].el, a[2 * x + 2].el);
    }

    /* from root to leaves */
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

    void propogate(int x, int lx, int rx) {
        if (lx != rx - 1) ///if we are not in the leaf
        {
            TLeaf & left = a[2 * x + 1], & right = a[2 * x + 2];
            if (a[x].add != 0) {
                left.el += a[x].add;
                if (left.set != op->getNeutral())
                {
                    left.set += a[x].add;
                    left.add = 0;
                }
                else
                    left.add += a[x].add;
                right.el += a[x].add;
                if (right.set != op->getNeutral())
                {
                    right.set += a[x].add;
                    right.add = 0;
                }
                else
                    right.add += a[x].add;
//                a[x].add = 0; ///0 is neutral for add
            }
            if (a[x].set != op->getNeutral()) {
                left.el = a[x].set;
                left.set = a[x].set;
                left.add = 0;
                right.el = a[x].set;
                right.set = a[x].set;
                right.add = 0;
//                a[x].set = op->getNeutral(); ///inf is neutral for set
            }
        }
        a[x].add = 0;
        a[x].set = op->getNeutral();
    }

    void update(int i) {
        int x = (i - 1) / 2;
        while (x != 0) {
            a[x] = op->exe(a, 2 * x + 1, 2 * x + 2);
            x = (x - 1) / 2;
        }
        if (i > 0 && a.size() >= 3)
            a[0] = op->exe(a, 1, 2);
    }

    int getGlobalInd(int i) {
        i--;
        return a.size() - lsize + i;
    }

    llong get_rec(int l, int r, int x, int lx, int rx) {
        if (r <= lx || rx <= l)
            return op->getNeutral();
        propogate(x, lx, rx);
        if (l <= lx && rx <= r)
            return a[x].el; /* return result */
        int m = (lx + rx) / 2;

        llong sl = get_rec(l, r, 2 * x + 1, lx, m);
        llong sr = get_rec(l, r, 2 * x + 2, m, rx);

        return op->exe(sl, sr);
    }

    void Init() {
        /* fill leaves */
        string s;
        for (size_t i = a.size() - lsize; i < a.size() - lsize + origsize; i++) {
            cin >> s;
            a[i] = stoll(s);
        }

        for (size_t i = a.size() - lsize + origsize; i < a.size(); i++)
            a[i] = op->getNeutral();

        for (int i = a.size() / 2 - 1; i >= 0; i--)
            a[i] = op->exe(a, 2 * i + 1, 2 * i + 2);
    }
};

int main(/* string fin, string fout*/ ) {
//    const string fin = "test\\input5.txt";

//    ifstream ifs(fin);
//    streambuf *old_buffer_in = cin.rdbuf(ifs.rdbuf());
//    ofstream ofs(fout);                                   ///
//    streambuf *old_buffer_out = cout.rdbuf(ofs.rdbuf());  ///

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
