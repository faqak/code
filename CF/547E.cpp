#include <bits/extc++.h>

#define all(x) begin(x), end(x)

using i64 = long long;
using u64 = unsigned long long;

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
  int n, q, s = 0;
  std::cin >> n >> q;
  constexpr u64 B = 924877;
  constexpr int SIGMA = 2e5;
  std::vector<std::string> str(n);
  std::vector<std::vector<std::pair<int, int>>> token(n);
  std::vector<int> ret(2 * q);
  std::vector<u64> pw(SIGMA + 1, 1);
  for (int i = 1; i <= SIGMA; ++i) pw[i] = pw[i - 1] * B;
  std::vector<std::vector<u64>> mapp(n);
  std::vector<std::tuple<int, int, int>> que(2 * q), lo(0), hi(0);
  __gnu_pbds::gp_hash_table<u64, int> hash;
  for (auto &elem : str) std::cin >> elem, s += elem.size();
  const int b = sqrt(s);
  for (int i = 0; i < n; ++i) {
    mapp[i].resize(str[i].size() + 1);
    mapp[i][0] = 0;
    for (int j = 0; j < str[i].size(); ++j) mapp[i][j + 1] = mapp[i][j] * B + str[i][j] - 'a' + 1;
  }
  for (int i = 0, l, k, r; i < q; ++i)
    std::cin >> l >> r >> k, --l, --r, --k, que[2 * i] = {l - 1, k, 2 * i}, que[2 * i + 1] = {r, k, 2 * i + 1};
  std::sort(all(que));
  for (auto elem : que) (str[std::get<1>(elem)].size() > b ? hi : lo).emplace_back(elem);

  auto Get = [&](int id, int l, int r) { return mapp[id][r] - mapp[id][l] * pw[r - l]; };

  auto Add = [&](int id) {
    for (int i = 0; i < str[id].size(); ++i)
      for (int j = i; j < std::min((int)str[id].size(), i + b); ++j)
        if (hash.find(Get(id, i, j + 1)) != hash.end()) ++hash[Get(id, i, j + 1)];
  };

  // solve low
  int p = 0;
  for (auto elem : lo) {
    int k = std::get<1>(elem);
    hash[Get(k, 0, str[k].size())] = 1;
  }
  for (auto elem : lo) {
    int r = std::get<0>(elem), k = std::get<1>(elem), id = std::get<2>(elem);
    while (p <= r) Add(p++);
    ret[id] = hash[Get(k, 0, str[k].size())] - 1;
  }
  // solve high
  for (auto elem : hi) {
    int r = std::get<0>(elem), k = std::get<1>(elem), id = std::get<2>(elem);
    token[k].emplace_back(r, id);
  }
  for (int i = 0; i < n; ++i) {
    if (str[i].size() <= b) continue;
    int key = i;
    std::vector<int> nxt(str[i].size());
    for (int &t : nxt) t = -1;
    for (int i = 1, j = -1; i < str[key].size(); ++i) {
      while (j >= 0 && str[key][j + 1] != str[key][i]) j = nxt[j];
      nxt[i] = (j += (str[key][j + 1] == str[key][i]));
    }
    std::string big = "";
    for (auto elem : str) big += elem + '#';
    std::vector<int> val(0);
    int cur = 0;
    for (int i = 0, j = -1; i < big.size(); ++i) {
      while (j >= 0 && str[key][j + 1] != big[i]) j = nxt[j];
      j += (str[key][j + 1] == big[i]);
      cur += (j == str[key].size() - 1);
      if (big[i] == '#') val.emplace_back(cur), cur = 0;
    }
    int pt = 0;
    for (auto p : token[i]) {
      int r = p.first, id = p.second;
      while (pt <= r) cur += val[pt++];
      ret[id] = cur;
    }
  }
  for (int i = 0; i < q; ++i) std::cout << ret[i * 2 + 1] - ret[i * 2] << "\n";
  return 0;
}