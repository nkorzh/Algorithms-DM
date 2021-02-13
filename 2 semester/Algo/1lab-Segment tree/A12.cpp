/* */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef long long mint;
//#define mint long

const mint num2 = 1073741823;
const mint num = 65535;
using namespace std;

class TSum
{
  vector<mint> a;
public:
  TSum() {}
  TSum(mint  n, mint x, mint t, mint a0)
  {
    a.resize(n);
    /* no delayed init */
    if (n >= 1)
      a[0] = a0;

    Init(x, t);
  }

  mint getSum(mint l, mint r)
  {
    if (l < 0 || r < 0)
      return 0;
    if (l > r)
      swap(l, r);
    if (l == 0)
      return a[r];
    return a[r] - a[l - 1];
  }

private:
  void Init(mint x, mint y)
  {
    for (mint i = 1; i < a.size(); i++)
    {
      a[i] = (x * a[i - 1] + y) & (num);
    }
    for (mint i = 1; i < a.size(); i++)
      a[i] += a[i - 1];
  }
};

int main()
{
  mint n = 3, x = 1, y = 2, a0 = 3, m = 3, z = 1, b0 = 4;
  mint t = -1;

  cin >> n >> x >> y >> a0 >> m >> z >> t >> b0;
  m <<= 1;

  TSum Sum(n, x, y, a0);
  vector<mint> b(m);

  mint sum_all = 0;

  b[0] = b0;

  for (mint i = 1; i < m; i++)
  {
    b[i] = (mint(z) * b[i - 1] + t) & (num2);
    //c[i] = b[i] & (n - 1);
  }

  for (mint i = 0; i < m; i++)
    if (b[i] < 0)
      b[i] = n - b[i] % n;
    else
      b[i] = b[i] % n;

  for (mint i = 0; i < m / 2; i++)
    sum_all += Sum.getSum(b[2 * i], b[2 * i + 1]);

  cout << sum_all << "\n";
  //system("pause");
  return 0;
}
