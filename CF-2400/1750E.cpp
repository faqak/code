#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

  auto sol = []() {
    int n;
    i64 ans = 0, res = 0;
    std::string s;
    std::cin >> n >> s;
    std::stack<int> st;
    std::vector<int> a(0), pre(n);

    for (int i = 0; i < n; ++i) {
      ans += 1ll * (i + 1) * (n - i), a.emplace_back(2 * (s[i] == ')') - 1);
      if (s[i] == '(')
        st.emplace(i);
      else {
        if (st.empty()) continue;
        res += 1ll * (st.top() + 1) * (n - i), st.pop();
      }
    }

    std::partial_sum(all(a), begin(pre)), sort(all(pre));
    for (int i = 0; i < n; ans += abs(pre[i++])) ans += 1ll * pre[i] * (2 * i + 1 - n);

    std::cout << ans / 2 - res << '\n';
  };

  int T;
  std::cin >> T;
  while (T--) sol();
  return 0;
}