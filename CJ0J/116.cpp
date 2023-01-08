#include <bits/stdc++.h>

constexpr int kN = 2.5e5 + 5, kM = 1e4 + 5, P = 998244353;

int n, p[kN], f[kM][kM];

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  std::cin >> n;
  for (int i = 0; i < n; ++i) std::cin >> p[i];
  if (p[0] != 1 || !std::is_sorted(p, p + n)) return std::cout << "0\n", 0;
  bool sub4 = 1, sub5 = 1;
  for (int i = 0; i < n; ++i) sub4 &= (p[i] == i / 2 + 1), sub5 &= (p[i] <= 2);
  if (sub4) return std::cout << "1\n", 0;
  if (sub5) return std::cout << std::max(1, (int)std::count(p, p + n, 2) - 1) << "\n", 0;
  int lis = p[n - 1];
  f[n - 1][1] = 1;
  for (int i = n - 2; ~i; --i)
    if (i == 0 || p[i] == p[i - 1] + 1) {
      (f[i][lis + 1 - p[i]] += f[i + 1][lis - p[i]]) %= P;
      for (int j = lis + 1 - p[i]; j <= n; ++j) (f[i][j] += f[i + 1][j]) %= P;
    } else
      for (int j = lis + 1 - p[i]; j <= n; ++j) f[i][j] = (f[i + 1][j] + f[i + 1][j - 1]) % P;
  std::cout << f[0][p[n - 1]] << "\n";
  return 0;
}
// 99 pts