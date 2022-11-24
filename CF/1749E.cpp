#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n, m;
    std::cin >> n >> m;

    auto get_id = [&m](int i, int j) { return i * m + j; };

    std::vector<std::vector<char>> a(n, std::vector<char>(m));
    std::vector<int> pre(n * m), vis(n * m, 0);
    std::deque<std::pair<int, int>> dq;
    for (auto &elem : a) for_each(all(elem), [](char &elem) { std::cin >> elem; });

    auto check = [&](int x, int y) -> bool {
      if (x + 1 < n && a[x + 1][y] == '#') return 0;
      if (x && a[x - 1][y] == '#') return 0;
      if (y && a[x][y - 1] == '#') return 0;
      return (y + 1 < m && a[x][y + 1] == '#') == 0;
    };

    for (int i = 0; i < n; ++i)
      if (check(i, 0)) {
        pre[get_id(i, 0)] = -1;
        if (a[i][0] == '#')
          dq.emplace_front(i, 0);
        else
          dq.emplace_back(i, 0);
        vis[get_id(i, 0)] = 1;
      }
    while (!dq.empty()) {
      int x = dq.front().first, y = dq.front().second;

      if (y == m - 1) {
        int cur = get_id(x, y);
        while (cur >= 0) a[cur / m][cur % m] = '#', cur = pre[cur];
        std::cout << "YES\n";
        for (auto vec : a) for_each(all(vec), [](char elem) { std::cout << elem; }), std::cout << '\n';
        return;
      }

      dq.pop_front();

      auto upd = [&](int i, int j) {
        if (vis[get_id(i, j)]) return;
        vis[get_id(i, j)] = 1, pre[get_id(i, j)] = get_id(x, y);
        if (a[i][j] == '#')
          dq.emplace_front(i, j);
        else
          dq.emplace_back(i, j);
      };

      if (x + 1 < n && y + 1 < m && check(x + 1, y + 1)) upd(x + 1, y + 1);
      if (x && y + 1 < m && check(x - 1, y + 1)) upd(x - 1, y + 1);
      if (x + 1 < n && y && check(x + 1, y - 1)) upd(x + 1, y - 1);
      if (x && y && check(x - 1, y - 1)) upd(x - 1, y - 1);
    }
    std::cout << "NO\n";
  };

  int t;
  std::cin >> t;
  while (t--) sol();
  return 0;
}