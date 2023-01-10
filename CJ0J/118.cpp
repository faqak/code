#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  constexpr int kP = 1e9 + 7;
  int n, m, x, y, ans = 0;
  std::cin >> n >> m >> x >> y;
  for (int a = 1; a <= n; ++a)
    for (int b = 1; b <= m; ++b) {
      auto ChkUL = [&](int i, int j) { return i < x && j < y; };

      auto ChkUR = [&](int i, int j) { return i < x && b - j <= y; };

      auto ChkDL = [&](int i, int j) { return a - i <= x && j < y; };

      auto ChkDR = [&](int i, int j) { return a - i <= x && b - j <= y; };

      std::array<int, 1 << 6> f;
      f.fill(0), f[0] = 1;

      for (int i = 0; i < a; ++i)
        for (int j = 0; j < b; ++j) {
          int c = (i == 0) + 2 * (i == a - 1) + 4 * (j == 0) + 8 * (j == b - 1);
          c += 16 * (!ChkUL(i, j) && !ChkDR(i, j)) + 32 * (!ChkUR(i, j) && !ChkDL(i, j));
          std::array<int, 1 << 6> g = f;
          for (int k = 0; k < (1 << 6); ++k) (g[k | c] += f[k]) %= kP;
          std::swap(f, g);
        }

      (ans += (1ll * f[15] + f[31] + f[47]) * (n - a + 1) % kP * 1ll * (m - b + 1) % kP) %= kP;
    }

  std::cout << (ans + 1) % kP << "\n";
  return 0;
}