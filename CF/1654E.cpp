#include <bits/extc++.h>

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  constexpr int V = 1E5;
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int &t : a) std::cin >> t;

  int ans = n;
  for (int d = -100; d <= 100; ++d) {
    __gnu_pbds::gp_hash_table<int, int> mp;
    for (int i = 0; i < n; ++i) ++mp[a[i] - i * d];
    for (auto p : mp) ans = std::min(ans, n - p.second);
  }
  std::vector<__gnu_pbds::gp_hash_table<int, int>> dp(n);
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < std::min(i + 1001, n); ++j)
      if ((a[j] - a[i]) % (j - i) == 0) ++dp[i][(a[j] - a[i]) / (j - i)];
  for (int i = 0; i < n; ++i)
    for (auto p : dp[i]) ans = std::min(ans, n - p.second - 1);

  std::cout << ans << "\n";
  return 0;
}