#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<std::vector<int>>> g(n + 1, std::vector<std::vector<int>>(n, std::vector<int>(n, -1e9)));
    std::vector<std::vector<bool>> vis(n, std::vector<bool>(n, 0));
    std::vector<std::vector<int>> h(n, std::vector<int>(n, -1e9));
    std::string s;
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> v[i];
    std::cin >> s;

    std::function<void(int, int)> dfs = [&](int l, int r) {
      if (l > r) return g[0][l][r] = 0, void();
      if (vis[l][r]) return;
      vis[l][r] = 1;
      for (int x = l; x < r; ++x) dfs(l, x), dfs(x + 1, r);
      if (r > l) dfs(l + 1, r - 1);
      for (int k = 0; k <= r - l + 1; ++k) {
        for (int x = l; x < r; ++x)
          g[k][l][r] = std::max(g[k][l][r], g[0][l][x] + g[k][x + 1][r]),
          g[k][l][r] = std::max(g[k][l][r], g[k][l][x] + g[0][x + 1][r]);
        if (s[l] == s[r] && k > 1) g[k][l][r] = std::max(g[k][l][r], g[k - 2][l + 1][r - 1]);
      }
      bool ok = 1;
      for (int i = l, j = r; i < j; ++i, --j) ok &= s[i] == s[j];
      if (ok) g[r - l + 1][l][r] = std::max(g[r - l + 1][l][r], 0);
      for (int i = 1; i <= r - l + 1; ++i)
        if (~v[i]) g[0][l][r] = std::max(g[0][l][r], g[i][l][r] + v[i]);
      h[l][r] = std::max(g[0][l][r], 0);
      for (int p = l; p < r; ++p)
        for (int q = p + 1; q <= r; ++q) h[l][r] = std::max(h[l][r], h[l][p] + h[q][r]);
    };

    dfs(0, n - 1);
    std::cout << h[0][n - 1] << '\n';
  }
  return 0;
}