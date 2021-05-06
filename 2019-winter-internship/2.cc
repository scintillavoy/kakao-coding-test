#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> solution(string s) {
  vector<int> answer;
  vector<unordered_set<int>> sets;
  int num = 0;

  // Parse string
  for (int i = 1; i < s.size() - 1; ++i) {
    switch (s[i]) {
      case '{':
        sets.emplace_back();
        break;
      case '}':
      case ',':
        if (num != 0) sets.back().insert(num);
        num = 0;
        break;
      default:
        num = num * 10 + s[i] - '0';
    }
  }

  // Sort by size
  sort(sets.begin(), sets.end(),
       [](const unordered_set<int> &a, const unordered_set<int> &b) {
         return a.size() < b.size();
       });

  // Construct answer
  answer.push_back(*(sets[0].begin()));
  for (int i = 1; i < sets.size(); ++i) {
    for (auto it = sets[i].begin(); it != sets[i].end(); ++it) {
      if (sets[i - 1].count(*it) == 0) {
        answer.push_back(*it);
        break;
      }
    }
  }
  return answer;
}
