#include <algorithm>
#include <cmath>
#include <iterator>
#include <list>
#include <string>
#include <vector>
using namespace std;

long long solution(string expression) {
  long long answer = 0;
  vector<string> precedences{"*+-", "*-+", "+*-", "+-*", "-+*", "-*+"};
  list<char> operators;
  list<long long> nums;

  // Tokenize expression into operators and nums
  string num;
  for (const auto &c : expression) {
    switch (c) {
      case '*':
      case '+':
      case '-':
        nums.push_back(stoll(num));
        num = "";
        operators.push_back(c);
        break;
      default:
        num += c;
    }
  }
  nums.push_back(stoll(num));

  // Evaluate
  for (const auto &precedence : precedences) {
    list<char> operators_ = operators;
    list<long long> nums_ = nums;
    for (const auto &x : precedence) {
      auto operators_it = operators_.begin();
      auto nums_it = nums_.begin();
      while (operators_it != operators_.end()) {
        if (*operators_it == x) {
          long long temp;
          switch (x) {
            case '*':
              temp = (*nums_it) * (*next(nums_it));
              break;
            case '+':
              temp = (*nums_it) + (*next(nums_it));
              break;
            case '-':
              temp = (*nums_it) - (*next(nums_it));
              break;
          }
          operators_it = operators_.erase(operators_it);
          nums_it = nums_.erase(nums_it);
          nums_it = nums_.erase(nums_it);
          nums_it = nums_.insert(nums_it, temp);
        } else {
          ++operators_it;
          ++nums_it;
        }
      }
    }
    answer = max(answer, abs(nums_.front()));
  }

  return answer;
}
