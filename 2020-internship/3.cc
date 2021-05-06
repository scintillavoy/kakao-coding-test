#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> solution(vector<string> gems) {
  vector<int> answer;
  unordered_map<string, int> check;
  for (const auto &gem : gems) {
    check[gem] = 1;
  }
  int num = check.size();

  int left = 0, right = 0;
  while (right < gems.size()) {
    // Move right pointer
    do {
      --check[gems[right]];
      if (check[gems[right]] == 0) {
        --num;
      }
      ++right;
    } while (num > 0);

    // Move left pointer
    while (check[gems[left]] < 0) {
      ++check[gems[left]];
      ++left;
    }

    // Update answer
    if (answer.empty() || answer[1] - answer[0] > right - 1 - left) {
      answer = {left + 1, right};
    }
  }

  return answer;
}
