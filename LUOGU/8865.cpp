#include <bits/stdc++.h>

#define all(V) begin(V), end(V)

using i64 = long long;

constexpr int P = 998244353;
// clang-format off
int norm(int x){if(x<0)x+=P;if(x>=P)x-=P;return x;}template<class T>T power(T a,i64 b){T r=1;for(;b;b>>=1,a*=a)if(b&1)r*=a;return r;}struct Z{int x;Z(int x=0):x(norm(x)){}Z(i64 x):x(norm(x%P)){}int val()const{return x;}Z operator-()const{return Z(norm(P-x));}Z inv()const{assert(x!=0);return power(*this,P-2);}Z&operator*=(const Z&rhs){x=i64(x)*rhs.x%P;return*this;}Z&operator+=(const Z&rhs){x=norm(x+rhs.x);return*this;}Z&operator-=(const Z&rhs){x=norm(x-rhs.x);return*this;}Z&operator/=(const Z&rhs){return*this*=rhs.inv();}friend Z operator*(const Z&lhs,const Z&rhs){Z res=lhs;res*=rhs;return res;}friend Z operator+(const Z&lhs,const Z&rhs){Z res=lhs;res+=rhs;return res;}friend Z operator-(const Z&lhs,const Z&rhs){Z res=lhs;res-=rhs;return res;}friend Z operator/(const Z&lhs,const Z&rhs){Z res=lhs;res/=rhs;return res;}friend std::istream&operator>>(std::istream&is,Z&a){i64 v;is>>v;a=Z(v);return is;}friend std::ostream&operator<<(std::ostream&os,const Z&a){return os<<a.val();}};
// clang-format on

void solve() {
  int n, m;
  Z v_c, v_f, c, f;
  std::cin >> n >> m >> c >> f;
  std::vector<std::vector<int>> a(n, std::vector<int>(m, 0));
  std::vector<std::vector<int>> rig(n, std::vector<int>(m + 1, 0)), dow(n + 1, std::vector<int>(m, 0));
  std::vector<std::vector<Z>> suf(n + 1, std::vector<Z>(m)), fus(n + 1, std::vector<Z>(m));
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < m; ++j) a[i][j] = s[j] - '0';
  }
  for (int i = 0; i < n; ++i)
    for (int j = m - 1; ~j; --j) rig[i][j] = (1 - a[i][j]) * (rig[i][j + 1] + 1);
  for (int i = n - 1; ~i; --i)
    for (int j = 0; j < m; ++j) dow[i][j] = (1 - a[i][j]) * (dow[i + 1][j] + 1);
  for (int i = 0; i < n; ++i) for_each(all(rig[i]), [](int &x) { --x; }), for_each(all(dow[i]), [](int &x) { --x; });
  for (int i = n - 1; ~i; --i)
    for (int j = 0; j < m; ++j) {
      suf[i][j] = suf[i + 1][j] + Z(1 - a[i][j]) * Z(rig[i][j]);
      fus[i][j] = fus[i + 1][j] + Z(1 - a[i][j]) * Z(rig[i][j]) * Z(dow[i][j]);
      if (a[i][j]) continue;
      if (dow[i][j] < 2) continue;
      v_c += Z(rig[i][j]) * (suf[i + 2][j] - suf[i + dow[i][j] + 1][j]);
      v_f += Z(rig[i][j]) * (fus[i + 2][j] - fus[i + dow[i][j] + 1][j]);
    }
  std::cout << c * v_c << ' ' << f * v_f << '\n';
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int t, id;
  std::cin >> t >> id;
  while (t--) solve();
  return 0;
}