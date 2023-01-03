#include <bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  struct ACAuto {
    int tot;
    std::vector<std::array<int, 26>> trie;
    std::vector<int> end, fail;
    int New() {
      std::array<int, 26> tmp;
      tmp.fill(0), trie.emplace_back(tmp), end.emplace_back(0), fail.emplace_back(0);
      return tot++;
    }
    void Add(std::string s) {
      int u = 0, v;
      for (char ch : s)
        if (trie[u][ch - 'a'])
          u = trie[u][ch - 'a'];
        else
          v = New(), u = (trie[u][ch - 'a'] = v);
      ++end[u];
    }
    ACAuto(std::vector<std::string> str = {}) {
      trie.clear(), end.clear(), fail.clear(), tot = 0, assert(!New());
      for (auto elem : str) Add(elem);
    }
    void Build() {
      std::queue<int> q;
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
    }
    int Query(std::string t, bool re = 0) {
      int u = 0, ret = 0;
      std::vector<std::pair<int, int>> rev(0);
      for (char ch : t) {
        u = trie[u][ch - 'a'];
        for (int v = u; v && ~end[v]; v = fail[v]) {
          if (re) rev.emplace_back(end[v], v);
          ret += end[v], end[v] = -1;
        }
      }
      for (auto p : rev) end[p.second] = p.first;
      return ret;
    }
  };
  int n;
  std::cin >> n;
  ACAuto solve;
  while (n--) {
    std::string s;
    std::cin >> s, solve.Add(s);
  }
  solve.Build();
  std::string t;
  std::cin >> t;
  std::cout << solve.Query(t) << "\n";
  return 0;
}