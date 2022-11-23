#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, m, p, q;
  std::cin >> n >> m >> p >> q;
  std::vector<std::vector<char>> field(n, std::vector<char>(m));
  for (auto &elem : field) for_each(all(elem), [](char &elem) { std::cin >> elem; });

  return 0;
}