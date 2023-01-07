#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

void Solve() {
  int n;
  std::string s;
  std::cin >> n >> s;
  std::vector<std::vector<int>> g(n, std::vector<int>());
  std::vector<int> siz(n, 1), mx(n, 0);
  for (int i = 1, u, v; i < n; ++i) std::cin >> u >> v, g[--u].emplace_back(--v), g[v].emplace_back(u);

  std::function<void(int, int)> Dfs = [&](int u, int fa) {
    for (int v : g[u])
      if (v != fa) Dfs(v, u), mx[u] = std::max(mx[u], siz[v]), siz[u] += siz[v];
    mx[u] = std::max(mx[u], n - siz[u]);
  };

  Dfs(0, 0);
  if (n & 1) {
    int key = -1;
    for (int i = 0; i < n; ++i) {
      if (mx[i] * 2 > n) continue;
      key = i;
    }
    for (int i = 0; i < n; ++i)
      if (mx[i] * 2 < n && s[i] == 'R') return std::cout << "Royale\n", void();
    int sum_c = 0, sum_r = 0;
    for_each(all(siz), [](int &x) { x = 1; }), Dfs(key, key);
    for (int v : g[key]) (s[v] > 'C' ? sum_r : sum_c) += siz[v];
    return std::cout << (sum_c < sum_r ? "Royale\n" : "Clash\n"), void();
  }
  std::vector<int> gr;
  for (int i = 0; i < n; ++i)
    if (mx[i] * 2 <= n) gr.emplace_back(i);
  if (gr.size() == 2 && s[gr[0]] == 'R' && s[gr[1]] == 'R') return std::cout << "Royale\n", void();
  if (gr.size() == 2) return std::cout << "Clash\n", void();
  if (s[gr[0]] == 'C') return std::cout << "Clash\n", void();
  int sum_c = 0, sum_r = 0;
  for_each(all(siz), [](int &x) { x = 1; }), Dfs(gr[0], gr[0]);
  for (int v : g[gr[0]]) (s[v] > 'C' ? sum_r : sum_c) += siz[v];
  return std::cout << (sum_c < sum_r ? "Royale\n" : "Clash\n"), void();
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int t;
  std::cin >> t;
  while (t--) Solve();
  return 0;
}