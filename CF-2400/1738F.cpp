#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  auto sol = []() {
    int n, all_col = 0;
    std::cin >> n;
    std::vector<int> deg(n), col(n, 0);
    std::set<std::pair<int, int>> set;
    for (int &elem : deg) std::cin >> elem;

    for (int i = 0; i < n; ++i) set.emplace(deg[i], i);
    while (!set.empty()) {
      int u = (--end(set))->second;
      bool found = 0;
      std::vector<int> neighbors = {u};
      for (int i = 0; i < deg[u]; ++i) {
        std::cout << "? " << u + 1 << std::endl;
        int v;
        std::cin >> v, --v, neighbors.emplace_back(v);
        if (col[v]) {
          found = 1;
          break;
        }
      }
      if (found)
        for (int t : neighbors) col[t] = col[neighbors.back()], set.erase({deg[t], t});
      else
        ++all_col, for_each(all(neighbors), [&](int elem) { col[elem] = all_col, set.erase({deg[elem], elem}); });
    }
    std::cout << "!";
    for (int t : col) std::cout << ' ' << t;
    std::cout << std::endl;
  };

  int t;
  std::cin >> t;
  while (t--) sol();
  return 0;
}