#include <cctype>
#include <string>
#include <vector>
using namespace std;

string solution(string new_id) {
  string temp;

  // Step 1
  for (auto &x : new_id) {
    if (isupper(x)) {
      x = tolower(x);
    }
  }

  // Step 2
  temp.clear();
  for (auto &x : new_id) {
    if (islower(x) || isdigit(x) || x == '-' || x == '_' || x == '.') {
      temp += x;
    }
  }
  new_id = temp;

  // Step 3
  temp.clear();
  for (int i = 0; i < new_id.size(); ++i) {
    temp += new_id[i];
    while (new_id[i] == '.' && i + 1 < new_id.size() && new_id[i + 1] == '.') {
      ++i;
    }
  }
  new_id = temp;

  // Step 4
  if (!new_id.empty() && new_id.front() == '.') new_id = new_id.substr(1);
  if (!new_id.empty() && new_id.back() == '.') new_id.pop_back();

  // Step 5
  if (new_id.empty()) new_id = "a";

  // Step 6
  if (new_id.size() >= 16) {
    new_id = new_id.substr(0, 15);
  }
  if (new_id.back() == '.') new_id.pop_back();

  // Step 7
  while (new_id.size() <= 2) {
    new_id += new_id.back();
  }

  return new_id;
}
