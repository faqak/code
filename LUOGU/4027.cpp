#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using db = double;

struct Li_Chao {
  using lin = std::pair<db, db>;
  struct Node {
    int l, r;
    bool cont;
    lin best;
    Node() { cont = 0, best = {0, -1e18}; }
  };
  std::vector<Node> t;
  std::vector<db> my;
  inline db Get(const lin &l, db x) { return l.first * my[x] + l.second; }
  void Build(int o, int l, int r) {
    t[o].l = l, t[o].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    Build(o * 2, l, mid), Build(o * 2 + 1, mid + 1, r);
  }
  void Add(int o, const lin &cur) {
    int l = t[o].l, r = t[o].r;
    auto ori = t[o].best;
    if (Get(cur, l) >= Get(ori, l) && Get(cur, r) >= Get(ori, r)) return t[o].cont = 1, t[o].best = cur, void();
    if (Get(cur, l) <= Get(ori, l) && Get(cur, r) <= Get(ori, r)) return;
    Add(o * 2, cur), Add(o * 2 + 1, cur);
  }
  db Query(int o, int x) {
    int l = t[o].l, r = t[o].r, mid = l + r >> 1;
    if (l == r) return Get(t[o].best, x);
    return std::max(Get(t[o].best, x), Query(o * 2 + (x > mid), x));
  }
  Li_Chao(std::vector<db> disc) { my = disc, t.resize(disc.size() << 2), Build(1, 0, disc.size() - 1); }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n;
  db s;
  std::cin >> n >> s;
  std::vector<db> a(n), b(n), rat(n), f(n), discrete;
  for (int i = 0; i < n; ++i) std::cin >> a[i] >> b[i] >> rat[i], discrete.emplace_back(a[i] / b[i]);
  std::sort(all(discrete));
  Li_Chao solve(discrete);
  for (int i = 0; i < n; ++i) {
    f[i] = b[i] * solve.Query(1, std::lower_bound(all(discrete), a[i] / b[i]) - begin(discrete));
    if (i > 0)
      f[i] = std::max(f[i], f[i - 1]);
    else
      f[i] = std::max(f[i], s);
    solve.Add(1, {f[i] * rat[i] / (a[i] * rat[i] + b[i]), f[i] / (a[i] * rat[i] + b[i])});
  }
  std::cout << std::fixed << std::setprecision(3) << f.back() << "\n";
  return 0;
}