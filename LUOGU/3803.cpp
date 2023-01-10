#include <bits/stdc++.h>

using i64 = long long;

constexpr int kP = 998244353, kG = 3, kI = (kP + 1) / kG;

struct Poly {
  std::vector<int> vec, rev;
  Poly(std::vector<int> init = {}) { vec = init, rev.clear(); }
  void dft(bool inv) {
    int n = vec.size();
    while ((n & -n) != n) vec.emplace_back(0), ++n;
    if (inv == false || rev.size() != n) {
      rev.resize(n, 0);
      for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
    }
    for (int i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(vec[i], vec[rev[i]]);
    auto pw = [](int a, int b = kP - 2, int p = kP, int r = 1) {
      for (; b; b >>= 1, a = 1ll * a * a % kP)
        if (b & 1) r = 1ll * r * a % kP;
      return r;
    };
    for (int i = 1; i < n; i <<= 1)
      for (int j = 0; j < n; j += 2 * i) {
        int omega = pw(inv ? kI : kG, (kP - 1) / i / 2);
        for (int k = j, cur = 1; k < j + i; ++k, cur = 1ll * cur * omega % kP) {
          int u = vec[k], v = 1ll * cur * vec[k + i] % kP;
          vec[k] = u + v, vec[k + i] = u - v;
          if (vec[k] >= kP) vec[k] -= kP;
          if (vec[k + i] < 0) vec[k + i] += kP;
        }
      }
    if (inv) {
      int in = pw(n);
      for (int &t : vec) t = 1ll * t * in % kP;
    }
  }
  friend Poly operator*(Poly a, Poly b) {
    int tot = a.vec.size() + b.vec.size() - 1;
    a.vec.resize(tot), b.vec.resize(tot);
    a.dft(0), b.dft(0);
    Poly c;
    c.vec.resize(a.vec.size());
    for (int i = 0; i < a.vec.size(); ++i) c.vec[i] = 1ll * a.vec[i] * b.vec[i] % kP;
    c.dft(1), c.vec.resize(tot);
    return c;
  }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  Poly a, b;
  int n, m;
  std::cin >> n >> m;
  a.vec.resize(n + 1), b.vec.resize(m + 1);
  for (int &t : a.vec) std::cin >> t;
  for (int &t : b.vec) std::cin >> t;
  auto res = a * b;
  for (int t : res.vec) std::cout << t << " ";
  std::cout << "\n";
  return 0;
}