#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42576
 * --내 풀이 ---
 * 값들을 hash table 에 입력
 * 값들을 뺌. 빈 배열이라면 삭제
 * iter 하면서, 이름을 모두 반환
 *
 */

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
  auto marathoners = std::map<std::string /*name*/, int /*count*/>();
  for (auto &p : participant) {
    marathoners[p]++;
  }

  for (auto &c : completion) {
    marathoners[c]--;
  }

  for (auto &m : marathoners) {
    if (m.second != 0)
      return m.first;
  }

  assert(false);
}

int main(int argc, char const *argv[]) {

  auto r = solution({"mislav", "stanko", "mislav", "ana"},
                    {"stanko", "ana", "mislav"});

  std::cout << "result (expect : mislav): " << r << std::endl;

  return 0;
}
