#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using db = double;

struct Li_Chao {
  using lin = std::pair<db, db>;
  struct Node {
    int l, r;
    bool cont;
    lin best;
    Node() { cont = 0, best = {0, 0}; }
  };
  std::vector<Node> t;
  inline db Get(const lin &l, int x) { return l.first * x + l.second; }
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
  Li_Chao(int mx) { t.resize((mx + 1 << 2) + 1), Build(1, 0, mx); }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  Li_Chao solve(5e4);
  int n;
  std::cin >> n;
  while (n--) {
    std::string s;
    std::cin >> s;
    if (s[0] == 'P') {
      db s, p;
      std::cin >> s >> p;
      solve.Add(1, {p, s - p});
    } else {
      int t;
      std::cin >> t;
      std::cout << int(solve.Query(1, t) / 100) << "\n";
    }
  }
  return 0;
}