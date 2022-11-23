#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, m, p, q;
  i64 ans = 1e18;
  std::cin >> n >> m >> p >> q;
  std::vector<std::vector<char>> field(n, std::vector<char>(m));
  std::vector<std::vector<std::pair<int, int>>> g(n * m);
  std::vector<i64> dis(n * m, 1e18);
  std::vector<bool> vis(n * m, 0);
  std::priority_queue<std::pair<i64, int>> pq;
  for (auto &elem : field) for_each(all(elem), [](char &elem) { std::cin >> elem; });

  auto get = [&m](int i, int j) { return i * m + j; };

  auto add_edge = [&](int u, int v) {
    if (field[u][v] == 'L' && u && v < m - 1) g[get(u - 1, v + 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'L' && u < n - 1 && v < m - 1) g[get(u + 1, v + 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'L' && v < m - 2) g[get(u, v + 2)].emplace_back(get(u, v), q);
    if (field[u][v] == 'R' && u && v) g[get(u - 1, v - 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'R' && u < n - 1 && v) g[get(u + 1, v - 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'R' && v > 1) g[get(u, v - 2)].emplace_back(get(u, v), q);
    if (field[u][v] == 'U' && u < n - 1 && v < m - 1) g[get(u + 1, v + 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'U' && u < n - 1 && v) g[get(u + 1, v - 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'U' && u < n - 2) g[get(u + 2, v)].emplace_back(get(u, v), q);
    if (field[u][v] == 'D' && u && v < m - 1) g[get(u - 1, v + 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'D' && u && v) g[get(u - 1, v - 1)].emplace_back(get(u, v), p);
    if (field[u][v] == 'D' && u > 1) g[get(u - 2, v)].emplace_back(get(u, v), q);
  };

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) add_edge(i, j);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (field[i][j] == '.') pq.emplace(dis[get(i, j)] = 0, get(i, j));

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto [v, w] : g[u])
      if (dis[v] > dis[u] + w) pq.emplace(-(dis[v] = dis[u] + w), v);
  }

  for (int i = 0; i < n; ++i)
    for (int j = 1; j < m; ++j) ans = std::min(ans, dis[get(i, j)] + dis[get(i, j - 1)]);
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j) ans = std::min(ans, dis[get(i, j)] + dis[get(i - 1, j)]);

  std::cout << (ans == 1e18 ? -1 : ans) << '\n';
  return 0;
}