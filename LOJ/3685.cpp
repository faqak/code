#include <bits/stdc++.h>

using i64 = long long;

constexpr int kN = 1.2e5 + 5, kLog = 17;

int n, m, a[kN][2], f[2][kLog][kN], jump[kLog][kN], tot, dep[kN], deg[2 * kN * (kLog + 3)];
bool vis[2 * kN * (kLog + 3)];
std::vector<int> g[kN], dag[2 * kN * (kLog + 3)];

void Dfs(int u, int fa) {
  f[0][0][u] = u + m, f[1][0][u] = u + m + n, jump[0][u] = fa, dep[u] = dep[fa] + 1;
  if (u > 1)
    for (int i = 1; i < kLog; ++i) {
      jump[i][u] = jump[i - 1][jump[i - 1][u]];
      f[0][i][u] = ++tot;
      dag[f[0][i - 1][u]].emplace_back(f[0][i][u]), dag[f[0][i - 1][jump[i - 1][u]]].emplace_back(f[0][i][u]);
      f[1][i][u] = ++tot;
      dag[f[1][i][u]].emplace_back(f[1][i - 1][u]), dag[f[1][i][u]].emplace_back(f[1][i - 1][jump[i - 1][u]]);
    }
  for (int v : g[u])
    if (v != fa) Dfs(v, u);
}
int Get(int u, int v) {
  if (dep[u] < dep[v]) std::swap(u, v);
  for (int i = kLog - 1; ~i; --i)
    if (dep[jump[i][u]] >= dep[v]) u = jump[i][u];
  if (u == v) return u;
  for (int i = kLog - 1; ~i; --i)
    if (jump[i][u] != jump[i][v]) u = jump[i][u], v = jump[i][v];
  return jump[0][u];
}

void Solve() {
  std::cin >> n;
  for (int i = 1; i <= tot; ++i) dag[i].clear();
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < kLog; ++j) jump[j][i] = f[0][j][i] = f[1][j][i] = 0;
  for (int i = 1; i <= n; ++i) g[i].clear();
  for (int i = 1, u, v; i < n; ++i) std::cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
  std::cin >> m, tot = 2 * n + m;
  for (int i = 1; i <= m; ++i)
    std::cin >> a[i][0] >> a[i][1], dag[i].emplace_back(a[i][0] + m), dag[a[i][1] + m + n].emplace_back(i);
  Dfs(1, 0);
  for (int i = 1; i <= m; ++i) {
    int u = a[i][0], v = a[i][1], l = Get(u, v);
    if (u != l) u = jump[0][u];
    for (int j = kLog - 1; ~j; --j)
      if (dep[jump[j][u]] >= dep[l]) dag[f[0][j][u]].emplace_back(i), u = jump[j][u];
    for (int j = kLog - 1; ~j; --j)
      if (dep[jump[j][v]] >= dep[l]) dag[f[0][j][v]].emplace_back(i), v = jump[j][v];
    u = a[i][0], v = a[i][1];
    if (v != l) v = jump[0][v];
    for (int j = kLog - 1; ~j; --j)
      if (dep[jump[j][u]] >= dep[l]) dag[i].emplace_back(f[1][j][u]), u = jump[j][u];
    for (int j = kLog - 1; ~j; --j)
      if (dep[jump[j][v]] >= dep[l]) dag[i].emplace_back(f[1][j][v]), v = jump[j][v];
    if (a[i][0] != l) dag[f[0][0][l]].emplace_back(i);
    if (a[i][1] != l) dag[i].emplace_back(f[1][0][l]);
  }
  std::queue<int> q;
  for (int i = 1; i <= tot; ++i) deg[i] = vis[i] = 0;
  for (int i = 1; i <= tot; ++i)
    for (int v : dag[i]) ++deg[v];
  for (int i = 1; i <= tot; ++i)
    if (!deg[i]) q.emplace(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop(), vis[u] = 1;
    for (int v : dag[u])
      if (--deg[v] == 0) q.emplace(v);
  }
  std::cout << (*std::min_element(vis + 1, vis + tot + 1) == 0 ? "No\n" : "Yes\n");
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int q;
  std::cin >> q;
  while (q--) Solve();
  return 0;
}