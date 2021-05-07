#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void ChooseK(const string &order, int K, int from, string prefix,
             unordered_map<string, int> &combinations) {
  if (K == 0) {
    ++combinations[prefix];
    return;
  }
  for (int i = from; i < order.size(); ++i) {
    ChooseK(order, K - 1, i + 1, prefix + order[i], combinations);
  }
}

vector<string> solution(vector<string> orders, vector<int> course) {
  vector<string> answer;
  unordered_map<int, unordered_map<string, int>> combinations;
  for (auto &order : orders) {
    sort(order.begin(), order.end());
    for (const auto &K : course) {
      ChooseK(order, K, 0, "", combinations[K]);
    }
  }

  for (const auto &combination : combinations) {
    int max_freq = -1;
    for (const auto &x : combination.second) {
      max_freq = max(max_freq, x.second);
    }
    for (const auto &x : combination.second) {
      if (max_freq >= 2 && x.second == max_freq) {
        answer.push_back(x.first);
      }
    }
  }
  sort(answer.begin(), answer.end());
  return answer;
}
