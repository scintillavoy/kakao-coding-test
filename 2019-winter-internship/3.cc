#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

void sol(vector<string> &user_id, vector<string> &banned_id,
         unordered_set<int> &match_list, int match, int idx) {
  // Base case
  if (idx == banned_id.size()) {
    match_list.insert(match);
    return;
  }

  for (int i = 0; i < user_id.size(); ++i) {
    // Check if matched
    if (user_id[i].size() != banned_id[idx].size() || (match & (1 << i)) != 0) {
      continue;
    }
    int j;
    for (j = 0; j < user_id[i].size(); ++j) {
      if (banned_id[idx][j] != '*' && user_id[i][j] != banned_id[idx][j]) {
        break;
      }
    }
    // Matching succeeded
    if (j == user_id[i].size()) {
      sol(user_id, banned_id, match_list, match | (1 << i), idx + 1);
    }
  }
}

int solution(vector<string> user_id, vector<string> banned_id) {
  unordered_set<int> match_list;
  sol(user_id, banned_id, match_list, 0, 0);
  return match_list.size();
}
