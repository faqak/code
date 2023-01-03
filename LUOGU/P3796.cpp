#include <bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  struct ACAuto {
    int tot;
    std::vector<std::array<int, 26>> trie;
    std::vector<int> end, fail, id, num;
    std::vector<std::string> input;
    int New() {
      std::array<int, 26> tmp;
      tmp.fill(0), trie.emplace_back(tmp), end.emplace_back(0), fail.emplace_back(0), num.emplace_back(0);
      return tot++;
    }
    void Add(std::string s) {
      int u = 0, v;
      input.emplace_back(s);
      for (char ch : s)
        if (trie[u][ch - 'a'])
          u = trie[u][ch - 'a'];
        else
          v = New(), u = (trie[u][ch - 'a'] = v);
      ++end[u], id.emplace_back(u);
    }
    ACAuto(std::vector<std::string> str = {}) {
      input.clear(), trie.clear(), end.clear(), fail.clear(), id.clear(), tot = 0, assert(!New());
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
    void Query(std::string t) {
      int u = 0, mx = 0;
      for (int &t : num) t = 0;
      for (char ch : t) {
        u = trie[u][ch - 'a'];
        for (int v = u; v; v = fail[v]) ++num[v];
      }

      for (int t : id) mx = std::max(mx, num[t]);
      std::cout << mx << "\n";
      for (int i = 0; i < id.size(); ++i)
        if (num[id[i]] == mx) std::cout << input[i] << "\n";
      return;
    }
  };
  int n;
  while (std::cin >> n && n) {
    ACAuto solve;
    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      solve.Add(s);
    }
    std::string t;
    std::cin >> t;
    solve.Build(), solve.Query(t);
  }
  return 0;
}