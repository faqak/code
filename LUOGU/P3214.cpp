#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  constexpr int P = 1e8 + 7;

  auto pw = [&](int a, int b = 1e8 + 5, int p = 1e8 + 7, int r = 1) {
    for (; b; b >>= 1, a = 1ll * a * a % p)
      if (b & 1) r = 1ll * r * a % p;
    return r;
  };

  int n, m;
  std::cin >> n >> m;
  int pw_2 = pw(2, n) - 1;
  std::vector<int> fac(m + 1, 1), down(m + 1, 1);
  for (int i = 1; i <= m; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
  for (int i = 1; i <= m; ++i) down[i] = 1ll * down[i - 1] * (pw_2 - i + 1) % P;

  auto choose = [&](int x) { return 1ll * down[x] * pw(fac[x]) % P; };

  std::vector<int> f(m + 1);
  for (int i = 3; i <= m; ++i)
    f[i] = 1ll * ((choose(i - 1) - f[i - 1] - 1ll * f[i - 2] * (pw_2 - i + 2) % P) % P + P) * pw(i) % P;

  std::cout << f[m] << '\n';
  return 0;
}