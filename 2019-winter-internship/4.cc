#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

long long FindNext(unordered_map<long long, long long> &rooms,
                   long long room_number) {
  if (rooms.count(room_number) == 0) {
    return room_number;
  }
  return rooms[room_number] = FindNext(rooms, rooms[room_number]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
  vector<long long> answer;
  unordered_map<long long, long long> rooms;
  for (int i = 0; i < room_number.size(); ++i) {
    long long empty_room = FindNext(rooms, room_number[i]);
    answer.push_back(empty_room);
    rooms[empty_room] = empty_room + 1;
  }
  return answer;
}
