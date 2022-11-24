#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, g[--u].emplace_back(--v, w), g[v].emplace_back(u, w);

  auto dijkstra = [&](std::vector<i64> &dis) {
    std::vector<bool> vis(n, 0);
    std::priority_queue<std::pair<i64, int>> q;
    for (int i = 0; i < n; ++i) q.emplace(-dis[i], i);
    while (!q.empty()) {
      int u = q.top().second;
      q.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (auto [v, w] : g[u])
        if (dis[v] > dis[u] + w) q.emplace(-(dis[v] = dis[u] + w), v);
    }
  };

  std::vector<i64> sid(n, 0), dis(n, 0);
  for (int i = 1; i < n; ++i) dis[i] = 1e18;
  dijkstra(dis);

  std::function<void(int, int, int, int)> sol = [&](int l, int r, int pl, int pr) {
    if (l > r) return;
    int mid = l + r >> 1, p;
    sid[mid] = 1e18;
    for (int i = pl; i <= pr; ++i) {
      i64 key = dis[i] + 1ll * (i - mid) * (i - mid);
      if (sid[mid] > key) sid[mid] = key, p = i;
    }
    sol(l, mid - 1, pl, p), sol(mid + 1, r, p, pr);
  };

  while (k--) sol(0, n - 1, 0, n - 1), swap(sid, dis), dijkstra(dis);

  for (int i = 0; i < n; ++i) std::cout << dis[i] << "\n "[i < n - 1];
  return 0;
}