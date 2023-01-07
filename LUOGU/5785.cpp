#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, s, h = 0, t = -1;
  std::cin >> n >> s;
  std::vector<i64> tt(n), c(n), f(n, 0), pre_t(n), pre_c(n);
  std::vector<int> q(n);
  for (int i = 0; i < n; ++i) std::cin >> tt[i] >> c[i];
  std::partial_sum(all(tt), begin(pre_t)), std::partial_sum(all(c), begin(pre_c));

  auto Y = [&](int i) { return f[i] - s * pre_c[i]; };

  auto X = [&](int i) { return pre_c[i]; };

  for (int i = 0; i < n; ++i) {
    f[i] = pre_c[i] * pre_t[i] + s * pre_c[n - 1] - pre_c[i] * pre_t[i] - s * pre_c[n - 1];
    // for (int j = 0; j < i; ++j) f[i] = std::min(f[i], Y(j) - X(j) * pre_t[i]);
    if (h <= t) {
      int lo = h, hi = t;
      while (lo < hi) {
        int mid = lo + hi >> 1;
        if (Y(q[mid + 1]) - Y(q[mid]) > pre_t[i] * (X(q[mid + 1]) - X(q[mid])))
          hi = mid;
        else
          lo = mid + 1;
      }
      f[i] = std::min(f[i], Y(q[lo]) - X(q[lo]) * pre_t[i]);
    }
    f[i] += pre_c[i] * pre_t[i] + s * pre_c[n - 1];
    while (h < t && (Y(q[t]) - Y(q[t - 1])) * (X(i) - X(q[t])) >= (Y(i) - Y(q[t])) * (X(q[t]) - X(q[t - 1]))) --t;
    q[++t] = i;
  }
  std::cout << f[n - 1] << "\n";
  return 0;
}