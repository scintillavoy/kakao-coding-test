#include <algorithm>
#include <limits>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int solution(vector<vector<int>> board) {
  int answer = numeric_limits<int>::max();
  // dp[row][col][the number of corners][orientation] = length
  // 3rd dimension is not necessary if we save the actual cost in dp
  // orientation: 0 = right, 1 = down, 2 = left, 3 = up
  vector<vector<vector<vector<int>>>> dp(board.size(),
    vector<vector<vector<int>>>(board.size(),
    vector<vector<int>>(board.size() * board.size(),
    vector<int>(4, 0))));
  vector<vector<int>> orientations{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  // Initialize queue for BFS
  queue<vector<int>> bfs;
  if (board[0][1] == 0) {
    dp[0][1][0][0] = 1;
    bfs.push({0, 1, 0, 0});
  }
  if (board[1][0] == 0) {
    dp[1][0][0][1] = 1;
    bfs.push({1, 0, 0, 1});
  }

  // Do BFS
  while (!bfs.empty()) {
    vector<int> curr = bfs.front();
    bfs.pop();
    vector<int> next;
    // i == 0: go straight
    // i == 1: go right
    // i == 2: go backwards (skipped)
    // i == 3: go left
    for (int i = 0; i < 4; ++i) {
      if (i == 2) continue;     // Don't have to go backwards
      next = curr;
      next[0] += orientations[(curr[3] + i) % 4][0];
      next[1] += orientations[(curr[3] + i) % 4][1];
      if (i != 0) next[2] += 1; // rotate
      next[3] = (curr[3] + i) % 4;
      if (next[0] >= 0 && next[0] < board.size() &&
          next[1] >= 0 && next[1] < board.size() &&
          next[2] < board.size() * board.size() &&
          board[next[0]][next[1]] == 0 &&
          dp[next[0]][next[1]][next[2]][next[3]] == 0) {
        dp[next[0]][next[1]][next[2]][next[3]] =
            dp[curr[0]][curr[1]][curr[2]][curr[3]] + 1;
        bfs.push({next[0], next[1], next[2], next[3]});
      }
    }
  }

  // Get the minimum cost
  for (int i = 0; i < board.size() * board.size(); ++i) {
    for (int j = 0; j < 4; ++j) {
      if (dp[board.size()-1][board.size()-1][i][j] != 0) {
        answer = min(answer,
                     dp[board.size()-1][board.size()-1][i][j] * 100 + i * 500);
      }
    }
  }

  return answer;
}
