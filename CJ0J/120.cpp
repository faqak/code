#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n;
  i64 ans = 0;
  std::cin >> n;
  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  std::vector<std::vector<std::pair<int, int>>> color(n * n + 1);
  for (auto &v : a) for_each(begin(v), end(v), [](int &x) { std::cin >> x; });
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) color[a[i][j]].emplace_back(i, j);
  for (int c = 1; c <= n * n; ++c) {
    if (color[c].empty()) continue;
    std::vector<int> dis;
    for (auto p : color[c]) dis.emplace_back(p.first);
    std::sort(begin(dis), end(dis)), dis.erase(unique(begin(dis), end(dis)), end(dis));
    std::vector<std::vector<int>> row(dis.size());
    for (int i = 0; i < dis.size(); ++i) row[i].emplace_back(-1);
    for (auto p : color[c]) row[lower_bound(begin(dis), end(dis), p.first) - begin(dis)].emplace_back(p.second);
    for (int i = 0; i < dis.size(); ++i) row[i].emplace_back(n);
    for (auto p : color[c]) {
      int coef = n - p.first, id = lower_bound(begin(dis), end(dis), p.first) - begin(dis);
      int l = *--lower_bound(begin(row[id]), end(row[id]), p.second) + 1, r = n - 1;
      for (int j = id; j >= 0; --j) {
        if (l > r || l > p.second || r < p.second) break;
        ans += 1ll * coef * (p.second - l + 1) * (r - p.second + 1) * (dis[j] - (j == 0 ? -1 : dis[j - 1]));
        if (j == 0) break;
        l = std::max(l, *--upper_bound(begin(row[j - 1]), end(row[j - 1]), p.second) + 1);
        r = std::min(r, *lower_bound(begin(row[j - 1]), end(row[j - 1]), p.second) - 1);
      }
    }
  }
  std::cout << ans << "\n";
  return 0;
}