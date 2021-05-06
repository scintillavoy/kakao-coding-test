#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
  vector<unordered_set<int>> adjacents(n);
  vector<unordered_set<int>> locks(n);      // locks[i] -> room i
  vector<unordered_set<int>> unlocks(n);    // room i -> unlocks[i]
  vector<int> states(n, 0);
  // 0: unvisited, 1: visiting, 2: waiting, 3: visited
  
  // Construct data structures
  for (const auto &x : path) {
    adjacents[x[0]].insert(x[1]);
    adjacents[x[1]].insert(x[0]);
  }
  for (const auto &x : order) {
    unlocks[x[0]].insert(x[1]);
    locks[x[1]].insert(x[0]);
  }

  // Do BFS
  queue<int> bfs;
  bfs.push(0);
  states[0] = 1;
  while (!bfs.empty()) {
    int curr = bfs.front();
    bfs.pop();

    // If it is locked
    if (!locks[curr].empty()) {
      states[curr] = 2;
      continue;
    }

    // Unlock other rooms
    for (const auto &unlock : unlocks[curr]) {
      locks[unlock].erase(curr);
      if (states[unlock] == 2 && locks[unlock].empty()) {
        states[unlock] = 1;
        bfs.push(unlock);
      }
    }

    // Visit adjacents
    for (const auto &adj : adjacents[curr]) {
      if (states[adj] != 0) continue;
      states[adj] = 1;
      bfs.push(adj);
    }

    states[curr] = 3;
  }

  // Check if all the rooms visited
  for (const auto &state : states) {
    if (state != 3) {
      return false;
    }
  }
  return true;
}
