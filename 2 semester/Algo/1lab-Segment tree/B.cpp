/* */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

typedef long long llong;

using namespace std;

class TGroup
{
public:
  long el;

  TGroup() : el(0) {}

  TGroup & set(int a, int i, int j = -1)
  {
    el = a;
    return *this;
  }
  TGroup & operator=(TGroup &b)
  {
    el = b.el;
    return *this;
  }

  TGroup & operator=(int a)
  {
    el = a;
    return *this;
  }
};

template <typename typev, typename typei>
class TOperator
{
public:
  TOperator() {}
  virtual typev exe(const vector<TGroup> &, typei, typei) = 0;
  virtual typev exe(const vector<typev> &, typei, typei) = 0;
  virtual typev exe(typev, typev) = 0;
  virtual typev exe(const TGroup &, const TGroup &) = 0;
};

template <typename typev, typename typei>
class TSum : public TOperator<typev, typei>
{
public:
  TSum() {}
  virtual typev exe(const vector<TGroup> &a, typei left, typei right) override
  {
    return a[left].el + a[right].el;
  }

  virtual typev exe(const vector<typev> &a, typei left, typei right) override
  {
    return a[left] + a[right];
  }

  virtual typev exe(typev a, typev b) override
  {
    return a + b;
  }

  virtual typev exe(const TGroup & a, const TGroup & b) override
  {
    return a.el + b.el;
  }
};


class TTree
{
private:
  TOperator<llong, int> *op;
public:
  size_t lsize, origsize;
  vector<llong> a;

  TTree() {}
  TTree( size_t n )
  {
    op = new TSum<llong, int>;

    origsize = n;
    double lb = log2(n);

    if (lb != (float)(long(lb))) // n is not result of exponentiation of 2 in integer degree
      lb = (long)lb + 1;

    lsize = pow(2, lb);
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

  void process()
  {
    string s, indi, indj;
    llong i, j;
    while (cin >> s)
    {
      cin >> indi >> indj;
      i = getGlobalInd(stoll(indi));
      j = stoll(indj);

      if (s == "sum")
      {
        cout << get_rec(i, getGlobalInd(j + 1), 0, a.size() - lsize, a.size()) << "\n";
      }
      else
      {
        if (0 <= i && i < a.size())
        {
          a[i] = j;
          update(i);
        /* if (*debug*)
         *   print();
         */
        }
      }
    }
  }

private:
  void update(int i)
  {
    i = (i - 1) / 2;
    while (i != 0)
    {
      a[i] = op->exe(a, 2 * i + 1, 2 * i + 2);
      i = (i - 1) / 2;
    }
    if (a.size() >= 3)
      a[0] = op->exe(a, 1, 2);
  }

  int getGlobalInd(int i)
  {
    i--;
    return a.size() - lsize + i;
  }

  llong get_rec(int l, int r, int x, int lx, int rx)
  {
    if (r <= lx || rx <= l)
      return 0; //neutral element
    if (l <= lx && rx <= r)
      return a[x];
    int m = (lx + rx) / 2;
  
    llong sl = get_rec(l, r, 2 * x + 1, lx, m);
    llong sr = get_rec(l, r, 2 * x + 2, m, rx);
  
    return op->exe(sl, sr);
  }

  void Init()
  {
    /* fill leaves */
    string s;
    for (int i = a.size() - lsize; i < a.size() - lsize + origsize; i++)
    {
      cin >> s;
      a[i] = stoll(s);
    }

    for (int i = a.size() - lsize + origsize; i < a.size(); i++)
      a[i] = 0;

    for (int i = a.size() / 2 - 1; i >= 0; i--)
      a[i] = op->exe(a, 2 * i + 1, 2 * i + 2);
  }
};

int main()
{
  int n = 3;
  cin >> n;

  TTree Tree(n);

  Tree.process();
  //system("pause");
}
