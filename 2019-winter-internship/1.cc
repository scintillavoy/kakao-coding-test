#include <stack>
#include <string>
#include <vector>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
  int answer = 0;
  stack<int> bucket;
  for (int i = 0; i < moves.size(); ++i) {
    int row = 0;
    int col = moves[i] - 1;
    while (row < board.size() && board[row][col] == 0) ++row;
    if (row == board.size()) continue;
    if (!bucket.empty() && bucket.top() == board[row][col]) {
      answer += 2;
      bucket.pop();
    } else {
      bucket.push(board[row][col]);
    }
    board[row][col] = 0;
  }
  return answer;
}
