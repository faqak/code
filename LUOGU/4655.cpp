#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

struct Li_Chao {
  using lin = std::pair<i64, i64>;
  struct Node {
    int l, r;
    bool cont;
    lin best;
    Node() { cont = 0, best = {0ll, LLONG_MAX}; }
  };
  std::vector<Node> t;
  inline i64 Get(const lin &l, int x) { return l.first * x + l.second; }
  void Build(int o, int l, int r) {
    t[o].l = l, t[o].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    Build(o * 2, l, mid), Build(o * 2 + 1, mid + 1, r);
  }
  void Add(int o, const lin &cur) {
    int l = t[o].l, r = t[o].r;
    auto ori = t[o].best;
    if (Get(cur, l) <= Get(ori, l) && Get(cur, r) <= Get(ori, r)) return t[o].cont = 1, t[o].best = cur, void();
    if (Get(cur, l) >= Get(ori, l) && Get(cur, r) >= Get(ori, r)) return;
    Add(o * 2, cur), Add(o * 2 + 1, cur);
  }
  i64 Query(int o, int x) {
    int l = t[o].l, r = t[o].r, mid = l + r >> 1;
    if (l == r) return Get(t[o].best, x);
    return std::min(Get(t[o].best, x), Query(o * 2 + (x > mid), x));
  }
  Li_Chao(int mx) { t.resize((mx + 1 << 2) + 1), Build(1, 0, mx); }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, mx = 0;
  std::cin >> n;
  std::vector<int> h(n);
  std::vector<i64> w(n), f(n, 0ll), pre(n);
  for (int &t : h) std::cin >> t, mx = std::max(mx, t);
  Li_Chao solve(mx);
  for (i64 &t : w) std::cin >> t;
  partial_sum(all(w), begin(pre));

  auto Add = [&](int i) { solve.Add(1, {-2ll * h[i], f[i] + 1ll * h[i] * h[i] - pre[i]}); };

  Add(0);
  for (int i = 1; i < n; ++i) f[i] = solve.Query(1, h[i]) + 1ll * h[i] * h[i] + pre[i - 1], Add(i);
  std::cout << f[n - 1] << "\n";
  return 0;
}