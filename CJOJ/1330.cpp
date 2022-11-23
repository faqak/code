#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, m, count_free = 0;
  i64 ans = 0;
  std::cin >> n >> m;
  std::vector<std::vector<char>> a(n, std::vector<char>(m));
  for (auto &elem : a) for_each(all(elem), [&](char &elem) { std::cin >> elem, count_free += elem == '.'; });

  // check whether the graph is connected
  std::vector<std::vector<int>> vis_s(n, std::vector<int>(m, 0));
  vis_s[0][0] = a[0][0] == '.';
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (a[i][j] == '.') vis_s[i][j] |= ((i ? vis_s[i - 1][j] : 0) | (j ? vis_s[i][j - 1] : 0));
  if (vis_s.back().back() == 0) return std::cout << 1ll * count_free * (count_free - 1) / 2 << '\n', 0;
  std::vector<std::vector<int>> vis_t(n, std::vector<int>(m, 0));
  vis_t[n - 1][m - 1] = 1;
  for (int i = n - 1; ~i; --i)
    for (int j = m - 1; ~j; --j)
      if (a[i][j] == '.') vis_t[i][j] |= ((i < n - 1 ? vis_t[i + 1][j] : 0) | (j < m - 1 ? vis_t[i][j + 1] : 0));

  auto get_rightmost = [&]() {
    std::vector<std::pair<int, int>> vec = {{0, 0}};
    std::pair<int, int> cur = {0, 0};
    while (cur != std::make_pair(n - 1, m - 1))
      ++((cur.second + 1 < m && vis_t[cur.first][cur.second + 1]) ? cur.second : cur.first), vec.emplace_back(cur);
    return vec;
  };
  auto get_bottom = [&]() {
    std::vector<std::pair<int, int>> vec = {{0, 0}};
    std::pair<int, int> cur = {0, 0};
    while (cur != std::make_pair(n - 1, m - 1))
      ++((cur.first + 1 < n && vis_t[cur.first + 1][cur.second]) ? cur.first : cur.second), vec.emplace_back(cur);
    return vec;
  };

  auto rightmost = get_rightmost(), bottom = get_bottom();
  std::set<std::pair<int, int>> in_r, in_b;
  int count_both = 0;

  for_each(all(rightmost), [&](auto e) { in_r.emplace(e); }), for_each(all(bottom), [&](auto e) { in_b.emplace(e); });
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) count_both += (in_r.count({i, j}) && in_b.count({i, j}));
  ans = 1ll * count_both * (count_free - 1) - 1ll * count_both * (count_both - 1) / 2;

  for (auto elem : rightmost) {
    int x = elem.first, y = elem.second;
    if (in_b.count({x, y})) continue;
    std::pair<int, int> cur;
    for (int nx = x + 1; nx < n; ++nx)
      if (vis_t[nx][y - 1] && vis_s[nx][y - 1]) {
        cur = {nx, y - 1};
        break;
      }
    std::pair<int, int> cur_tmp = cur;

    ans -= in_b.count(cur);
    while (!in_r.count(cur))
      ans += in_b.count(cur), --((cur.first && vis_s[cur.first - 1][cur.second]) ? cur.first : cur.second);
    cur = cur_tmp;
    while (!in_r.count(cur))
      ans += in_b.count(cur), ++((cur.second + 1 < m && vis_t[cur.first][cur.second + 1]) ? cur.second : cur.first);
  }

  std::cout << ans << '\n';
  return 0;
}