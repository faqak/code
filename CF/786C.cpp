#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n;
  std::cin >> n;
  int lim = sqrt(n * log2(n));
  std::vector<int> a(n);
  for (int &t : a) std::cin >> t;

  auto Solve = [&](int x) {
    std::vector<int> occ(n + 1, 0), tag;
    int m = 1, siz = 0;
    for (int t : a)
      if (siz + !occ[t] <= x)
        siz += !occ[t], tag.emplace_back(t), occ[t] = 1;
      else {
        for (int t : tag) occ[t] = 0;
        ++m, occ[t] = 1, tag = {t}, siz = 1;
      }
    return m;
  };

  for (int i = 1; i <= lim; ++i) std::cout << Solve(i) << " ";
  int cur = lim + 1;
  for (int ans = sqrt(n) + 1; ans; --ans) {
    if (Solve(cur) != ans) continue;
    if (cur > n) break;
    int lo = cur, hi = n;
    while (lo < hi) {
      int mid = lo + hi + 1 >> 1;
      if (Solve(mid) == ans)
        lo = mid;
      else
        hi = mid - 1;
    }
    for (int j = cur; j <= lo; ++j) std::cout << ans << " ";
    cur = lo + 1;
  }
  std::cout << "\n";
  return 0;
}