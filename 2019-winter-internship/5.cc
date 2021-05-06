#include <algorithm>
#include <deque>
#include <limits>
#include <vector>
using namespace std;

// Time complexity: O(n)
// Sliding window with monotonically decreasing queue
int solution(vector<int> stones, int k) {
  int answer = numeric_limits<int>::max();
  deque<int> window;
  for (int i = 0; i < stones.size(); ++i) {
    // Keep the window monotonically decreasing
    while (!window.empty() && stones[window.back()] <= stones[i]) {
      window.pop_back();
    }
    // Push the index of the next stone
    window.push_back(i);
    // The length of the window should be less than or equal to k
    if (i - window.front() >= k) {
      window.pop_front();
    }
    // Update the answer
    if (i >= k - 1) {
      answer = min(answer, stones[window.front()]);
    }
  }
  return answer;
}
