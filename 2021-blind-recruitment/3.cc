#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void SaveInfo(unordered_map<string, vector<int>> &info_map, string &info_key,
              int score, int depth) {
  if (depth == 4) {
    info_map[info_key].push_back(score);
    return;
  }
  SaveInfo(info_map, info_key, score, depth + 1);
  char temp = info_key[depth];
  info_key[depth] = '-';
  SaveInfo(info_map, info_key, score, depth + 1);
  info_key[depth] = temp;
}

vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  unordered_map<string, vector<int>> info_map;

  for (const auto &x : info) {
    istringstream iss(x);
    string word;
    string info_key;
    while (iss >> word) {
      if (word == "and") {
        continue;
      } else if (isdigit(word.front())) {
        SaveInfo(info_map, info_key, stoi(word), 0);
        break;
      } else {
        info_key += word.front();
      }
    }
  }

  for (auto &x : info_map) {
    sort(x.second.begin(), x.second.end());
  }

  for (const auto &x : query) {
    istringstream iss(x);
    string word;
    string query_key;
    while (iss >> word) {
      if (word == "and") {
        continue;
      } else if (isdigit(word.front())) {
        auto lb = lower_bound(info_map[query_key].begin(),
                              info_map[query_key].end(), stoi(word));
        answer.push_back(info_map[query_key].end() - lb);
        break;
      } else {
        query_key += word.front();
      }
    }
  }

  return answer;
}
