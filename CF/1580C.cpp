#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, m;
  std::cin >> n >> m;
  const int b = sqrt(m);
  std::vector<std::pair<int, int>> a(n);
  std::vector<int> in(n), del(m + 1, 0);
  std::vector<std::vector<int>> add(b, std::vector<int>(b, 0));
  for (auto &p : a) std::cin >> p.first >> p.second;

  auto Add = [&](int l, int r, int v) { del[l] += v, del[r] -= v; };

  for (int day = 0, sum = 0, op, x, term, cur; day < m; ++day) {
    std::cin >> op >> x, cur = 0, --x, term = a[x].first + a[x].second;
    if (op == 1) in[x] = day;
    if (term < b)
      for (int i = a[x].first; i < term; ++i) add[term][(in[x] + i) % term] += 2 * (op < 2) - 1;
    else
      for (int i = in[x] + a[x].first; i < m; i += term)
        Add(std::max(day, i), std::max(day, std::min(m, i + a[x].second)), 2 * (op < 2) - 1);
    for (int i = 1; i < b; ++i) cur += add[i][day % i];
    sum += del[day], std::cout << cur + sum << "\n";
  }
  return 0;
}