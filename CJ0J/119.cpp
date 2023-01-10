#include <bits/stdc++.h>

using i64 = long long;

constexpr int kN = 1e5 + 5, kP = 998244353, kG = 3, kI = (kP + 1) / kG;

int n, k, a[kN], b[kN << 1], nxt[kN];

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

    auto Pw = [](int a, int b = kP - 2, int p = kP, int r = 1) {
      for (; b; b >>= 1, a = 1ll * a * a % kP)
        if (b & 1) r = 1ll * r * a % kP;
      return r;
    };

    for (int i = 1; i < n; i <<= 1)
      for (int j = 0; j < n; j += 2 * i) {
        int omega = Pw(inv ? kI : kG, (kP - 1) / i / 2);
        for (int k = j, cur = 1; k < j + i; ++k, cur = 1ll * cur * omega % kP) {
          int u = vec[k], v = 1ll * cur * vec[k + i] % kP;
          vec[k] = u + v, vec[k + i] = u - v;
          if (vec[k] >= kP) vec[k] -= kP;
          if (vec[k + i] < 0) vec[k + i] += kP;
        }
      }
    if (inv) {
      int in = Pw(n);
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
  std::cin >> n >> k;
  for (int i = 0; i < n; ++i) std::cin >> a[i];
  for (int i = 0; i < n; ++i) std::cin >> b[i], b[i + n] = b[i];
  if (k >= n - 1) return std::cout << "0\n", 0;

  std::vector<int> fac(k + 2, 1);
  for (int i = 1; i < k + 2; ++i) fac[i] = 1ll * fac[i - 1] * i % kP;

  auto Pw = [](int a, int b = kP - 2, int p = kP, int r = 1) {
    for (; b; b >>= 1, a = 1ll * a * a % kP)
      if (b & 1) r = 1ll * r * a % kP;
    return r;
  };

  auto C = [&](int x, int y) { return 1ll * fac[x] * Pw(fac[y]) % kP * 1ll * Pw(fac[x - y]) % kP; };

  std::vector<int> dif_a;
  Poly cur, trans;
  cur.vec.resize(n);
  for (int i = 0; i < n; ++i) cur.vec[i] = a[i];
  trans.vec.resize(k + 2);
  for (int i = 0; i <= k + 1; ++i) trans.vec[i] = 1ll * ((i & 1) ? kP - 1 : 1) * C(k + 1, i) % kP;
  cur = cur * trans;
  for (int i = k + 1; i < n; ++i) dif_a.emplace_back(cur.vec[i]);

  std::vector<int> dif_b;
  Poly ruc;
  for (int i = 0; i < 2 * n; ++i) ruc.vec.emplace_back(b[i]);
  ruc = ruc * trans;
  for (int i = k + 1; i < 2 * n; ++i) dif_b.emplace_back(ruc.vec[i]);

  dif_a.insert(begin(dif_a), -1), dif_b.insert(begin(dif_b), -1);
  for (int i = 1, j = 0; i < dif_a.size(); ++i) {
    while (j && dif_a[j + 1] != dif_a[i]) j = nxt[j];
    nxt[i] = (j += (dif_a[j + 1] == dif_a[i]));
  }
  for (int i = 1, j = 0; i < dif_b.size(); ++i) {
    while (j && dif_a[j + 1] != dif_b[i]) j = nxt[j];
    if ((j += (dif_a[j + 1] == dif_b[i])) == dif_a.size() - 1) return std::cout << i - dif_a.size() + 1 << "\n", 0;
  }
  std::cout << "-1\n";
  return 0;
}