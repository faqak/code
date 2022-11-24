#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::vector<int> cand;
    std::multiset<i64> val;
    std::vector<std::vector<i64>> f;

    {
      int ori = n;
      for (int i = 2; i * i <= ori; ++i)
        if (ori % i == 0) {
          cand.emplace_back(n / i), f.emplace_back(std::vector<i64>(n / i, 0));
          for (int j = 0; j < n / i; ++j) val.emplace(0);
          while (ori % i == 0) ori /= i;
        }
      if (ori > 1) {
        cand.emplace_back(n / ori), f.emplace_back(std::vector<i64>(n / ori, 0));
        for (int i = 0; i < n / ori; ++i) val.emplace(0);
      }
    }

    auto add = [&](int p, int x) {
      for (int i = 0; i < cand.size(); ++i)
        val.erase(val.find(cand[i] * f[i][p % cand[i]])), val.emplace(cand[i] * (f[i][p % cand[i]] += x - a[p]));
      a[p] = x;
    };

    for (int i = 0, x; i < n; ++i) std::cin >> x, add(i, x);

    std::cout << *val.rbegin() << '\n';
    while (q--) {
      int p, x;
      std::cin >> p >> x, --p, add(p, x), std::cout << *val.rbegin() << '\n';
    }
  };

  int t;
  std::cin >> t;
  while (t--) sol();
  return 0;
}