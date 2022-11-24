#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, ans = 0;
  std::cin >> n;
  std::vector<int> a(n);
  for (int &t : a) std::cin >> t;
  std::vector<std::vector<int>> g(n);
  std::vector<std::set<int>> set(n);
  for (int i = 1, u, v; i < n; ++i) std::cin >> u >> v, --u, --v, g[u].emplace_back(v), g[v].emplace_back(u);

  std::function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
    bool erase = 0;

    set[u].emplace(d);
    for (int v : g[u])
      if (v != fa) {
        dfs(v, u, d ^ a[v]);
        if (set[u].size() < set[v].size()) std::swap(set[u], set[v]);
        for (int t : set[v]) erase |= (set[u].count(t ^ a[u]));
        for (int t : set[v]) set[u].emplace(t);
      }

    if (erase) ++ans, set[u].clear();
  };

  dfs(0, 0, a[0]);

  std::cout << ans << '\n';
  return 0;
}