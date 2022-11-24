#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n;
    std::cin >> n;
    std::vector<int> d[2];
    d[0].resize(n), d[1].resize(n);
    for_each(all(d[0]), [](int &e) { std::cin >> e; }), for_each(all(d[1]), [](int &e) { std::cin >> e; });

    auto check = [&](int p_d) {
      std::vector<std::pair<int, int>> val;
      std::vector<int> a(0);
      std::multiset<int> find[2];
      for (int t : d[0]) val.emplace_back(t, 0), find[0].emplace(t);
      for (int t : d[1]) val.emplace_back(t, 1), find[1].emplace(t);

      sort(all(val), std::greater<>());
      for (auto p : val) {
        if (find[p.second].find(p.first) == end(find[p.second])) continue;
        if (find[p.second ^ 1].find(abs(p_d - p.first)) == end(find[p.second ^ 1])) return 0;
        if (p.second) a.emplace_back(p_d - p.first);
        if (p.second == 0) a.emplace_back(p.first);
        find[p.second ^ 1].erase(find[p.second ^ 1].find(abs(p_d - p.first)));
        find[p.second].erase(find[p.second].find(p.first));
      }
      int delta = std::min(std::min(0, *std::min_element(all(a))), p_d);
      std::cout << "YES\n";
      for (int t : a) std::cout << t - delta << ' ';
      std::cout << "\n" << -delta << ' ' << p_d - delta << '\n';
      return 1;
    };

    for (int i = 0; i < n; ++i) {
      if (check(abs(d[0][0] - d[1][i]))) return;
      if (check(d[0][0] + d[1][i])) return;
    }
    std::cout << "NO\n";
  };

  int t;
  std::cin >> t;
  while (t--) sol();
  return 0;
}