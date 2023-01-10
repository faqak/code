#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 1e9 + 7;
// clang-format off
int norm(int x){if(x<0)x+=P;if(x>=P)x-=P;return x;}template<class T>T power(T a,i64 b){T r=1;for(;b;b>>=1,a*=a)if(b&1)r*=a;return r;}struct Z{int x;Z(int x=0):x(norm(x)){}Z(i64 x):x(norm(x%P)){}int val()const{return x;}Z operator-()const{return Z(norm(P-x));}Z inv()const{assert(x!=0);return power(*this,P-2);}Z&operator*=(const Z&rhs){x=i64(x)*rhs.x%P;return*this;}Z&operator+=(const Z&rhs){x=norm(x+rhs.x);return*this;}Z&operator-=(const Z&rhs){x=norm(x-rhs.x);return*this;}Z&operator/=(const Z&rhs){return*this*=rhs.inv();}friend Z operator*(const Z&lhs,const Z&rhs){Z res=lhs;res*=rhs;return res;}friend Z operator+(const Z&lhs,const Z&rhs){Z res=lhs;res+=rhs;return res;}friend Z operator-(const Z&lhs,const Z&rhs){Z res=lhs;res-=rhs;return res;}friend Z operator/(const Z&lhs,const Z&rhs){Z res=lhs;res/=rhs;return res;}friend std::istream&operator>>(std::istream&is,Z&a){i64 v;is>>v;a=Z(v);return is;}friend std::ostream&operator<<(std::ostream&os,const Z&a){return os<<a.val();}};
// clang-format on

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n;
  Z tot = 1, ans = 0;
  std::cin >> n;
  std::vector<int> a(n), pos(n);

  {
    std::vector<std::pair<int, int>> tmp(n);
    int cnt = 0;
    for (auto &p : tmp) std::cin >> p.first, p.second = cnt++;
    std::sort(begin(tmp), end(tmp));
    for (int i = 0; i < n; ++i) a[i] = tmp[i].first, pos[i] = tmp[i].second;
  }

  for (int i = 0; i < n; ++i) tot = tot * (a[i] - i);
  if (tot.val() == 0) return std::cout << "0\n", 0;
  struct Node {
    int l, r;
    Z val, mul;
  };
  std::vector<Node> t(n << 2);

  auto Pushup = [&](int o) { t[o].val = t[o * 2].val + t[o * 2 + 1].val; };
  auto Pushdown = [&](int o) {
    if (t[o].mul.val() != 1)
      t[o * 2].val *= t[o].mul, t[o * 2 + 1].val *= t[o].mul, t[o * 2].mul *= t[o].mul, t[o * 2 + 1].mul *= t[o].mul,
          t[o].mul = 1;
  };

  std::function<void(int, int, int)> Build = [&](int o, int l, int r) {
    t[o].l = l, t[o].r = r;
    if (l == r) return t[o].val = 0, t[o].mul = 1, void();
    int mid = l + r >> 1;
    Build(o * 2, l, mid), Build(o * 2 + 1, mid + 1, r), Pushup(o);
  };

  std::function<Z(int, int, int)> Query = [&](int o, int l, int r) {
    if (l > r) return Z(0);
    int L = t[o].l, R = t[o].r;
    if (l <= L && R <= r) return t[o].val;
    if (l > R || L > r) return Z(0);
    Pushdown(o);
    return Query(o * 2, l, r) + Query(o * 2 + 1, l, r);
  };

  std::function<void(int, int, Z)> Add = [&](int o, int x, Z y) {
    int l = t[o].l, r = t[o].r, mid = l + r >> 1;
    if (l == r) return t[o].val += y, void();
    Pushdown(o), Add(o * 2 + (x > mid), x, y), Pushup(o);
  };

  std::vector<int> tre(n, 0);

  auto Addt = [&](int x, int v) {
    for (++x; x <= n; x += x & -x) tre[x - 1] += v;
  };

  auto Que = [&](int x) {
    int v = 0;
    for (++x; x; x &= x - 1) v += tre[x - 1];
    return v;
  };

  Build(1, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    ans += Query(1, 0, pos[i] - 1) * tot / 2 / (a[i] - i);
    ans -= Query(1, pos[i] + 1, n - 1) * tot / 2 / (a[i] - i);
    Z coef = Z(a[i] - i - 1) / Z(a[i] - i);
    ans += tot * (Que(n - 1) - Que(pos[i])), Addt(pos[i], 1);
    t[1].mul = t[1].mul * coef, t[1].val = t[1].val * coef, Add(1, pos[i], Z(a[i] - i - 1));
  }
  std::cout << ans << "\n";
  return 0;
}