#include <bits/stdc++.h>

using i64 = long long;

struct UFS {
  std::vector<int> fa;
  int conn;
  UFS(int n = 0) { conn = n, fa.resize(n), iota(begin(fa), end(fa), 0); }

  int Get(int x) { return x != fa[x] ? fa[x] = Get(fa[x]) : x; }

  void Merge(int u, int v) { conn -= int(Get(u) != Get(v)), fa[Get(u)] = Get(v); }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  constexpr int kP = 998244353;
  std::array<UFS, 1 << 21> conn;
  std::array<int, 21> e;
  std::array<int, 1 << 21> pre;
  int n, ans = 0, cant = (1 << 21) - 1;
  std::cin >> n, e.fill(0), conn.fill(21);
  std::vector<int> a(n);
  for (int &t : a) std::cin >> t, ++pre[t];
  for (int t : a)
    for (int i = 0; i < 21; ++i)
      if (t >> i & 1) e[i] |= t, cant &= (cant ^ (1 << i));
  for (int i = 1; i < (1 << 21); ++i) {
    int key = i & -i, dot = __builtin_ctz(key);
    conn[i] = conn[i ^ key];
    for (int j = 0; j < 21; ++j)
      if ((e[dot] >> j & 1) && (i >> j & 1)) conn[i].Merge(dot, j);
  }
  for (int j = 0; j < 21; ++j)
    for (int i = 0; i < (1 << 21); ++i)
      if (i & (1 << j)) (pre[i] += pre[i ^ (1 << j)]) %= kP;

  auto pw = [](int a, int b, int p, int r = 1) {
    for (; b; b >>= 1, a = 1ll * a * a % p)
      if (b & 1) r = 1ll * r * a % p;
    return r;
  };

  for (int st = 0; st < (1 << 21); ++st) {
    if (st & cant) continue;
    int coef = (__builtin_popcount(st) & 1) ? kP - 1 : 1;
    int sur = (1 << conn[st].conn - 21 + __builtin_popcount(st));
    sur = 1ll * sur * pw(2, pre[(1 << 21) - 1 - st], kP) % kP;
    (ans += 1ll * (sur + kP - 2) * coef % kP) %= kP;
  }
  std::cout << ans << "\n";
  return 0;
}