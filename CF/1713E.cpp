#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (auto &elem : a) for_each(all(elem), [](int &elem) { std::cin >> elem; });
    std::vector<int> fa(2 * n);
    std::iota(all(fa), 0);

    std::function<int(int)> get = [&](int x) { return x != fa[x] ? fa[x] = get(fa[x]) : x; };

    auto add_edge = [&](int u, int v) {
      if (a[u][v] < a[v][u] && get(u) != get(v + n))
        fa[get(u)] = get(v), fa[get(u + n)] = get(v + n);
      else if (a[u][v] > a[v][u] && get(u) != get(v))
        fa[get(u)] = get(v + n), fa[get(u + n)] = get(v);
    };

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (i < j) add_edge(i, j);

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (i < j && get(i) == get(j + n)) std::swap(a[j][i], a[i][j]);

    for (auto vec : a) for_each(all(vec), [](int elem) { std::cout << elem << ' '; }), std::cout << '\n';
  };

  int t;
  std::cin >> t;
  while (t--) sol();
  return 0;
}