#include <bits/stdc++.h>

using i64 = long long;

constexpr int kN = 205;

int n, a[kN], trie[kN][26], tot, val[kN], w[kN], fail[kN];
i64 l;
std::queue<int> q;
struct Mat {
  i64 a[kN][kN];
  Mat() {
    for (int i = 0; i <= tot; ++i)
      for (int j = 0; j <= tot; ++j) a[i][j] = -1e18;
  }
  Mat operator*(const Mat &rhs) const {
    Mat ret;
    for (int i = 0; i <= tot; ++i)
      for (int j = 0; j <= tot; ++j)
        for (int k = 0; k <= tot; ++k) ret.a[i][j] = std::max(ret.a[i][j], a[i][k] + rhs.a[k][j]);
    return ret;
  }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  std::cin >> n >> l;
  for (int i = 0; i < n; ++i) std::cin >> a[i];
  for (int i = 0, u; i < n; ++i) {
    std::string s;
    std::cin >> s, u = 0;
    for (char c : s) u = trie[u][c - 'a'] ? trie[u][c - 'a'] : (trie[u][c - 'a'] = ++tot);
    val[u] += a[i];
  }
  for (int i = 0; i < 26; ++i)
    if (trie[0][i]) q.emplace(trie[0][i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i)
      if (trie[u][i])
        fail[trie[u][i]] = trie[fail[u]][i], q.emplace(trie[u][i]);
      else
        trie[u][i] = trie[fail[u]][i];
  }
  for (int i = 1; i <= tot; ++i)
    for (int j = i; j; j = fail[j]) w[i] += val[j];
  Mat init, tran;
  init.a[0][0] = 0;
  for (int i = 0; i <= tot; ++i)
    for (int j = 0; j < 26; ++j) tran.a[i][trie[i][j]] = w[trie[i][j]];
  for (; l; l >>= 1, tran = tran * tran)
    if (l & 1) init = init * tran;
  std::cout << *std::max_element(init.a[0], init.a[0] + tot + 1) << "\n";
  return 0;
}