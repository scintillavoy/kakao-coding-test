#include <cmath>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string solution(vector<int> numbers, string hand) {
  string answer;
  vector<pair<int, int>> pos{{3, 1},                  // 0
                             {0, 0}, {0, 1}, {0, 2},  // 1 2 3
                             {1, 0}, {1, 1}, {1, 2},  // 4 5 6
                             {2, 0}, {2, 1}, {2, 2},  // 7 8 9
                             {3, 0}, {3, 2}};         // * #
  int left = 10, right = 11;
  for (const auto &num : numbers) {
    switch (num) {
      case 1:
      case 4:
      case 7:
        answer.push_back('L');
        left = num;
        break;
      case 3:
      case 6:
      case 9:
        answer.push_back('R');
        right = num;
        break;
      case 2:
      case 5:
      case 8:
      case 0:
        int left_dist = abs(pos[left].first - pos[num].first) +
                        abs(pos[left].second - pos[num].second);
        int right_dist = abs(pos[right].first - pos[num].first) +
                         abs(pos[right].second - pos[num].second);
        if (left_dist < right_dist) {
          answer.push_back('L');
          left = num;
        } else if (left_dist > right_dist) {
          answer.push_back('R');
          right = num;
        } else if (hand == "left") {
          answer.push_back('L');
          left = num;
        } else {
          answer.push_back('R');
          right = num;
        }
        break;
    }
  }
  return answer;
}
