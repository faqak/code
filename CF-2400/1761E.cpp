#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n), blocks(0);

    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      for (int j = 0; j < n; ++j)
        if (s[j] - '0') g[i].emplace_back(j);
    }

    std::vector<bool> vis(n, 0);
    std::function<void(int)> dfs = [&](int u) {
      blocks.back().emplace_back(u), vis[u] = 1;
      for (int v : g[u])
        if (!vis[v]) dfs(v);
    };

    for (int i = 0; i < n; ++i)
      if (!vis[i]) blocks.emplace_back(std::vector<int>(0)), dfs(i);

    // ans = 0
    if (blocks.size() == 1) return std::cout << "0\n", void();
    // ans = 1
    for (auto elem : blocks)
      if (elem.size() == 1) return std::cout << "1\n" << elem[0] + 1 << '\n', void();
    for (auto elem : blocks) {
      bool clique = 1;
      std::pair<int, int> choose = {1e9, 1e9};

      for (int u : elem)
        if (g[u].size() != elem.size() - 1) clique = 0;

      if (clique) continue;
      for (int u : elem) choose = std::min(choose, {g[u].size(), u});

      return std::cout << "1\n" << choose.second + 1 << '\n', void();
    }
    // ans = 2
    if (blocks.size() > 2) {
      std::cout << "2\n" << blocks[0][0] + 1 << ' ';
      std::pair<int, int> choose = {1e9, 1e9};
      for (int i = 1; i < blocks.size(); ++i) choose = std::min(choose, {blocks[i].size(), blocks[i][0]});
      return std::cout << choose.second + 1 << '\n', void();
    }
    // ans > 2
    if (blocks[0].size() > blocks[1].size()) std::swap(blocks[0], blocks[1]);
    std::cout << blocks[0].size() << '\n';
    for (int t : blocks[0]) std::cout << t + 1 << " \n"[t == blocks[0].back()];
  };

  int T;
  std::cin >> T;
  while (T--) sol();
  return 0;
}