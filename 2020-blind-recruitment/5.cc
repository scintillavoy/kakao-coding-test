#include <string>
#include <vector>
using namespace std;

// Check if the object can be placed in wall[row][col]
bool CheckCondition(const vector<vector<int>> &wall, int row, int col, int type) {
  if (row < 0 || row >= wall.size() || col < 0 || col >= wall.size()) {
    return true;
  }
  if ((wall[row][col] & (1 << type)) == 0) return true;
  if (type == 0) {        // Vertical
    if (col == 0 ||
        (col > 0 && (wall[row][col-1] & 1) != 0) ||
        (wall[row][col] & 2) != 0 ||
        (row > 0 && (wall[row-1][col] & 2) != 0)) {
      return true;
    } else {
      return false;
    }
  } else if (type == 1) { // Horizontal
    if ((col > 0 && (wall[row][col-1] & 1) != 0) ||
        (row+1 < wall.size() && col > 0 && (wall[row+1][col-1] & 1) != 0) ||
        (row > 0 && (wall[row-1][col] & 2) != 0 &&
        row+1 < wall.size() && (wall[row+1][col] & 2) != 0)) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
  vector<vector<int>> wall(n+1, vector<int>(n+1, 0));
  // 0: nothing, 1: vertical, 2: horizontal, 3: both

  // Process build_frame
  for (const auto &build : build_frame) {
    if (build[3] == 1) {            // Add
      wall[build[0]][build[1]] |= (1 << build[2]);
      if (CheckCondition(wall, build[0], build[1], build[2])) {
        continue;
      } else {
        wall[build[0]][build[1]] &= ~(1 << build[2]);
      }
    } else if (build[3] == 0) {     // Remove
      if (build[2] == 0) {          // Vertical
        wall[build[0]][build[1]] &= ~(1 << build[2]);
        if (CheckCondition(wall, build[0], build[1]+1, 0) &&
            CheckCondition(wall, build[0]-1, build[1]+1, 1) &&
            CheckCondition(wall, build[0], build[1]+1, 1)) {
          continue;
        } else {
          wall[build[0]][build[1]] |= (1 << build[2]);
        }
      } else if (build[2] == 1) {   // Horizontal
        wall[build[0]][build[1]] &= ~(1 << build[2]);
        if (CheckCondition(wall, build[0], build[1], 0) &&
            CheckCondition(wall, build[0]+1, build[1], 0) &&
            CheckCondition(wall, build[0]-1, build[1], 1) &&
            CheckCondition(wall, build[0]+1, build[1], 1)) {
          continue;
        } else {
          wall[build[0]][build[1]] |= (1 << build[2]);
        }
      }
    }
  }

  // Construct answer
  vector<vector<int>> answer;
  for (int i = 0; i < wall.size(); ++i) {
    for (int j = 0; j < wall.size(); ++j) {
      if ((wall[i][j] & 1) != 0) {
        answer.push_back({i, j, 0});
      }
      if ((wall[i][j] & 2) != 0) {
        answer.push_back({i, j, 1});
      }
    }
  }
  return answer;
}
